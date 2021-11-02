/*
 * KeyPad.h
 *
 *  Created on: Oct 27, 2021
 *      Author: Chris
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <key_press.h>
#include "driverlib.h"

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

Button switch_press_scan(void);

void InitKeypad(void);

Button keypad_scanner(void);




#endif /* KEYPAD_H_ */
