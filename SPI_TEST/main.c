#include "driverlib.h"

int main(void) {
    // Start up USCI_A0
    status = SPI_masterInit(USCI_A0_BASE, SMCLK, CLK_getSMClk(),
                            SPICLK, MSB_FIRST,
                            CLOCK_POLARITY_INACTIVITYHIGH
                            );

    if (STATUS_FAIL == returnValue) {
        return;
    }

    //start up the SPI
    SPI_enable(USCI_A0_BASE);

    //enable interrupt
    SPI_enableInterrupt(USCI_A0_BASE, UCRXIE);

    //wait for slave to init
    __delay_cycles(100);

    //dummy data to send:
    sendData = 0x01;

    //ensure buffer ready
    while (!SPI_interruptStatus(USCI_A0_BASE, UCTXIFG));

    //transmit data
    SPI_transmitData(USCI_A0_BASE, sendData);

    return 0;
}
