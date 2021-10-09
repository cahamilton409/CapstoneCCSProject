/*
 * Keypress.h
 *
 *  Created on: Oct 6, 2021
 *      Author: Chris
 */

#ifndef KEYPRESS_H_
#define KEYPRESS_H_

#include <stdint.h>
#include <stdlib.h>
#include "USB_app/keyboard.h"

#include "FSM.h"

// Spanish Symbol Mappings.
#define A_RIGHT_ACCENT                  'z'
#define E_RIGHT_ACCENT                  'x'
#define I_RIGHT_ACCENT                  'c'
#define O_RIGHT_ACCENT                  'v'
#define U_RIGHT_ACCENT                  'b'
#define U_DIAERESIS                     'n'
#define N_TENUTO                        'm'
#define QUESTION_MARK_INVERTED          ','
#define EXCLAMATION_POINT_INVERTED      '.'

// French Symbol Mappings.
#define A_LEFT_ACCENT                   '1'
#define A_CARET                         '2'
//#define E_RIGHT_ACCENT                '3'
#define E_LEFT_ACCENT                   '4'
#define E_CARET                         '5'
#define E_DIAERESIS                     '6'
#define I_DIAERESIS                     '7'
#define I_CARET                         '8'
#define O_CARET                         '9'
#define U_LEFT_ACCENT                   '0'
#define U_CARET                         '-'
//#define U_DIAERESIS                   '='
#define C_CEDILLA                       'q'
#define Y_DIAERESIS                     'w'
#define AE                              'e'
#define OE                              'r'

#define NUM_SPANISH_CHARACTERS 9
#define NUM_FRENCH_CHARACTERS 16



typedef enum {
    French,
    Spanish
} Language;

typedef enum {
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    SpanishTab,
    FrenchTab
} Button;

typedef struct {
    Button       PressedKey;            // Which key was pressed
    FSMState     Action;                // How the key was pressed
    uint8_t      KeyPressDetected;      // If a key press has been detected
} KeyPressInfoType;

extern const uint8_t SpanishCharacters [NUM_SPANISH_CHARACTERS];
extern const uint8_t FrenchCharacters [NUM_FRENCH_CHARACTERS];
extern volatile uint8_t keySendComplete;
extern volatile KeyPressInfoType KeyPressInfo;
extern volatile Language CurrentLanguage;

void KeyPressInit(void);
void ChangeCurrentLanguage(Button SelectedTab);
uint8_t GetKeyFromButton(Button PressedKey);
void SpecialKeyPress(uint8_t c);
void MoveKeyToFront(Button PressedKey);

#endif /* KEYPRESS_H_ */
