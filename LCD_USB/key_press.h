/*
 * Keypress.h
 *
 *  Created on: Oct 6, 2021
 *      Author: Chris
 */

#ifndef KEY_PRESS_H_
#define KEY_PRESS_H_

#include <stdint.h>
#include <stdlib.h>
#include "USB_app/keyboard.h"


// Spanish Symbol Mappings.
#define A_RIGHT_ACCENT                  'z'
#define E_RIGHT_ACCENT                  'x'
#define I_RIGHT_ACCENT                  'c'
#define O_RIGHT_ACCENT                  'v'
#define U_RIGHT_ACCENT                  '/'
#define U_DIAERESIS                     'n'
#define N_TENUTO                        'm'
#define QUESTION_MARK_INVERTED          ','
#define EXCLAMATION_POINT_INVERTED      '.'

// French Symbol Mappings.
#define A_LEFT_ACCENT                   '1'
#define A_CARET                         '2'
#define E_LEFT_ACCENT                   '4'
#define E_CARET                         '5'
#define E_DIAERESIS                     '6'
#define I_DIAERESIS                     '7'
#define I_CARET                         '8'
#define O_CARET                         '9'
#define U_LEFT_ACCENT                   '0'
#define U_CARET                         '-'
#define C_CEDILLA                       'q'
#define Y_DIAERESIS                     'w'
#define AE                              'e'
#define OE                              'r'

// Greek Symbol Mappings.
#define PHI                             'a'
#define OMEGA_UPPERCASE                 's'
#define DELTA                           'd'
#define LAMBDA                          'f'
#define MU                              'g'
#define PI                              'h'
#define THETA                           'j'
#define SIGMA                           'k'
#define OMEGA_LOWERCASE                 'l'

// Character counts for each language used.
#define NUM_SPANISH_CHARACTERS 9
#define NUM_FRENCH_CHARACTERS 16
#define NUM_GREEK_CHARACTERS 9

// A type to represent the current language.
typedef enum
{
    spanish,
    french_page1,
    french_page2,
    greek
} language_t;

// A type to represent the different buttons available on the display.
typedef enum
{
    key1,
    key2,
    key3,
    key4,
    key5,
    key6,
    key7,
    key8,
    key9,
    spanish_tab,
    french_tab,
    greek_tab,
    no_key,
    next_key,
    back_key
} button_t;

// A type to represent the different types of actions that a user can perform
typedef enum {
    change_page,
    send_key,
    move_key
} action_t;

// A type containing structured information about a key press.
typedef struct
{
    button_t pressed_key;        // Which key was pressed
    action_t action;   // How the key was pressed
} key_press_info_type;

extern const uint8_t g_spanish_characters [NUM_SPANISH_CHARACTERS];
extern const uint8_t g_french_characters [NUM_FRENCH_CHARACTERS];
extern const uint8_t g_greek_characters [NUM_GREEK_CHARACTERS];

extern volatile uint8_t g_key_send_complete;
extern volatile key_press_info_type g_key_press_info;
extern volatile language_t g_current_language;
extern volatile uint8_t g_spanish_mappings[NUM_SPANISH_CHARACTERS];
extern volatile uint8_t g_french_mappings[NUM_FRENCH_CHARACTERS];
extern volatile uint8_t g_greek_mappings[NUM_GREEK_CHARACTERS];

void key_press_init(void);
void change_current_language(button_t selected_tab);
uint8_t get_key_from_button(button_t pressed_key);
void special_key_press(uint8_t mapped_character);
void move_key_to_front(button_t pressed_key);

#endif /* KEY_PRESS_H_ */
