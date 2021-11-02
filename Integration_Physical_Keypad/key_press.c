/*
 * KeyPress.c
 *
 *  Created on: Oct 7, 2021
 *      Author: Chris
 */

#include <key_press.h>
#include <stdint.h>
#include <stdlib.h>

#include "driverlib.h"
#include "USB_API/USB_Common/usb.h"
#include "USB_app/keyboard.h"

const uint8_t g_spanish_characters[NUM_SPANISH_CHARACTERS] = {
    A_RIGHT_ACCENT,
    E_RIGHT_ACCENT,
    I_RIGHT_ACCENT,
    O_RIGHT_ACCENT,
    U_RIGHT_ACCENT,
    U_DIAERESIS,
    N_TENUTO,
    QUESTION_MARK_INVERTED,
    EXCLAMATION_POINT_INVERTED};

const uint8_t g_french_characters [NUM_FRENCH_CHARACTERS] = {
    A_LEFT_ACCENT,
    A_CARET,
    E_RIGHT_ACCENT,
    E_LEFT_ACCENT,
    E_CARET,
    E_DIAERESIS,
    I_DIAERESIS,
    I_CARET,
    O_CARET,
    U_LEFT_ACCENT,
    U_CARET,
    U_DIAERESIS,
    C_CEDILLA,
    Y_DIAERESIS,
    AE,
    OE};

// TODO This variable will be associated with flash memory and may be moved.
volatile language_t g_current_language;
volatile uint8_t g_key_send_complete = TRUE;
volatile key_press_info_type g_key_press_info;


void key_press_init() {
    g_key_press_info.key_press_detected = FALSE;
    g_current_language = Spanish; // This will need to be changed to be the last language used.

    // Use LEDs for tracking the current language
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN7);
    update_language_led_indicators();

}

void change_current_language(button_t selected_tab) {
    if (selected_tab == french_tab) {
        g_current_language = French;
    }
    else if (selected_tab == spanish_tab) {
        g_current_language = Spanish;
    }
    update_language_led_indicators();


}

// TODO This function will likely interact with the stored flash memory, and may be moved.
uint8_t get_key_from_button(button_t pressed_key) {
    if (g_current_language == Spanish) {
        return g_spanish_characters[pressed_key];
    }

    if (g_current_language == French) {
        return g_french_characters[pressed_key];
    }
    return QUESTION_MARK_INVERTED;
}


void special_key_press(uint8_t mapped_character) {
    // HOLD DOWN THE ALT KEY.
    Keyboard_press(KEY_RIGHT_ALT);
    while(!g_key_send_complete);
    g_key_send_complete = FALSE;

    // PRESS THE SPECIFIED KEY.
    Keyboard_press(mapped_character);
    while(!g_key_send_complete);
    g_key_send_complete = FALSE;
    Keyboard_release(mapped_character);
    while(!g_key_send_complete);
    g_key_send_complete = FALSE;

    // RELEASE THE ALT KEY.
    Keyboard_release(KEY_RIGHT_ALT);
    while(!g_key_send_complete);
    g_key_send_complete = FALSE;
}

// TODO This function will interact with the flash memory and may be moved.
void MoveKeyToFront(button_t pressed_key) {
    return;
}

void update_language_led_indicators(void){
    if (g_current_language == Spanish) {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);
    }
    else {
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN7);
    }
}



