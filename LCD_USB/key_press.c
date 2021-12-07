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

#include "flash_memory.h"

//
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

const uint8_t g_greek_characters [NUM_GREEK_CHARACTERS] = {
    PHI,
    OMEGA_UPPERCASE,
    DELTA,
    LAMBDA,
    MU,
    PI,
    THETA,
    SIGMA,
    OMEGA_LOWERCASE};


volatile language_t g_current_language;
volatile uint8_t g_key_send_complete = TRUE;
volatile key_press_info_type g_key_press_info;
volatile uint8_t g_spanish_mappings[NUM_SPANISH_CHARACTERS];
volatile uint8_t g_french_mappings[NUM_FRENCH_CHARACTERS];
volatile uint8_t g_greek_mappings[NUM_GREEK_CHARACTERS];

// Initializes the device for special key presses.
void key_press_init() {
    g_key_press_info.b_key_press_detected = FALSE;
    g_current_language = spanish;
}

// Changes the current language based on the button that was just pressed.
void change_current_language(button_t selected_tab) {
    if (selected_tab == french_tab)
    {
        if (g_current_language == french_page1)
        {
            g_current_language = french_page2;
        }
        else
        {
        g_current_language = french_page1;
        }
    }
    else if (selected_tab == spanish_tab)
    {
        g_current_language = spanish;
    }
    else if (selected_tab == greek_tab)
    {
        g_current_language = greek;
    }
}

// Get the character that will to be sent based on which key was pressed.
uint8_t get_key_from_button(button_t pressed_key) {
    if (g_current_language == spanish)
    {
        return g_spanish_mappings[pressed_key];
    }

    if (g_current_language == french_page1)
    {
        return g_french_mappings[pressed_key];
    }

    if (g_current_language == french_page2)
    {
        if ((pressed_key + 9) < NUM_FRENCH_CHARACTERS)
        {
            return g_french_mappings[pressed_key + 9];
        }
    }

    if (g_current_language == greek) {
        return g_greek_mappings[pressed_key];
    }

    return 0;
}

// Send a character along with the "Alt" modifier to type the special character associated with the character.
void special_key_press(uint8_t mapped_character) {
    // HOLD DOWN THE ALT KEY.
    Keyboard_press(KEY_RIGHT_ALT);
    while(!g_key_send_complete)
    {
    }
    g_key_send_complete = FALSE;

    // PRESS THE SPECIFIED KEY.
    Keyboard_press(mapped_character);
    while(!g_key_send_complete)
    {
    }
    g_key_send_complete = FALSE;
    Keyboard_release(mapped_character);
    while(!g_key_send_complete)
    {
    }
    g_key_send_complete = FALSE;

    // RELEASE THE ALT KEY.
    Keyboard_release(KEY_RIGHT_ALT);
    while(!g_key_send_complete)
    {
    }
    g_key_send_complete = FALSE;
}

// Rearrange the keys so that the selected key is displayed first.
// TODO This function will interact with the flash memory and may be moved.
void move_key_to_front(button_t pressed_key) {
    uint8_t i;
    // SHIFT THE SPANISH MAPPINGS IF THE CURRENT LANGUAGE IS SPANISH.
    if (g_current_language == spanish) {
        // CREATE A COPY OF THE MAPPING.
        uint8_t old_mappings[NUM_SPANISH_CHARACTERS];
        for (i = 0; i < NUM_SPANISH_CHARACTERS; i++) {
            old_mappings[i] = g_spanish_mappings[i];
        }

        // SHIFT THE MAPPING BASED ON THE SELECTED KEY.
        g_spanish_mappings[0] = old_mappings[pressed_key];
        button_t key_index;
        for (key_index = key1; key_index < pressed_key; key_index++) {
            g_spanish_mappings[key_index+1] = old_mappings[key_index];
        }
    }

    // SHIFT THE FRENCH MAPPINGS IF THE CURRENT LANGUAGE IS FRENCH.
    if ((g_current_language == french_page1) || (g_current_language == french_page2)) {
        // CREATE A COPY OF THE MAPPING.
        uint8_t old_mappings[NUM_FRENCH_CHARACTERS];
        for (i = 0; i < NUM_FRENCH_CHARACTERS; i++) {
            old_mappings[i] = g_french_mappings[i];
        }

        // SHIFT THE MAPPING BASED ON THE SELECTED KEY.
        // Scale the index if it is on the second page.
        uint8_t key_index = (uint8_t) pressed_key;
        if (g_current_language == french_page2)
        {
            key_index += 9;
        }
        // Check to make sure the index is not out of bounds.
        if (key_index >= NUM_FRENCH_CHARACTERS)
        {
            return;
        }
        g_french_mappings[0] = old_mappings[key_index];
        for (i = 0; i < key_index; i++) {
            g_french_mappings[i+1] = old_mappings[i];
        }
    }

    // SHIFT THE GREEK MAPPINGS OF THE CURRENT LANGUAGE IS GREEK.
    if (g_current_language == greek) {
        // CREATE A COPY OF THE MAPPING.
        uint8_t old_mappings[NUM_GREEK_CHARACTERS];
        for (i = 0; i < NUM_GREEK_CHARACTERS; i++) {
            old_mappings[i] = g_greek_mappings[i];
        }

        // SHIFT THE MAPPING BASED ON THE SELECTED KEY.
        g_greek_mappings[0] = old_mappings[pressed_key];
        button_t key_index;
        for (key_index = key1; key_index < pressed_key; key_index++) {
            g_greek_mappings[key_index+1] = old_mappings[key_index];
        }
    }


}
