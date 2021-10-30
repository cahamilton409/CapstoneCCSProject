#include "KeyPad.h"
#include "KeyPress.h"
#include "driverlib.h"


Button switch_press_scan(void)                       // Get key from user
{
            Button key = NoKey;              // Assume no key pressed
            while(key==NoKey)              // Wait untill a key is pressed
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

Button keypad_scanner(void)
{
    uint32_t i;

    X1_LOW;
    X2_HIGH;
    X3_HIGH;
    X4_HIGH;
    if (Y1_IN == 0) {for(i=10000; i>0; i--); while (Y1_IN==0); return Key1; }
    if (Y2_IN == 0) {for(i=10000; i>0; i--); while (Y2_IN==0); return Key2; }
    if (Y3_IN == 0) {for(i=10000; i>0; i--); while (Y3_IN==0); return Key3; }
    if (Y4_IN == 0) {for(i=10000; i>0; i--); while (Y4_IN==0); return SpanishTab; }

    X1_HIGH;
    X2_LOW;
    X3_HIGH;
    X4_HIGH;
    if (Y1_IN == 0) {for(i=10000; i>0; i--); while (Y1_IN==0); return Key4; }
    if (Y2_IN == 0) {for(i=10000; i>0; i--); while (Y2_IN==0); return Key4; }
    if (Y3_IN == 0) {for(i=10000; i>0; i--); while (Y3_IN==0); return Key6; }
    if (Y4_IN == 0) {for(i=10000; i>0; i--); while (Y4_IN==0); return FrenchTab; }

    X1_HIGH;
    X2_HIGH;
    X3_LOW;
    X4_HIGH;
    if (Y1_IN == 0) {for(i=10000; i>0; i--); while (Y1_IN==0); return Key7; }
    if (Y2_IN == 0) {for(i=10000; i>0; i--); while (Y2_IN==0); return Key8; }
    if (Y3_IN == 0) {for(i=10000; i>0; i--); while (Y3_IN==0); return Key9; }
    if (Y4_IN == 0) {for(i=10000; i>0; i--); while (Y4_IN==0); return NoKey; }

    X1_HIGH;
    X2_HIGH;
    X3_HIGH;
    X4_LOW;
    if (Y1_IN == 0) {for(i=10000; i>0; i--); while (Y1_IN==0); return NoKey; }
    if (Y2_IN == 0) {for(i=10000; i>0; i--); while (Y2_IN==0); return NoKey; }
    if (Y3_IN == 0) {for(i=10000; i>0; i--); while (Y3_IN==0); return NoKey; }
    if (Y4_IN == 0) {for(i=10000; i>0; i--); while (Y4_IN==0); return NoKey; }

    return NoKey;
}