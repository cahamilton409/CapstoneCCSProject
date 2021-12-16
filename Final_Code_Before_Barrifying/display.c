#include <display.h>
#include "key_press.h"
#include "UART0.h"
#include <stdint.h>

#include "lib/eve/include/EVE.h"
#include "lib/eve/include/HAL.h"
#include "display_API.h"
#include "display_fonts.h"
#include "audio.h"
#include "MCU.h"
#include <string.h>
#include "keypad.h"

const uint16_t x_buttons[9] = {80,240,400,80,240,400,80,240,400};
const uint16_t y_buttons[9] = {220,220,220,380,380,380,540,540,540};
uint16_t french[NUM_FRENCH_CHARACTERS] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
uint16_t spanish_arr[NUM_SPANISH_CHARACTERS] = {33,34,35,36,37,38,39,40,41};
uint16_t greek_arr[NUM_GREEK_CHARACTERS] = {49,50,51,52,53,54,55,56,57};

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

const uint16_t height = 120;
const uint16_t width = 120;
const uint16_t spanish_button_x = 80;
const uint16_t spanish_button_y = 50;
const uint16_t french_button_x = 240;
const uint16_t french_button_y = 50;
const uint16_t greek_button_x = 400;
const uint16_t greek_button_y = 50;
const uint16_t language_select_height = 100;
const uint16_t language_select_width = 160;
uint8_t key;
uint8_t i = 0;

void display_init(void) {
    EVE_Init();
    eve_init_fonts();
}

void default_grid() {
    EVE_LIB_BeginCoProList();
    EVE_CMD_DLSTART();
    EVE_CLEAR_COLOR_RGB(229, 114, 0);
    EVE_CLEAR(1,1,1);
    EVE_CMD_SETROTATE(2);

    draw_keys(no_key);

    EVE_DISPLAY();
    EVE_CMD_SWAP();
    EVE_LIB_EndCoProList();
    EVE_LIB_AwaitCoProEmpty();
}

void grid_with_touch() {
    EVE_LIB_BeginCoProList();
    EVE_CMD_DLSTART();
    EVE_CLEAR_COLOR_RGB(229, 114, 0);
    EVE_CLEAR(1,1,1);
    EVE_CMD_SETROTATE(2);


    draw_keys(g_key_press_info.pressed_key);

    EVE_DISPLAY();
    EVE_CMD_SWAP();
    EVE_LIB_EndCoProList();
    EVE_LIB_AwaitCoProEmpty();
}

void wait_for_touch() {
    default_grid();
    uint8_t selected;
    while ((selected = eve_read_tag_real(&key)) == 0) {
        default_grid();
        check_volume();
    }
    g_key_press_info.pressed_key = (button_t) (selected-1);
    g_key_press_info.b_key_press_detected = 1;
}

void handle_touch() {
    grid_with_touch();

    g_time_elapsed = 0;
    while (eve_read_tag_real(&key) != 0) {
        g_time_elapsed++;
    }

    if ((g_key_press_info.pressed_key == spanish_tab) || (g_key_press_info.pressed_key == french_tab) || (g_key_press_info.pressed_key == greek_tab)|| (g_key_press_info.pressed_key == next_key)|| (g_key_press_info.pressed_key == back_key)) {
        g_key_press_info.action = change_page;
    }
    else if (g_time_elapsed > 2500) {
        g_key_press_info.action = move_key;
    }
    else {
        g_key_press_info.action = send_key;
    }
}

void draw_keys(button_t selected_key) {
    EVE_CMD_PROGRESS(360, 760, 100, 20, 2, volume_level, 3);
    EVE_CMD_TEXT(410,735, 30, EVE_OPT_CENTERX | EVE_OPT_CENTERY,"Volume");
    uint8_t selected = selected_key;
    if (g_current_language == spanish){
        for (i = 0; i < 9; i++) {
            if (i != selected) {
                uint8_t display_index = get_display_index(i);
                EVE_RECT_WITH_TEXT_BITMAP(x_buttons[i],y_buttons[i],height,width,spanish_arr[display_index],i+1);
            }
            if (i == selected) {
                EVE_RECT(x_buttons[selected],y_buttons[selected],height,width,selected+1);
            }
        }
        EVE_RECT_WITH_TEXT_COLOR_EDGE(french_button_x,french_button_y,language_select_height,language_select_width,"French",11,255,255,255,1);
        EVE_RECT_WITH_TEXT_COLOR_EDGE(spanish_button_x,spanish_button_y,language_select_height,language_select_width,"Spanish",10,229, 114, 0,1);
        EVE_RECT_WITH_TEXT_COLOR_EDGE(greek_button_x,greek_button_y,language_select_height,language_select_width,"Greek",12,255,255,255,1);
        EVE_LINE(160,100,40,35, 45, 75,0,480);
        EVE_LINE(160,100,40,35, 45, 75,-100,0);
        EVE_LINE(320,100,40,35, 45, 75,-100,0);
        EVE_COLOR_RGB(255, 255, 255);
    }

    else if (g_current_language == french_page1) {

        for (i = 0; i < 9; i++) {
            if (i != selected) {
                uint8_t display_index = get_display_index(i);
                EVE_RECT_WITH_TEXT_BITMAP(x_buttons[i],y_buttons[i],height,width,french[display_index],i+1);
            }
            if (i == selected) {
                EVE_RECT(x_buttons[selected],y_buttons[selected],height,width,selected+1);
            }
        }
        EVE_RECT_WITH_TEXT_COLOR_EDGE(french_button_x,french_button_y,language_select_height,language_select_width,"French",11,229, 114, 0,1);
        EVE_RECT_WITH_TEXT_COLOR_EDGE(spanish_button_x,spanish_button_y,language_select_height,language_select_width,"Spanish",10,255,255,255,1);
        EVE_RECT_WITH_TEXT_COLOR_EDGE(greek_button_x,greek_button_y,language_select_height,language_select_width,"Greek",12,255,255,255,1);
        EVE_RECT_WITH_TEXT_COLOR_EDGE(240,700,75,75,">",14,255,255,255,13);
        EVE_LINE(0,100,40,35, 45, 75,0,160);
        EVE_LINE(320,100,40,35, 45, 75,0,160);
        EVE_LINE(160,100,40,35, 45, 75,-100,0);
        EVE_LINE(320,100,40,35, 45, 75,-100,0);
        EVE_CREATE_SQUARE(240,700,100,' ',0);

    }

    else if (g_current_language == french_page2) {

        for (i = 0; i < 7; i++) {
            if (i != selected) {
                uint8_t display_index = get_display_index(i + 9);
                EVE_RECT_WITH_TEXT_BITMAP(x_buttons[i],y_buttons[i],height,width,french[display_index],i+1);
            }
            if (i == selected) {
                EVE_RECT(x_buttons[selected],y_buttons[selected],height,width,selected+1);
            }
        }
        EVE_RECT_WITH_TEXT_COLOR_EDGE(french_button_x,french_button_y,language_select_height,language_select_width,"French",11,229, 114, 0,1);
        EVE_RECT_WITH_TEXT_COLOR_EDGE(spanish_button_x,spanish_button_y,language_select_height,language_select_width,"Spanish",10,255,255,255,1);
        EVE_RECT_WITH_TEXT_COLOR_EDGE(greek_button_x,greek_button_y,language_select_height,language_select_width,"Greek",12,255,255,255,1);
        EVE_RECT_WITH_TEXT_COLOR_EDGE(240,700,75,75,"<",15,255,255,255,13);
        EVE_LINE(0,100,40,35, 45, 75,0,160);
        EVE_LINE(320,100,40,35, 45, 75,0,160);
        EVE_LINE(160,100,40,35, 45, 75,-100,0);
        EVE_LINE(320,100,40,35, 45, 75,-100,0);
        EVE_CREATE_SQUARE(240,700,100,' ',0);

    }

    if (g_current_language == greek){
        for (i = 0; i < 9; i++) {
            if (i != selected) {
                uint8_t display_index = get_display_index(i);
                EVE_RECT_WITH_TEXT_BITMAP(x_buttons[i],y_buttons[i],height,width,greek_arr[display_index],i+1);
            }
            if (i == selected) {
                EVE_RECT(x_buttons[selected],y_buttons[selected],height,width,selected+1);
            }
        }
        EVE_RECT_WITH_TEXT_COLOR_EDGE(french_button_x,french_button_y,language_select_height,language_select_width,"French",11,255,255,255,1);
        EVE_RECT_WITH_TEXT_COLOR_EDGE(spanish_button_x,spanish_button_y,language_select_height,language_select_width,"Spanish",10,255,255,255,1);
        EVE_RECT_WITH_TEXT_COLOR_EDGE(greek_button_x,greek_button_y,language_select_height,language_select_width,"Greek",12,229, 114, 0,1);
        EVE_LINE(0,100,40,35, 45, 75,0,320);
        EVE_LINE(160,100,40,35, 45, 75,-100,0);
        EVE_LINE(320,100,40,35, 45, 75,-100,0);
    }


}

uint8_t get_display_index(uint8_t mapping_index) {
    if (g_current_language == spanish) {
        char current_char = g_spanish_mappings[mapping_index];
        switch (current_char) {
        case A_RIGHT_ACCENT:
            return 0;
        case E_RIGHT_ACCENT:
            return 1;
        case I_RIGHT_ACCENT:
            return 2;
        case O_RIGHT_ACCENT:
            return 3;
        case U_RIGHT_ACCENT:
            return 4;
        case U_DIAERESIS:
            return 5;
        case N_TENUTO:
            return 6;
        case QUESTION_MARK_INVERTED:
            return 7;
        case EXCLAMATION_POINT_INVERTED:
            return 8;
        default:
            return 0;
        }
    }

    if ((g_current_language == french_page1) || (g_current_language == french_page2)) {
        char current_char = g_french_mappings[mapping_index];
        switch (current_char) {
        case A_LEFT_ACCENT:
            return 0;
        case A_CARET:
            return 1;
        case E_RIGHT_ACCENT:
            return 2;
        case E_LEFT_ACCENT:
            return 3;
        case E_CARET:
            return 4;
        case E_DIAERESIS:
            return 5;
        case I_DIAERESIS:
            return 6;
        case I_CARET:
            return 7;
        case O_CARET:
            return 8;
        case U_LEFT_ACCENT:
            return 9;
        case U_CARET:
            return 10;
        case U_DIAERESIS:
            return 11;
        case C_CEDILLA:
            return 12;
        case Y_DIAERESIS:
            return 13;
        case AE:
            return 14;
        case OE:
            return 15;
        default:
            return 0;
        }
    }

    if (g_current_language == greek) {
        char current_char = g_greek_mappings[mapping_index];
        switch (current_char) {
        case PHI:
            return 0;
        case OMEGA_UPPERCASE:
            return 1;
        case DELTA:
            return 2;
        case LAMBDA:
            return 3;
        case MU:
            return 4;
        case PI:
            return 5;
        case THETA:
            return 6;
        case SIGMA:
            return 7;
        case OMEGA_LOWERCASE:
            return 8;
        default:
            return 0;
        }
    }

    return 0;
}




