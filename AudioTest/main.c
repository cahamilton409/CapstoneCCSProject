/*
 * Audio.c
 *
 *  Created on: Sep 28, 2021
 *  Author: Rohan
 *
 */
#include <stdint.h>
#include <stdio.h>
#include "driverlib.h"
#include "msp430.h"
#include "Clock.h"
#include "UART0.h"

uint8_t aLastState; // Previous state (0 or 1) of Pin A
uint8_t aState; // Current state of Pin A (0 or 1)
uint8_t bState; // Current state of Pin B (0 or 1)
uint8_t volume; // A test variable to track whether turning the encoder increases or decreases this value

/*
 * Description: Initializes the input + output pins, initializes global variables to track
 * rotary encoder state
 * Inputs: None
 * Outputs: None
 */
void Audio_Init(void) {
    GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN0); // P4.0 is an output
    GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN7); // P3.7 is an output
    Clock_Delay1us(1000);
    aState = 0;
    bState = 0;
    volume = 100;
    return;
}

/* Currently reads in the signals from the rotary encoder, determines which direction
*  the encoder is turning and adjusts the volume as necessary
*/

int main(void){
    WDTCTL = WDTPW | WDTHOLD;                 // Stop Watchdog

    PMM_setVCore(PMM_CORE_LEVEL_3); // Minumum Vcore setting required for the USB API is PMM_CORE_LEVEL_2 .
    initClocks(25000000);
    Audio_Init();
    UART0_Init();
    while(1){
        aState = GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN0); // Read in the current state of Pin A
        bState = GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN7);
//        UART0_OutString(" A State: ");
//        UART0_OutUDec(aState);
//        Clock_Delay1ms(1000);
//        UART0_OutString(" B State: ");
//        UART0_OutUDec(bState);
//        Clock_Delay1ms(1000);
//        UART0_OutString("\r\n");

        if(aState != aLastState){
            bState = GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN7);
            if(bState != aState){
                // The rotary encoder is moving clockwise, increase volume
                volume = volume + 1;
                UART0_OutString("Increasing!");
            }
            else{
                // The rotary encoder is moving counterclockwise, decrease volume
                volume = volume - 1;
                UART0_OutString("Decreasing!");
            }
            aLastState = aState;
            UART0_OutString("\r\n");
        }
    }
}

//int main2(void){
//    WDTCTL = WDTPW | WDTHOLD;                 // Stop Watchdog
//
//    PMM_setVCore(PMM_CORE_LEVEL_3); // Minumum Vcore setting required for the USB API is PMM_CORE_LEVEL_2 .
//    initClocks(25000000);
//    Audio_Init();
//    UART0_Init();
//    volatile uint32_t i;        // volatile to prevent optimization
//
//    while(1){
//        UART0_OutUDec(count);
//        UART0_OutString(text);
//        Clock_Delay1ms(1000);
//        count++;
//        UART0_OutString(clearscreen);
//    }
//}
