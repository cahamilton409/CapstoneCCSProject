
#include "driverlib.h"


uint8_t aState; // Current state of Pin A (0 or 1)
uint8_t bState; // Current state of Pin B (0 or 1)
void main (void)
{
    //Stop WDT
    WDT_A_hold(WDT_A_BASE);

    GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN0); // P4.0 is an input
    GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN7); // P3.7 is an input

    while(1) {
        aState = GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN7);
        bState = GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN0);

    }
}

