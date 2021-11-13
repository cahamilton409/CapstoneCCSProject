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
    uint32_t i;

    UART0_OutString("The current language: ");
    if (g_current_language == spanish)
    {
        UART0_OutString("Spanish");
    }
    if (g_current_language == french)
    {
        UART0_OutString("French");
    }
    UART0_OutString("\n\r");

    for (i = 0; i < 9; i++) {
        char current_char;
        UART0_OutString("Key ");
        UART0_OutUDec(i+1);
        UART0_OutString(": ");

        if(g_current_language == spanish) {
            current_char = g_spanish_characters[i];
            switch (current_char) {
            case (A_RIGHT_ACCENT):
                UART0_OutString("�");
                break;
            case (E_RIGHT_ACCENT):
                UART0_OutString("�");
                break;
            case (I_RIGHT_ACCENT):
                UART0_OutString("�");
                break;
            case (O_RIGHT_ACCENT):
                UART0_OutString("�");
                break;
            case (U_RIGHT_ACCENT):
                UART0_OutString("�");
                break;
            case (U_DIAERESIS):
                UART0_OutString("�");
                break;
            case (N_TENUTO):
                UART0_OutString("�");
                break;
            case (QUESTION_MARK_INVERTED):
                UART0_OutString("�");
                break;
            case (EXCLAMATION_POINT_INVERTED):
                UART0_OutString("�");
                break;
            }
        }

        if(g_current_language == french) {
            current_char = g_french_characters[i];
            switch (current_char) {
            case (A_LEFT_ACCENT):
                UART0_OutString("�");
                break;
            case (A_CARET):
                UART0_OutString("�");
                break;
            case (E_RIGHT_ACCENT):
                UART0_OutString("�");
                break;
            case (E_LEFT_ACCENT):
                UART0_OutString("�");
                break;
            case (E_CARET):
                UART0_OutString("�");
                break;
            case (E_DIAERESIS):
                UART0_OutString("�");
                break;
            case (I_DIAERESIS):
                UART0_OutString("�");
                break;
            case (I_CARET):
                UART0_OutString("�");
                break;
            case (O_CARET):
                UART0_OutString("�");
                break;
            case (U_LEFT_ACCENT):
                UART0_OutString("�");
                break;
            case (U_CARET):
                UART0_OutString("�");
                break;
            case (U_DIAERESIS):
                UART0_OutString("�");
                break;
            case (C_CEDILLA):
                UART0_OutString("�");
                break;
            case (Y_DIAERESIS):
                UART0_OutString("�");
                break;
            case (AE):
                UART0_OutString("�");
                break;
            case (OE):
                UART0_OutString("�");
                break;
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



