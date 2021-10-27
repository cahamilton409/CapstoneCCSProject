/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

#include "driverlib.h"

//******************************************************************************
//!
//!   Empty Project that includes driverlib
//!
//******************************************************************************


//#define X1_PORT          GPIO_PORT_6

#define X1_PORT GPIO_PORT_P6
#define X1_PIN  GPIO_PIN0
#define X1_HIGH GPIO_setOutputHighOnPin(X1_PORT, X1_PIN)
#define X1_LOW  GPIO_setOutputLowOnPin(X1_PORT, X1_PIN)

#define X2_PORT GPIO_PORT_P6
#define X2_PIN  GPIO_PIN1
#define X2_HIGH GPIO_setOutputHighOnPin(X2_PORT, X2_PIN)
#define X2_LOW  GPIO_setOutputLowOnPin(X2_PORT, X2_PIN)

#define X3_PORT GPIO_PORT_P6
#define X3_PIN  GPIO_PIN2
#define X3_HIGH GPIO_setOutputHighOnPin(X3_PORT, X3_PIN)
#define X3_LOW  GPIO_setOutputLowOnPin(X3_PORT, X3_PIN)

#define X4_PORT GPIO_PORT_P6
#define X4_PIN  GPIO_PIN3
#define X4_HIGH GPIO_setOutputHighOnPin(X4_PORT, X4_PIN)
#define X4_LOW  GPIO_setOutputLowOnPin(X4_PORT, X4_PIN)


#define Y1_PORT GPIO_PORT_P6
#define Y1_PIN  GPIO_PIN4
#define Y1_IN   GPIO_getInputPinValue(Y1_PORT, Y1_PIN)

#define Y2_PORT GPIO_PORT_P7
#define Y2_PIN  GPIO_PIN0
#define Y2_IN   GPIO_getInputPinValue(Y2_PORT, Y2_PIN)

#define Y3_PORT GPIO_PORT_P3
#define Y3_PIN  GPIO_PIN6
#define Y3_IN   GPIO_getInputPinValue(Y3_PORT, Y3_PIN)

#define Y4_PORT GPIO_PORT_P3
#define Y4_PIN  GPIO_PIN5
#define Y4_IN   GPIO_getInputPinValue(Y4_PORT, Y4_PIN)


//#define X_1    GPIO
//#define X_2    RB1
//#define X_3    RB2
//#define X_4    RB3
//#define Y_1    RB4
//#define Y_2    RB5
//#define Y_3    RB6
//#define Y_4    RB7
//#define Keypad_PORT_Direction     TRISB

void InitKeypad(void);
char switch_press_scan(void);
char keypad_scanner(void);



//uint8_t y1, y2, y3, y4;
char key;
void main (void)
{
    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    InitKeypad();
    X1_HIGH;
    X2_HIGH;
    X3_LOW;
    X4_LOW;
    while (1) {
        key = switch_press_scan();
//        y1 = Y1_IN;
//        y2 = Y2_IN;
//        y3 = Y3_IN;
//        y4 = Y4_IN;
    }
}

char switch_press_scan(void)                       // Get key from user
{
            char key = 'n';              // Assume no key pressed
            while(key=='n')              // Wait untill a key is pressed
            key = keypad_scanner();   // Scan the keys again and again
            return key;                  //when key pressed then return its value
}

void InitKeypad(void)
{
    GPIO_setOutputLowOnPin(Y1_PORT, Y1_PIN);
    GPIO_setOutputLowOnPin(Y2_PORT, Y2_PIN);
    GPIO_setOutputLowOnPin(Y3_PORT, Y3_PIN);
    GPIO_setOutputLowOnPin(Y4_PORT, Y4_PIN);
    X1_LOW;
    X2_LOW;
    X3_LOW;
    X4_LOW;

    GPIO_setAsOutputPin(X1_PORT, X1_PIN);
    GPIO_setAsOutputPin(X2_PORT, X2_PIN);
    GPIO_setAsOutputPin(X3_PORT, X3_PIN);
    GPIO_setAsOutputPin(X4_PORT, X4_PIN);

    GPIO_setAsInputPinWithPullUpResistor(Y1_PORT, Y1_PIN);
    GPIO_setAsInputPinWithPullUpResistor(Y2_PORT, Y2_PIN);
    GPIO_setAsInputPinWithPullUpResistor(Y3_PORT, Y3_PIN);
    GPIO_setAsInputPinWithPullUpResistor(Y4_PORT, Y4_PIN);

}

char keypad_scanner(void)
{
    int i;
    X1_LOW;
    X2_HIGH;
    X3_HIGH;
    X4_HIGH;
    if (Y1_IN == 0) {for(i=10000; i>0; i--); while (Y1_IN==0); return '1'; }
    if (Y2_IN == 0) {for(i=10000; i>0; i--); while (Y2_IN==0); return '2'; }
    if (Y3_IN == 0) {for(i=10000; i>0; i--); while (Y3_IN==0); return '3'; }
    if (Y4_IN == 0) {for(i=10000; i>0; i--); while (Y4_IN==0); return 'A'; }

    X1_HIGH;
    X2_LOW;
    X3_HIGH;
    X4_HIGH;
    if (Y1_IN == 0) {for(i=10000; i>0; i--); while (Y1_IN==0) return '4'; }
    if (Y2_IN == 0) {for(i=10000; i>0; i--); while (Y2_IN==0) return '5'; }
    if (Y3_IN == 0) {for(i=10000; i>0; i--); while (Y3_IN==0) return '6'; }
    if (Y4_IN == 0) {for(i=10000; i>0; i--); while (Y4_IN==0) return 'B'; }

    X1_HIGH;
    X2_HIGH;
    X3_LOW;
    X4_HIGH;
    if (Y1_IN == 0) {for(i=10000; i>0; i--); while (Y1_IN==0) return '7'; }
    if (Y2_IN == 0) {for(i=10000; i>0; i--); while (Y2_IN==0) return '8'; }
    if (Y3_IN == 0) {for(i=10000; i>0; i--); while (Y3_IN==0) return '9'; }
    if (Y4_IN == 0) {for(i=10000; i>0; i--); while (Y4_IN==0) return 'C'; }

    X1_HIGH;
    X2_HIGH;
    X3_HIGH;
    X4_LOW;
    if (Y1_IN == 0) {for(i=10000; i>0; i--); while (Y1_IN==0) return '*'; }
    if (Y2_IN == 0) {for(i=10000; i>0; i--); while (Y2_IN==0) return '0'; }
    if (Y3_IN == 0) {for(i=10000; i>0; i--); while (Y3_IN==0) return '#'; }
    if (Y4_IN == 0) {for(i=10000; i>0; i--); while (Y4_IN==0) return 'D'; }


    return 'n';
}
