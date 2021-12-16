#include "flash_memory.h"
#include "key_press.h"

#include <msp430.h>

// Check if the flash memory data is stored correctly and load the key mappings if the
// memory is valid. Otherwise, load the default language mappings.
void flash_memory_init(void)
{
    // Load the mappings from memory.
    load_mappings();

    // Check if the Spanish mappings are valid..
    uint8_t mapping_valid = 0;
    uint8_t i;
    uint8_t mapping_index;
    for (mapping_index = 0; mapping_index < NUM_SPANISH_CHARACTERS; mapping_index++)
    {
        mapping_valid = 0;
        for (i = 0; i < NUM_SPANISH_CHARACTERS; i++)
        {
            if (g_spanish_mappings[mapping_index] == g_spanish_characters[i])
            {
                mapping_valid = 1;
            }
        }
        if (mapping_valid == 0)
        {
            break;
        }
    }

    // Check if the French mappings are valid..
    if (mapping_valid == 1)
    {
        for (mapping_index = 0; mapping_index < NUM_FRENCH_CHARACTERS; mapping_index++)
        {
            mapping_valid = 0;
            for (i = 0; i < NUM_FRENCH_CHARACTERS; i++)
            {
                if (g_french_mappings[mapping_index] == g_french_characters[i])
                {
                    mapping_valid = 1;
                }
            }
            if (mapping_valid == 0)
            {
                break;
            }
        }
    }

    // Check if the Greek mappings are valid.
    if (mapping_valid == 1)
    {
        for (mapping_index = 0; mapping_index < NUM_GREEK_CHARACTERS; mapping_index++)
        {
            mapping_valid = 0;
            for (i = 0; i < NUM_GREEK_CHARACTERS; i++)
            {
                if (g_greek_mappings[mapping_index] == g_greek_characters[i])
                {
                    mapping_valid = 1;
                }
            }
            if (mapping_valid == 0)
            {
                break;
            }
        }
    }

    // If the mappings are invalid, load the default mappings instead.
    if (mapping_valid == 0) {
        for (i = 0; i<NUM_SPANISH_CHARACTERS; i++)
        {
            g_spanish_mappings[i] = g_spanish_characters[i];
        }

        for (i = 0; i<NUM_FRENCH_CHARACTERS; i++)
        {
            g_french_mappings[i] = g_french_characters[i];
        }

        for (i = 0; i<NUM_GREEK_CHARACTERS; i++)
        {
            g_greek_mappings[i] = g_greek_characters[i];
        }
    }
}

// Store the key position mappings in their storage space in flash memory.
void save_mappings()
{
    unsigned int i;

    // Create a local copy of the mappings for each language.
    // Using the volatile for writing to memory causes
    // incorrect data to be stored in flash memory.
    uint8_t copy_spanish_mappings[NUM_SPANISH_CHARACTERS];
    for (i = 0; i < NUM_SPANISH_CHARACTERS; i++)
    {
        copy_spanish_mappings[i] = g_spanish_mappings[i];
    }
    uint8_t copy_french_mappings[NUM_FRENCH_CHARACTERS];
    for (i = 0; i < NUM_FRENCH_CHARACTERS; i++)
    {
        copy_french_mappings[i] = g_french_mappings[i];
    }
    uint8_t copy_greek_mappings[NUM_GREEK_CHARACTERS];
    for (i = 0; i < NUM_GREEK_CHARACTERS; i++)
    {
        copy_greek_mappings[i] = g_greek_mappings[i];
    }

    // Initialize a flash memory pointer for writing.
    char * Flash_ptr;
    Flash_ptr = (char *) 0x1800;
    FCTL3 = FWKEY;
    FCTL1 = FWKEY+ERASE;
    *Flash_ptr = 0;
    FCTL1 = FWKEY+WRT;

    // Write the Spanish mappings.
    for (i = 0; i < NUM_SPANISH_CHARACTERS; i++)
    {
    *Flash_ptr++ = copy_spanish_mappings[i];
    }

    // Write the French mappings.
    for (i = 0; i < NUM_FRENCH_CHARACTERS; i++)
    {
      *Flash_ptr++ = copy_french_mappings[i];
    }

    // Write the Greek mappings.
    for (i = 0; i < NUM_SPANISH_CHARACTERS; i++)
    {
      *Flash_ptr++ = copy_greek_mappings[i];
    }

    // Lock the memory after the write is complete.
    FCTL1 = FWKEY;
    FCTL3 = FWKEY+LOCK;
}

// Read the key position mappings from their storage space in memory.
void load_mappings()
{
    // Initialize a flash memory for reading.
    unsigned int i;
    char * Flash_ptr;
    Flash_ptr = (char *) MEMORY_LOCATION;

    // Load the Spanish mappings.
    for (i = 0; i < NUM_SPANISH_CHARACTERS; i++)
    {
        g_spanish_mappings[i] = *Flash_ptr++;
    }

    // Load the French mappings.
    for (i = 0; i < NUM_FRENCH_CHARACTERS; i++)
    {
        g_french_mappings[i] = *Flash_ptr++;
    }

    // Load the Greek mappings.
    for (i = 0; i < NUM_GREEK_CHARACTERS; i++)
    {
        g_greek_mappings[i] = *Flash_ptr++;
    }

}
