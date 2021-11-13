/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

#include "driverlib.h"
#include "key_press.h"

//******************************************************************************
//!
//!   Empty Project that includes driverlib
//!
//******************************************************************************

#define MAP_LENGTH 9

//// Spanish Symbol Mappings.
//#define A_RIGHT_ACCENT                  'z'
//#define E_RIGHT_ACCENT                  'x'
//#define I_RIGHT_ACCENT                  'c'
//#define O_RIGHT_ACCENT                  'v'
//#define U_RIGHT_ACCENT                  'b'
//#define U_DIAERESIS                     'n'
//#define N_TENUTO                        'm'
//#define QUESTION_MARK_INVERTED          ','
//#define EXCLAMATION_POINT_INVERTED      '.'
//
//// French Symbol Mappings.
//#define A_LEFT_ACCENT                   '1'
//#define A_CARET                         '2'
////#define E_RIGHT_ACCENT                '3'
//#define E_LEFT_ACCENT                   '4'
//#define E_CARET                         '5'
//#define E_DIAERESIS                     '6'
//#define I_DIAERESIS                     '7'
//#define I_CARET                         '8'
//#define O_CARET                         '9'
//#define U_LEFT_ACCENT                   '0'
//#define U_CARET                         '-'
////#define U_DIAERESIS                   '='
//#define C_CEDILLA                       'q'
//#define Y_DIAERESIS                     'w'
//#define AE                              'e'
//#define OE                              'r'

//const uint8_t g_spanish_characters[NUM_SPANISH_CHARACTERS] = {
//    A_RIGHT_ACCENT,
//    E_RIGHT_ACCENT,
//    I_RIGHT_ACCENT,
//    O_RIGHT_ACCENT,
//    U_RIGHT_ACCENT,
//    U_DIAERESIS,
//    N_TENUTO,
//    QUESTION_MARK_INVERTED,
//    EXCLAMATION_POINT_INVERTED};
//
//const uint8_t g_french_characters [NUM_FRENCH_CHARACTERS] = {
//    A_LEFT_ACCENT,
//    A_CARET,
//    E_RIGHT_ACCENT,
//    E_LEFT_ACCENT,
//    E_CARET,
//    E_DIAERESIS,
//    I_DIAERESIS,
//    I_CARET,
//    O_CARET,
//    U_LEFT_ACCENT,
//    U_CARET,
//    U_DIAERESIS,
//    C_CEDILLA,
//    Y_DIAERESIS,
//    AE,
//    OE};
//
//typedef enum
//{
//    key1,
//    key2,
//    key3,
//    key4,
//    key5,
//    key6,
//    key7,
//    key8,
//    key9,
//    spanish_tab,
//    french_tab,
//    no_key
//} button_t;


typedef struct
{
    button_t key;
    uint8_t value;
} map_t;

map_t example_map[MAP_LENGTH];// = {{key1, 0}, {key2, 0}};
button_t i;
void main (void)
{
    for (i=key1; i<=key9; i++)
    {
        map_t temp_map = {i, g_spanish_characters[i]};
        example_map[i] = temp_map;
    }
    example_map[0].value = 1;
    example_map[1].value = 2;
    while (1) {

    }
}
