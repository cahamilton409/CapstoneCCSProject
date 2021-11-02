#include "driverlib.h"

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    USCI_A_SPI_initMasterParam config = {0};
    config.selectClockSource = USCI_A_SPI_CLOCKSOURCE_SMCLK;
    config.clockSourceFrequency = UCS_getSMCLK();
    config.desiredSpiClock = 500000;
    config.msbFirst = USCI_A_SPI_MSB_FIRST;
    config.clockPolarity = USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
    config.clockPhase = USCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    // Start up USCI_A0
    bool status = USCI_A_SPI_initMaster(USCI_A0_BASE, &config);
    uint8_t sendData = 0x10;

    if (STATUS_FAIL == status) {
        return 0;
    }

    //start up the SPI
    USCI_A_SPI_enable(USCI_A0_BASE);

    //enable interrupt

    USCI_A_SPI_clearInterrupt(USCI_A0_BASE, USCI_A_SPI_RECEIVE_INTERRUPT);
    USCI_A_SPI_clearInterrupt(USCI_A0_BASE, USCI_A_SPI_TRANSMIT_INTERRUPT);

    while (true) {
            //wait for slave to init
            __delay_cycles(100);

            //dummy data to send:
            //ensure buffer ready
            //while (!USCI_A_SPI_getInterruptStatus(USCI_A0_BASE, UCTXIFG));

            //transmit data
            USCI_A_SPI_transmitData(USCI_A0_BASE, sendData);
    }

    return 0;
}
