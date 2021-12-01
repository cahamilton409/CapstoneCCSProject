#ifndef Display_h
#define Display_h

typedef enum {
    spanish,
    french_page1,
    french_page2
} language_t;

void display_init();
void default_grid();
void grid_with_touch();
void wait_for_touch();
void handle_touch();

#endif /*Display_h*/
