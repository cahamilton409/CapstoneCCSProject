/*
 * Audio.c
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 */
#include <stdint.h>
#include "msp.h"
#include "Clock.h"
#include "TExaS.h"

volatile uint8_t DataA; // Data from Pin A
volatile uint8_t DataB; // Data from Pin B

void Audio_Init(void) {
    P4->SEL0 &= ~0x01;
    P4->SEL1 &= ~0x01;    //  P4.0 as GPIO
    P4->DIR &= ~0x01;      //  make P4.0 out
    
    P3->SEL0 &= ~0x80;
    P3->SEL1 &= ~0x80;    //  P4.0 as GPIO
    P3->DIR &= ~0x80;      //  make P4.0 out
    return;
}


