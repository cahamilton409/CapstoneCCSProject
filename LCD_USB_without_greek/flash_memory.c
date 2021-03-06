/*
 * FlashMem.c
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 */

#include "flash_memory.h"
#include "key_press.h"

#include <msp430.h>

uint8_t spanish_mappings[NUM_SPANISH_CHARACTERS] = {
    QUESTION_MARK_INVERTED,
    A_RIGHT_ACCENT,
    E_RIGHT_ACCENT,
    I_RIGHT_ACCENT,
    O_RIGHT_ACCENT,
    U_RIGHT_ACCENT,
    U_DIAERESIS,
    N_TENUTO,
    EXCLAMATION_POINT_INVERTED};

void flash_memory_init(void) {
    // LOAD MAPPINGS FROM MEMORY.
    load_mappings();

    // IF THE MAPPINGS ARE INVALID, REVERT TO THE DEFAULT MAPPINGS.
    uint8_t mapping_valid = 0;
    uint8_t i;
    uint8_t mapping_index;
    for (mapping_index = 0; mapping_index < NUM_SPANISH_CHARACTERS; mapping_index++) {
        mapping_valid = 0;
        for (i = 0; i < NUM_SPANISH_CHARACTERS; i++) {
            if (g_spanish_mappings[mapping_index] == g_spanish_characters[i]) {
                mapping_valid = 1;
            }
        }
        if (mapping_valid == 0) {
            break;
        }
    }

    if (mapping_valid == 0) {
        // Populate the language mappings.
        for (i = 0; i<NUM_SPANISH_CHARACTERS; i++) {
            g_spanish_mappings[i] = g_spanish_characters[i];
        }
        for (i = 0; i<NUM_FRENCH_CHARACTERS; i++) {
            g_french_mappings[i] = g_french_characters[i];
        }
    }
}

void save_mappings()
{
    unsigned int i;

    uint8_t copy_spanish_mappings[NUM_SPANISH_CHARACTERS];
    for (i = 0; i < NUM_SPANISH_CHARACTERS; i++) {
        copy_spanish_mappings[i] = g_spanish_mappings[i];
    }

    uint8_t copy_french_mappings[NUM_FRENCH_CHARACTERS];
    for (i = 0; i < NUM_FRENCH_CHARACTERS; i++) {
        copy_french_mappings[i] = g_french_mappings[i];
    }

  char * Flash_ptr;                         // Initialize Flash pointer
  Flash_ptr = (char *) 0x1800;
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                      // Set Erase bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash seg
  FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

  for (i = 0; i < NUM_SPANISH_CHARACTERS; i++)
  {
    *Flash_ptr++ = copy_spanish_mappings[i];                   // Write value to flash
  }

  for (i = 0; i < NUM_FRENCH_CHARACTERS; i++) {
      *Flash_ptr++ = copy_french_mappings[i];
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
}

void load_mappings()
{
    unsigned int i;
    char * Flash_ptr;                         // Initialize Flash pointer
    Flash_ptr = (char *) MEMORY_LOCATION;
    for (i = 0; i < NUM_SPANISH_CHARACTERS; i++) {
        g_spanish_mappings[i] = *Flash_ptr++;
    }
    for (i = 0; i < NUM_FRENCH_CHARACTERS; i++) {
        g_french_mappings[i] = *Flash_ptr++;
    }

}
