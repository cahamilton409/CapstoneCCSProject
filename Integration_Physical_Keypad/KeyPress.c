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

// TODO This variable will be associated with flash memory and may be moved.
volatile Language CurrentLanguage;
volatile uint8_t keySendComplete = TRUE;
volatile KeyPressInfoType KeyPressInfo;


void KeyPressInit() {
    KeyPressInfo.KeyPressDetected = FALSE;
    CurrentLanguage = Spanish; // This will need to be changed to be the last language used.
}

void ChangeCurrentLanguage(Button SelectedTab) {
    if (SelectedTab == FrenchTab) {
        CurrentLanguage = French;
    }
    else if (SelectedTab == SpanishTab) {
        CurrentLanguage = Spanish;
    }
    else {
        while(1) {}; // Wait in an infinite loop because this function should not have been called.
    }
}

// TODO This function will likely interact with the stored flash memory, and may be moved.
uint8_t GetKeyFromButton(Button PressedKey) {
    if (CurrentLanguage == Spanish) {
        switch(PressedKey) {
            case Key1:
                return SpanishCharacters[0];
            case Key2:
                return SpanishCharacters[1];
            case Key3:
                return SpanishCharacters[2];
            case Key4:
                return SpanishCharacters[3];
            case Key5:
                return SpanishCharacters[4];
            case Key6:
                return SpanishCharacters[5];
            case Key7:
                return SpanishCharacters[6];
            case Key8:
                return SpanishCharacters[7];
            case Key9:
                return SpanishCharacters[8];
            default:
                return QUESTION_MARK_INVERTED;
        }
    }

    if (CurrentLanguage == French) {
        switch(PressedKey) {
            case Key1:
                return FrenchCharacters[0];
            case Key2:
                return FrenchCharacters[1];
            case Key3:
                return FrenchCharacters[2];
            case Key4:
                return FrenchCharacters[3];
            case Key5:
                return FrenchCharacters[4];
            case Key6:
                return FrenchCharacters[5];
            case Key7:
                return FrenchCharacters[6];
            case Key8:
                return FrenchCharacters[7];
            case Key9:
                return FrenchCharacters[8];

            default:
                return QUESTION_MARK_INVERTED;
        }
    }
    return QUESTION_MARK_INVERTED;
}


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

// TODO This function will interact with the flash memory and may be moved.
void MoveKeyToFront(Button PressedKey) {
    return;
}





