#include <display.h>
#include "key_press.h"
#include "UART0.h"

char clearscreen[] = "\r\n\n\n\n\n\n\n\n\n\n";


void display_init() {
    UART0_Init();
    update_display();
}

void update_display() {
    UART0_OutString(clearscreen);
    uint8_t i;

    UART0_OutString("The current language: ");
    if (g_current_language == spanish)
    {
        UART0_OutString("Spanish");
    }
    if (g_current_language == french_page1)
    {
        UART0_OutString("French: Page 1");
    }
    if (g_current_language == french_page2)
    {
        UART0_OutString("French: Page 2");
    }
    UART0_OutString("\n\r");

    for (i = 0; i < 9; i++) {
        char current_char;
        UART0_OutString("Key ");
        UART0_OutUDec(i+1);
        UART0_OutString(": ");

        if(g_current_language == spanish) {
            current_char = g_spanish_mappings[i];
            switch (current_char) {
            case (A_RIGHT_ACCENT):
                UART0_OutString("á");
                break;
            case (E_RIGHT_ACCENT):
                UART0_OutString("é");
                break;
            case (I_RIGHT_ACCENT):
                UART0_OutString("í");
                break;
            case (O_RIGHT_ACCENT):
                UART0_OutString("ó");
                break;
            case (U_RIGHT_ACCENT):
                UART0_OutString("ú");
                break;
            case (U_DIAERESIS):
                UART0_OutString("ü");
                break;
            case (N_TENUTO):
                UART0_OutString("ñ");
                break;
            case (QUESTION_MARK_INVERTED):
                UART0_OutString("¿");
                break;
            case (EXCLAMATION_POINT_INVERTED):
                UART0_OutString("¡");
                break;
            }
        }

        // Scale the mapping index if it is the second page.
        uint8_t mapping_index = i;
        if (g_current_language == french_page2)
        {
            mapping_index += 9;
        }
        if((g_current_language == french_page1) || (g_current_language == french_page2)) {
            // Check to make sure the index has a mapping.
            if (mapping_index < NUM_FRENCH_CHARACTERS)
            {
                current_char = g_french_mappings[mapping_index];
                switch (current_char) {
                case (A_LEFT_ACCENT):
                    UART0_OutString("à");
                    break;
                case (A_CARET):
                    UART0_OutString("â");
                    break;
                case (E_RIGHT_ACCENT):
                    UART0_OutString("é");
                    break;
                case (E_LEFT_ACCENT):
                    UART0_OutString("è");
                    break;
                case (E_CARET):
                    UART0_OutString("ê");
                    break;
                case (E_DIAERESIS):
                    UART0_OutString("ë");
                    break;
                case (I_DIAERESIS):
                    UART0_OutString("ï");
                    break;
                case (I_CARET):
                    UART0_OutString("î");
                    break;
                case (O_CARET):
                    UART0_OutString("ô");
                    break;
                case (U_LEFT_ACCENT):
                    UART0_OutString("ù");
                    break;
                case (U_CARET):
                    UART0_OutString("û");
                    break;
                case (U_DIAERESIS):
                    UART0_OutString("ü");
                    break;
                case (C_CEDILLA):
                    UART0_OutString("ç");
                    break;
                case (Y_DIAERESIS):
                    UART0_OutString("ÿ");
                    break;
                case (AE):
                    UART0_OutString("æ");
                    break;
                case (OE):
                    UART0_OutString("o");
                    break;
                default:
                    UART0_OutString("_");
                }
            }
            // Print a blank space for unused keys.
            else
            {
                UART0_OutString("_");
            }

        }
        if ((i == 2) || (i == 5) || (i == 8))
        {
          UART0_OutString("\n\r");
        }
        else
        {
            UART0_OutString(" | ");
        }

    }
}



