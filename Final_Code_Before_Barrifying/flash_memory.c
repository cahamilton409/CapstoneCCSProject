/*
 * FlashMem.c
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 */

#include "flash_memory.h"
#include "key_press.h"

#include <msp430.h>

void flash_memory_init(void) {
    // LOAD MAPPINGS FROM MEMORY.
    load_mappings();

    // CHECK IF THE SPANISH MAPPINGS ARE VALID.
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

    // CHECK IF THE FRENCH MAPPINGS ARE VALID.
    if (mapping_valid == 1) {
        for (mapping_index = 0; mapping_index < NUM_FRENCH_CHARACTERS; mapping_index++) {
            mapping_valid = 0;
            for (i = 0; i < NUM_FRENCH_CHARACTERS; i++) {
                if (g_french_mappings[mapping_index] == g_french_characters[i]) {
                    mapping_valid = 1;
                }
            }
            if (mapping_valid == 0) {
                break;
            }
        }
    }

    // CHECK IF THE GREEK MAPPINGS ARE VALID.
    if (mapping_valid == 1) {
        for (mapping_index = 0; mapping_index < NUM_GREEK_CHARACTERS; mapping_index++) {
            mapping_valid = 0;
            for (i = 0; i < NUM_GREEK_CHARACTERS; i++) {
                if (g_greek_mappings[mapping_index] == g_greek_characters[i]) {
                    mapping_valid = 1;
                }
            }
            if (mapping_valid == 0) {
                break;
            }
        }
    }

    // IF THE MAPPINGS ARE INVALID, LOAD THE DEFAULT MAPPINGS.
    if (mapping_valid == 0) {
        // Populate the language mappings.
        for (i = 0; i<NUM_SPANISH_CHARACTERS; i++) {
            g_spanish_mappings[i] = g_spanish_characters[i];
        }
        for (i = 0; i<NUM_FRENCH_CHARACTERS; i++) {
            g_french_mappings[i] = g_french_characters[i];
        }
        for (i = 0; i<NUM_GREEK_CHARACTERS; i++) {
            g_greek_mappings[i] = g_greek_characters[i];
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

    uint8_t copy_greek_mappings[NUM_GREEK_CHARACTERS];
    for (i = 0; i < NUM_GREEK_CHARACTERS; i++) {
        copy_greek_mappings[i] = g_greek_mappings[i];
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

  for (i = 0; i < NUM_SPANISH_CHARACTERS; i++) {
      *Flash_ptr++ = copy_greek_mappings[i];
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
    for (i = 0; i < NUM_GREEK_CHARACTERS; i++) {
        g_greek_mappings[i] = *Flash_ptr++;
    }

}
