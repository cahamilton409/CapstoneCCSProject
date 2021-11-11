/*
 * SPI.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Emory
 */
#include "SPI.h"

#define DUMMY   0xFF

#define SLAVE_CS_OUT    P3OUT
#define SLAVE_CS_DIR    P3DIR
#define SLAVE_CS_PIN    BIT2

#define CMD_TYPE_0_SLAVE              0
#define CMD_TYPE_1_SLAVE              1
#define CMD_TYPE_2_SLAVE              2

#define CMD_TYPE_0_MASTER              3
#define CMD_TYPE_1_MASTER              4
#define CMD_TYPE_2_MASTER              5

#define TYPE_0_LENGTH              4
#define TYPE_1_LENGTH              1
#define TYPE_2_LENGTH              1

#define MAX_BUFFER_SIZE     20

uint8_t SlaveType0[TYPE_0_LENGTH] = {0};
uint8_t SlaveType1[TYPE_1_LENGTH] = {0};
uint8_t SlaveType2[TYPE_2_LENGTH] = {0};

SPI_Mode MasterMode = IDLE_MODE;
uint8_t TransmitRegAddr = 0;
uint8_t ReceiveBuffer[MAX_BUFFER_SIZE] = {0};
uint8_t RXByteCtr = 0;
uint8_t ReceiveIndex = 0;
uint8_t TransmitBuffer[MAX_BUFFER_SIZE] = {0};
uint8_t TXByteCtr = 0;
uint8_t TransmitIndex = 0;

//Copies an array to a different destination.
void CopyArray(uint8_t *source, uint8_t *dest, uint8_t count)
{
    uint8_t copyIndex = 0;
    for (copyIndex = 0; copyIndex < count; copyIndex++)
    {
        dest[copyIndex] = source[copyIndex];
    }
}

//Writes over SPY to a register with a value.
SPI_Mode SPI_Master_Write(uint8_t *reg_data, uint8_t count)
{
    MasterMode = TX_DATA_MODE;

    //Copy register data to TransmitBuffer
    CopyArray(reg_data, TransmitBuffer, count);

    TXByteCtr = count-1;
    RXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;

    SendUCA0Data(TransmitBuffer[TransmitIndex++]);
    __bis_SR_register(CPUOFF + GIE);              // Enter LPM0 w/ interrupts

    return MasterMode;
}

//Writes over SPY to a register with a value and a lead register.
SPI_Mode SPI_Master_WriteReg(uint8_t reg_addr, uint8_t *reg_data, uint8_t count)
{
    MasterMode = TX_REG_ADDRESS_MODE;
    TransmitRegAddr = reg_addr;

    //Copy register data to TransmitBuffer
    CopyArray(reg_data, TransmitBuffer, count);

    TXByteCtr = count;
    RXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;

    SendUCA0Data(TransmitRegAddr);

    __bis_SR_register(CPUOFF + GIE);              // Enter LPM0 w/ interrupts

    return ReceiveBuffer;
}

//Reads over SPY from a register.
uint8_t * SPI_Master_ReadReg(uint8_t reg_addr, uint8_t count)
{
    MasterMode = TX_REG_ADDRESS_MODE;
    TransmitRegAddr = reg_addr;
    RXByteCtr = count;
    TXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;

    SendUCA0Data(TransmitRegAddr);

    __bis_SR_register(CPUOFF + GIE);              // Enter LPM0 w/ interrupts

    return ReceiveBuffer;
}

//Sends data to SPI buffer.
void SendUCA0Data(uint8_t val)
{
    while (!(UCA0IFG & UCTXIFG));              // USCI_A0 TX buffer ready?
    UCA0TXBUF = val;
}

//Toggles transmit enable bit on.
void CS_On()
{
    SLAVE_CS_OUT |= SLAVE_CS_PIN;
}

//Toggles transmit enable bit off.
void CS_Off()
{
    SLAVE_CS_OUT &= ~(SLAVE_CS_PIN);
}

//******************************************************************************
// Device Initialization *******************************************************
//******************************************************************************

//Setting clock to 16 MHz.
void initClockTo16MHz()
{
    UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
    UCSCTL4 |= SELA_2;                        // Set ACLK = REFO
    __bis_SR_register(SCG0);                  // Disable the FLL control loop
    UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
    UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation
    UCSCTL2 = FLLD_0 + 487;                   // Set DCO Multiplier for 16MHz
                                              // (N + 1) * FLLRef = Fdco
                                              // (487 + 1) * 32768 = 16MHz
                                              // Set FLL Div = fDCOCLK
    __bic_SR_register(SCG0);                  // Enable the FLL control loop

    // Worst-case settling time for the DCO when the DCO range bits have been
    // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
    // UG for optimization.
    // 32 x 32 x 16 MHz / 32,768 Hz = 500000 = MCLK cycles for DCO to settle
    __delay_cycles(500000);//
    // Loop until XT1,XT2 & DCO fault flag is cleared
    do
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG); // Clear XT2,XT1,DCO fault flags
        SFRIFG1 &= ~OFIFG;                          // Clear fault flags
    }while (SFRIFG1&OFIFG);                         // Test oscillator fault flag
}

//adjust voltage for 16 MHz clock
uint16_t setVCoreUp(uint8_t level){
    uint32_t PMMRIE_backup, SVSMHCTL_backup, SVSMLCTL_backup;

    //The code flow for increasing the Vcore has been altered to work around
    //the erratum FLASH37.
    //Please refer to the Errata sheet to know if a specific device is affected
    //DO NOT ALTER THIS FUNCTION

    //Open PMM registers for write access
    PMMCTL0_H = 0xA5;

    //Disable dedicated Interrupts
    //Backup all registers
    PMMRIE_backup = PMMRIE;
    PMMRIE &= ~(SVMHVLRPE | SVSHPE | SVMLVLRPE |
                SVSLPE | SVMHVLRIE | SVMHIE |
                SVSMHDLYIE | SVMLVLRIE | SVMLIE |
                SVSMLDLYIE
                );
    SVSMHCTL_backup = SVSMHCTL;
    SVSMLCTL_backup = SVSMLCTL;

    //Clear flags
    PMMIFG = 0;

    //Set SVM highside to new level and check if a VCore increase is possible
    SVSMHCTL = SVMHE | SVSHE | (SVSMHRRL0 * level);

    //Wait until SVM highside is settled
    while((PMMIFG & SVSMHDLYIFG) == 0)
    {
        ;
    }

    //Clear flag
    PMMIFG &= ~SVSMHDLYIFG;

    //Check if a VCore increase is possible
    if((PMMIFG & SVMHIFG) == SVMHIFG)
    {
        //-> Vcc is too low for a Vcore increase
        //recover the previous settings
        PMMIFG &= ~SVSMHDLYIFG;
        SVSMHCTL = SVSMHCTL_backup;

        //Wait until SVM highside is settled
        while((PMMIFG & SVSMHDLYIFG) == 0)
        {
            ;
        }

        //Clear all Flags
        PMMIFG &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG |
                     SVMLVLRIFG | SVMLIFG |
                     SVSMLDLYIFG
                     );

        //Restore PMM interrupt enable register
        PMMRIE = PMMRIE_backup;
        //Lock PMM registers for write access
        PMMCTL0_H = 0x00;
        //return: voltage not set
        return false;
    }

    //Set also SVS highside to new level
    //Vcc is high enough for a Vcore increase
    SVSMHCTL |= (SVSHRVL0 * level);

    //Wait until SVM highside is settled
    while((PMMIFG & SVSMHDLYIFG) == 0)
    {
        ;
    }

    //Clear flag
    PMMIFG &= ~SVSMHDLYIFG;

    //Set VCore to new level
    PMMCTL0_L = PMMCOREV0 * level;

    //Set SVM, SVS low side to new level
    SVSMLCTL = SVMLE | (SVSMLRRL0 * level) |
               SVSLE | (SVSLRVL0 * level);

    //Wait until SVM, SVS low side is settled
    while((PMMIFG & SVSMLDLYIFG) == 0)
    {
        ;
    }

    //Clear flag
    PMMIFG &= ~SVSMLDLYIFG;
    //SVS, SVM core and high side are now set to protect for the new core level

    //Restore Low side settings
    //Clear all other bits _except_ level settings
    SVSMLCTL &= (SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 +
                 SVSMLRRL1 + SVSMLRRL2
                 );

    //Clear level settings in the backup register,keep all other bits
    SVSMLCTL_backup &=
        ~(SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

    //Restore low-side SVS monitor settings
    SVSMLCTL |= SVSMLCTL_backup;

    //Restore High side settings
    //Clear all other bits except level settings
    SVSMHCTL &= (SVSHRVL0 + SVSHRVL1 +
                 SVSMHRRL0 + SVSMHRRL1 +
                 SVSMHRRL2
                 );

    //Clear level settings in the backup register,keep all other bits
    SVSMHCTL_backup &=
        ~(SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);

    //Restore backup
    SVSMHCTL |= SVSMHCTL_backup;

    //Wait until high side, low side settled
    while(((PMMIFG & SVSMLDLYIFG) == 0) &&
          ((PMMIFG & SVSMHDLYIFG) == 0))
    {
        ;
    }

    //Clear all Flags
    PMMIFG &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG |
                SVMLVLRIFG | SVMLIFG | SVSMLDLYIFG
                );

    //Restore PMM interrupt enable register
    PMMRIE = PMMRIE_backup;

    //Lock PMM registers for write access
    PMMCTL0_H = 0x00;

    return true;
}

//adjust voltage core level for clock
bool increaseVCoreToLevel2()
{
    uint8_t level = 2;
    uint8_t actlevel;
    bool status = true;

    //Set Mask for Max. level
    level &= PMMCOREV_3;

    //Get actual VCore
    actlevel = PMMCTL0 & PMMCOREV_3;

    //step by step increase or decrease
    while((level != actlevel) && (status == true))
    {
        if(level > actlevel)
        {
            status = setVCoreUp(++actlevel);
        }
    }

    return (status);
}

//initialize all gpio pins
void initGPIO()
{
  //LEDs
  P1OUT = 0x00;                             // P1 setup for LED & reset output
  P1DIR |= BIT0 + BIT5;

  P4DIR |= BIT7;
  P4OUT &= ~(BIT7);

  //SPI Pins
  P3SEL |= BIT3 + BIT4;                     // P3.3,4 option select
  P2SEL |= BIT7;                            // P2.7 option select

  //Button to initiate transfer
  P1DIR &= ~BIT1;                           // Set P1.1 to inpput direction
  P1REN |= BIT1;                            // Enable P1.1 internal resistance
  P1OUT |= BIT1;                            // Set P1.1 as pull-Up resistance
  P1IES |= BIT1;                            // P1.1 Hi/Lo edge
  P1IFG &= ~BIT1;                           // P1.1 IFG cleared
  P1IE |= BIT1;                             // P1.1 interrupt enabled
}

//init SPI pins
void initSPI()
{
  //Clock Polarity: The inactive state is high
  //MSB First, 8-bit, Master, 3-pin mode, Synchronous
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 |= 0x20;                          // /2
  UCA0BR1 = 0;                              //
  UCA0MCTL = 0;                             // No modulation must be cleared for SPI
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                          // Enable USCI0 RX interrupt

  SLAVE_CS_DIR |= SLAVE_CS_PIN;
  SLAVE_CS_OUT |= SLAVE_CS_PIN;
}

//run SPI init sequence
void SPI_Init()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    increaseVCoreToLevel2();
    initClockTo16MHz();
    initGPIO();
    initSPI();

    __delay_cycles(100000);

}

//******************************************************************************
// SPI Interrupt ***************************************************************
//******************************************************************************

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  uint8_t uca0_rx_val = 0;
  switch(__even_in_range(UCA0IV,4))
  {
    case 0:break;                             // Vector 0 - no interrupt
    case 2:                                   // Vector 2 - RXIFG
        uca0_rx_val = UCA0RXBUF;
        switch (MasterMode)
        {
            case TX_REG_ADDRESS_MODE:
                if (RXByteCtr)
                {
                    MasterMode = RX_DATA_MODE;   // Need to start receiving now
                    //Send Dummy To Start
                    __delay_cycles(2000000);
                    //SendUCA0Data(DUMMY);
                }
                else
                {
                    MasterMode = TX_DATA_MODE;        // Continue to transmision with the data in Transmit Buffer
                    //Send First
                    SendUCA0Data(TransmitBuffer[TransmitIndex++]);
                    TXByteCtr--;
                }
                break;

            case TX_DATA_MODE:
                if (TXByteCtr)
                {
                  SendUCA0Data(TransmitBuffer[TransmitIndex++]);
                  TXByteCtr--;
                }
                else
                {
                  //Done with transmission
                  MasterMode = IDLE_MODE;
                  __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
                }
                break;

            case RX_DATA_MODE:
                if (RXByteCtr)
                {
                    ReceiveBuffer[ReceiveIndex++] = uca0_rx_val;
                    //Transmit a dummy
                    RXByteCtr--;
                }
                if (RXByteCtr == 0)
                {
                    MasterMode = IDLE_MODE;
                    __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
                }
                else
                {
                    SendUCA0Data(DUMMY);
                }
                break;

            default:
                __no_operation();
                break;
        }
        __delay_cycles(1000);
        break;
    case 4:break;                             // Vector 4 - TXIFG
    default: break;
  }
}
