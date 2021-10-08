/*
 * KeyPress.c
 *
 *  Created on: Oct 7, 2021
 *      Author: Chris
 */

#include "KeyPress.h"

#include <stdint.h>
#include <stdlib.h>

#include "USB_API/USB_Common/usb.h"
#include "USB_app/keyboard.h"

const uint8_t SpanishCharacters[NUM_SPANISH_CHARACTERS] = {
    A_RIGHT_ACCENT,
    E_RIGHT_ACCENT,
    I_RIGHT_ACCENT,
    O_RIGHT_ACCENT,
    U_RIGHT_ACCENT,
    U_DIAERESIS,
    N_TENUTO,
    QUESTION_MARK_INVERTED,
    EXCLAMATION_POINT_INVERTED};

const uint8_t FrenchCharacters [NUM_FRENCH_CHARACTERS] = {
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

void SpecialKeyPress(uint8_t c) {
    // HOLD DOWN THE ALT KEY.
    Keyboard_press(KEY_RIGHT_ALT);
    while(!keySendComplete);
    keySendComplete = FALSE;

    // PRESS THE SPECIFIED KEY.
    Keyboard_press(c);
    while(!keySendComplete);
    keySendComplete = FALSE;
    Keyboard_release(c);
    while(!keySendComplete);
    keySendComplete = FALSE;

    // RELEASE THE ALT KEY.
    Keyboard_release(KEY_RIGHT_ALT);
    while(!keySendComplete);
    keySendComplete = FALSE;
}






