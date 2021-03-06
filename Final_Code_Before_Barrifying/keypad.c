#include <key_press.h>
#include <keypad.h>
#include "driverlib.h"

volatile uint32_t g_time_elapsed;

// Configure the GPIO ports for the physical keypad.
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

// Probe the keys until a is pressed and return the key that was pressed.
button_t switch_press_scan(void)
{
            button_t key = no_key;
            while(key==no_key)
            key = keypad_scanner();
            return key;
}

// Probe each row of keys individually and return if a key press is detected.
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
        g_time_elapsed = 0;
        while (Y1_IN==0) {
            g_time_elapsed++;
        }
        return key1;}
    if (Y2_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y2_IN==0) {
            g_time_elapsed++;
        }
        return key2; }
    if (Y3_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y3_IN==0) {
            g_time_elapsed++;
        }
        return key3; }
    if (Y4_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y4_IN==0) {
            g_time_elapsed++;
        }
        return spanish_tab; }

    // SCAN THE SECOND ROW OF KEYS.
    X1_HIGH;
    X2_LOW;
    X3_HIGH;
    X4_HIGH;
    if (Y1_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y1_IN==0) {
            g_time_elapsed++;
        }
        return key4; }
    if (Y2_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y2_IN==0) {
            g_time_elapsed++;
        }
        return key5; }
    if (Y3_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y3_IN==0) {
            g_time_elapsed++;
        }
        return key6; }
    if (Y4_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y4_IN==0) {
            g_time_elapsed++;
        }
        return french_tab; }

    // SCAN THE THIRD ROW OF KEYS.
    X1_HIGH;
    X2_HIGH;
    X3_LOW;
    X4_HIGH;
    if (Y1_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y1_IN==0) {
            g_time_elapsed++;
        }
        return key7; }
    if (Y2_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y2_IN==0) {
            g_time_elapsed++;
        }
        return key8; }
    if (Y3_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y3_IN==0) {
            g_time_elapsed++;
        }
        return key9; }
    if (Y4_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y4_IN==0) {
            g_time_elapsed++;
        }
        return no_key; }

    // SCAN THE FOURTH ROW OF KEYS.
    X1_HIGH;
    X2_HIGH;
    X3_HIGH;
    X4_LOW;
    if (Y1_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y1_IN==0) {
            g_time_elapsed++;
        }
        return no_key; }
    if (Y2_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y2_IN==0) {
            g_time_elapsed++;
        }
        return no_key; }
    if (Y3_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y3_IN==0) {
            g_time_elapsed++;
        }
        return no_key; }
    if (Y4_IN == 0) {
        for(i=DEBOUNCE_DELAY_IN_TICKS; i>0; i--);
        g_time_elapsed = 0;
        while (Y4_IN==0) {
            g_time_elapsed++;
        }
        return no_key; }

    return no_key;
}
