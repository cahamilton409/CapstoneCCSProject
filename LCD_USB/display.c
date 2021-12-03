#include <display.h>
#include "key_press.h"
#include "UART0.h"
#include <stdint.h>

#include "lib/eve/include/EVE.h"
#include "lib/eve/include/HAL.h"
#include "example/eve_example.h"
#include "MCU.h"
#include <string.h>
#include "keypad.h"

const uint16_t x_buttons[9] = {80,240,400,80,240,400,80,240,400};
const uint16_t y_buttons[9] = {300,300,300,500,500,500,700,700,700};
char * french[9] = {"a","b","c","d","e","f","g","h","i"};
char * spanish_arr[9] = {"a`","e`","i`","o`","u`","u..","n~","?","!"};
const uint16_t height = 120;
const uint16_t width = 120;
const uint16_t french_button_x = 140;
const uint16_t french_button_y = 120;
const uint16_t spanish_button_x = 340;
const uint16_t spanish_button_y = 120;
const uint16_t language_select_height = 100;
const uint16_t language_select_width = 150;
uint8_t key;
uint8_t i = 0;

void display_init(void) {
    uint32_t font_end;
    EVE_Init();
    font_end = eve_init_fonts();
    eve_load_images(font_end);
}

void default_grid() {
    EVE_LIB_BeginCoProList();
    EVE_CMD_DLSTART();
    EVE_CLEAR_COLOR_RGB(229, 114, 0);
    EVE_CLEAR(1,1,1);
    EVE_CMD_SETROTATE(3);

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
    EVE_CMD_SETROTATE(3);

    draw_keys(g_key_press_info.pressed_key);

    EVE_DISPLAY();
    EVE_CMD_SWAP();
    EVE_LIB_EndCoProList();
    EVE_LIB_AwaitCoProEmpty();
}

void wait_for_touch() {
    default_grid();
    uint8_t selected;
    while ((selected = eve_read_tag_real(&key)) == 0);
    g_key_press_info.pressed_key = (button_t) (selected-1);
    g_key_press_info.b_key_press_detected = 1;
}

void handle_touch() {
    grid_with_touch();

    g_time_elapsed = 0;
    while (eve_read_tag_real(&key) != 0) {
        g_time_elapsed++;
    }

    if ((g_key_press_info.pressed_key == spanish_tab) || (g_key_press_info.pressed_key == spanish_tab)) {
        g_key_press_info.action = change_page;
    }
    else if (g_time_elapsed > 5000) {
        g_key_press_info.action = move_key;
    }
    else {
        g_key_press_info.action = send_key;
    }
}

void draw_keys(button_t selected_key) {
    uint8_t selected = selected_key;
    if (g_current_language == french_page1) {

        for (i = 0; i < 9; i++) {
            if (i != selected) {
                EVE_RECT_WITH_TEXT(x_buttons[i],y_buttons[i],height,width,french[i],i+1);
            }
            if (i == selected) {
                EVE_RECT(x_buttons[selected],y_buttons[selected],height,width,selected+1);
            }
        }
        EVE_RECT_WITH_TEXT_COLOR(french_button_x,french_button_y,language_select_height,language_select_width,"French",10,255,255,0);
        EVE_RECT_WITH_TEXT_COLOR(spanish_button_x,spanish_button_y,language_select_height,language_select_width,"Spanish",11,255,255,255);
    }
    else if (g_current_language == spanish){
        for (i = 0; i < 9; i++) {
            if (i != selected) {
                EVE_RECT_WITH_TEXT(x_buttons[i],y_buttons[i],height,width,spanish_arr[i],i+1);
            }
            if (i == selected) {
                EVE_RECT(x_buttons[selected],y_buttons[selected],height,width,selected+1);
            }
        }
        EVE_RECT_WITH_TEXT_COLOR(french_button_x,french_button_y,language_select_height,language_select_width,"French",10,255,255,255);
        EVE_RECT_WITH_TEXT_COLOR(spanish_button_x,spanish_button_y,language_select_height,language_select_width,"Spanish",11,255,255,0);
    }

}

