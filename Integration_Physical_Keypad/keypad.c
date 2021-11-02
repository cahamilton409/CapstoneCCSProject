#include <key_press.h>
#include <keypad.h>
#include "driverlib.h"


void keypad_init(void)
{
    // SET ALL OUTPUTS INITIALLY LOW.
    GPIO_setOutputLowOnPin(Y1_PORT, Y1_PIN);
    GPIO_setOutputLowOnPin(Y2_PORT, Y2_PIN);
    GPIO_setOutputLowOnPin(Y3_PORT, Y3_PIN);
    GPIO_setOutputLowOnPin(Y4_PORT, Y4_PIN);
    GPIO_setOutputLowOnPin(X1_PORT, X1_PIN);
    GPIO_setOutputLowOnPin(X2_PORT, X2_PIN);
    GPIO_setOutputLowOnPin(X3_PORT, X3_PIN);
    GPIO_setOutputLowOnPin(X4_PORT, X4_PIN);

    // CONFIGURE THE ROWS AS OUTPUTS.
    GPIO_setAsOutputPin(X1_PORT, X1_PIN);
    GPIO_setAsOutputPin(X2_PORT, X2_PIN);
    GPIO_setAsOutputPin(X3_PORT, X3_PIN);
    GPIO_setAsOutputPin(X4_PORT, X4_PIN);

    // CONFIGURE THE COLUMNS AS INPUTS WITH PULL-UP RESISTORS.
    GPIO_setAsInputPinWithPullUpResistor(Y1_PORT, Y1_PIN);
    GPIO_setAsInputPinWithPullUpResistor(Y2_PORT, Y2_PIN);
    GPIO_setAsInputPinWithPullUpResistor(Y3_PORT, Y3_PIN);
    GPIO_setAsInputPinWithPullUpResistor(Y4_PORT, Y4_PIN);
}

button_t switch_press_scan(void)
{
            button_t key = no_key;
            while(key==no_key)
            key = keypad_scanner();
            return key;
}

button_t keypad_scanner(void)
{
    uint32_t i;

    // SCAN THE FIRST ROW OF KEYS.
    X1_LOW;
    X2_HIGH;
    X3_HIGH;
    X4_HIGH;
    if (Y1_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS;i>0; i--);
        while (Y1_IN==0);
        return key1;}
    if (Y2_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y2_IN==0);
        return key2; }
    if (Y3_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y3_IN==0);
        return key3; }
    if (Y4_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y4_IN==0);
        return spanish_tab; }

    // SCAN THE SECOND ROW OF KEYS.
    X1_HIGH;
    X2_LOW;
    X3_HIGH;
    X4_HIGH;
    if (Y1_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y1_IN==0);
        return key4; }
    if (Y2_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y2_IN==0);
        return key5; }
    if (Y3_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y3_IN==0);
        return key6; }
    if (Y4_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y4_IN==0);
        return french_tab; }

    // SCAN THE THIRD ROW OF KEYS.
    X1_HIGH;
    X2_HIGH;
    X3_LOW;
    X4_HIGH;
    if (Y1_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y1_IN==0);
        return key7; }
    if (Y2_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y2_IN==0);
        return key8; }
    if (Y3_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y3_IN==0);
        return key9; }
    if (Y4_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y4_IN==0);
        return no_key; }

    // SCAN THE FOURTH ROW OF KEYS.
    X1_HIGH;
    X2_HIGH;
    X3_HIGH;
    X4_LOW;
    if (Y1_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y1_IN==0);
        return no_key; }
    if (Y2_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y2_IN==0);
        return no_key; }
    if (Y3_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y3_IN==0);
        return no_key; }
    if (Y4_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        while (Y4_IN==0);
        return no_key; }

    return no_key;
}
