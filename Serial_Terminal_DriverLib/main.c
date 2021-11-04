
#include "driverlib.h"
#include "msp430.h"

#include "UART0.h"

#include <stdbool.h>
#include <stdint.h>


//******************************************************************************
// Device Initialization *******************************************************
//******************************************************************************

void initClocks(uint32_t mclkFreq)
{
    UCS_initClockSignal(
       UCS_FLLREF,
       UCS_REFOCLK_SELECT,
       UCS_CLOCK_DIVIDER_1);

    UCS_initClockSignal(
       UCS_ACLK,
       UCS_REFOCLK_SELECT,
       UCS_CLOCK_DIVIDER_1);

    UCS_initFLLSettle(
        mclkFreq/1000,
        mclkFreq/32768);
}

//******************************************************************************
// Main ************************************************************************
// Enters LPM0 if SMCLK is used and waits for UART interrupts. If ACLK is used *
// then the device will enter LPM3 mode instead. The UART RX interrupt handles *
// the received character and echoes it.                                       *
//******************************************************************************


//uint32_t i;
uint32_t count = 0;
char text[] = "I am an MSP432 lol\r\n";
char clearscreen[] = "\r\n\n\n\n\n\n\n\n\n\n";
void ser_output(char *str);
void initUART(void);

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop Watchdog

  PMM_setVCore(PMM_CORE_LEVEL_2); // Minumum Vcore setting required for the USB API is PMM_CORE_LEVEL_2 .
  initClocks(16000000);
//  initUART();
  UART0_Init();
//  volatile uint32_t i, j;        // volatile to prevent optimization

  while(1){
//      ser_output(text);
//      UART0_OutUDec(count);

      UART0_OutString(text);
//      for(i=10000000; i>0; i--) {
//      }
//      count++;
//      UART0_OutString(clearscreen);

  }
}




