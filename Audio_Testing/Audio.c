/*
 * Audio.c
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 *
 */
#include <stdint.h>
#include "msp.h"
#include "Clock.h"
#include "TExaS.h"

uint8_t aLastState; // Previous state (0 or 1) of Pin A
uint8_t aState; // Current state of Pin A (0 or 1)
utin8_t bState; // Current state of Pin B (0 or 1)
uint8_t volume; // A test variable to track whether turning the encoder increases or decreases this value 

// Initializes input ports and variables needed to keep track of the rotary encoder states
void Audio_Init(void) {
    P4->SEL0 &= ~0x01;
    P4->SEL1 &= ~0x01;    //  P4.0 as GPIO
    P4->DIR &= ~0x00;      //  make P4.0 out

    P3->SEL0 &= ~0x80;
    P3->SEL1 &= ~0x80;    //  P3.7 as GPIO
    P3->DIR &= ~0x80;      //  make P3.7 in

    Clock_Delay1us(1000);
    aLastState = (P4->IN); // Get the current state of Pin A
    aState = 0;
    bState = 0;
    volume = 0;
    return;
}

/* Currently reads in the signals from the rotary encoder, determines which direction
*  the encoder is turning and adjusts the volume as necessary 
*/
int main(void){
    Clock_Init48MHz();
    Audio_Init();
    TExaS_Init(LOGICANALYZER_P4);
    TExaS_Init(LOGICANALYZER_P3);
    while(1){
        aState = (P4->IN); // Read in the current state of Pin A
        if(aState != aLastState){
            bState = (P3->IN);
            if(bState != aState){
                // The rotary encoder is moving clockwise, increase volume
                volume = volume + 1; 
            }
            else{
                // The rotary encoder is moving counterclockwise, decrease volume
                volume = volume - 1;
            }
            aLastState = aState;
        }
    }
}
