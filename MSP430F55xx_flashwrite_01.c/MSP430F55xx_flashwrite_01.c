/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 *
 *******************************************************************************
 * 
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP430F552x Demo - Single-Byte Flash In-System Programming, Copy SegC to SegD
//
//  Description: This program first erases flash seg C, then it increments all
//  values in seg C, then it erases seg D, then copies seg C to seg D. Starting
//  addresses of segments defined in this code: Seg C-0x1880, Seg D-0x1800.
//  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//  //* Set Breakpoint on NOP in the Mainloop to avoid Stressing Flash *//
//
//                MSP430F552x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430.h>
#include <stdint.h>

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

const uint8_t g_spanish_characters[NUM_SPANISH_CHARACTERS] = {
    QUESTION_MARK_INVERTED,
    A_RIGHT_ACCENT,
    E_RIGHT_ACCENT,
    I_RIGHT_ACCENT,
    O_RIGHT_ACCENT,
    U_RIGHT_ACCENT,
    U_DIAERESIS,
    N_TENUTO,
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




// Function prototypes
void init_mappings();
void save_mappings();
void load_mappings();


uint8_t g_spanish_mappings[NUM_SPANISH_CHARACTERS];
uint8_t g_french_mappings[NUM_FRENCH_CHARACTERS];
uint8_t i;
uint8_t read_val = 0;
uint8_t *addr = (uint8_t *) 0x1800;
int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  init_mappings();
  save_mappings();
  save_mappings();
  save_mappings();
  save_mappings();
  save_mappings();
  save_mappings();

  for (i = 0; i < NUM_SPANISH_CHARACTERS; i++) {
      g_spanish_mappings[i] = 0;
  }
  for (i = 0; i < NUM_FRENCH_CHARACTERS; i++) {
      g_french_mappings[i] = 0;
  }
  load_mappings();

  for (i = 0; i < 128; i++) {
      read_val = addr[i];
  }
  while(1)
  {

    __no_operation();
  }
}


void save_mappings()
{
  unsigned int i;
  char * Flash_ptr;                         // Initialize Flash pointer
  Flash_ptr = (char *) 0x1800;
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                      // Set Erase bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash seg
  FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

  for (i = 0; i < NUM_SPANISH_CHARACTERS; i++)
  {
    *Flash_ptr++ = g_spanish_mappings[i];                   // Write value to flash
  }
  for (i = 0; i < NUM_FRENCH_CHARACTERS; i++) {
      *Flash_ptr++ = g_french_mappings[i];
  }
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
}

void load_mappings()
{
    unsigned int i;
    char * Flash_ptr;                         // Initialize Flash pointer
    Flash_ptr = (char *) 0x1800;
    for (i = 0; i < NUM_SPANISH_CHARACTERS; i++) {
        g_spanish_mappings[i] = *Flash_ptr++;
    }
    for (i = 0; i < NUM_FRENCH_CHARACTERS; i++) {
        g_french_mappings[i] = *Flash_ptr++;
    }
}



void init_mappings() {
    // Populate the language mappings.
    uint8_t i;
    for (i = 0; i<NUM_SPANISH_CHARACTERS; i++) {
        g_spanish_mappings[i] = g_spanish_characters[i];
    }
    for (i = 0; i<NUM_FRENCH_CHARACTERS; i++) {
        g_french_mappings[i] = g_french_characters[i];
    }
}
