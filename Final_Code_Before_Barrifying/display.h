#ifndef Display_h
#define Display_h

#include "key_press.h"

void display_init();
void default_grid();
void grid_with_touch();
void wait_for_touch();
void handle_touch();


void draw_keys(button_t selected_key);
uint8_t get_display_index(uint8_t mapping_index);

#endif /*Display_h*/
