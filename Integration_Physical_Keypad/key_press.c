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

    // Use LEDs for tracking the current language
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN7);
    UpdateLanguageLedIndicators();

}

void ChangeCurrentLanguage(Button SelectedTab) {
    if (SelectedTab == FrenchTab) {
        CurrentLanguage = French;
    }
    else if (SelectedTab == SpanishTab) {
        CurrentLanguage = Spanish;
    }
    UpdateLanguageLedIndicators();


}

// TODO This function will likely interact with the stored flash memory, and may be moved.
uint8_t GetKeyFromButton(Button PressedKey) {
    if (CurrentLanguage == Spanish) {
        return SpanishCharacters[PressedKey];
    }

    if (CurrentLanguage == French) {
        return FrenchCharacters[PressedKey];
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

void UpdateLanguageLedIndicators(void){
    if (CurrentLanguage == Spanish) {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);
    }
    else {
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN7);
    }
}



