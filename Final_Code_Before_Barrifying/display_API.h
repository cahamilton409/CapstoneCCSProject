/*
 * display_API.h
 *
 *  Created on: Dec 7, 2021
 *      Author: Emory
 */

#ifndef DISPLAY_API_H_
#define DISPLAY_API_H_

uint8_t eve_read_tag(uint8_t *key);
uint8_t eve_read_tag_real(uint8_t *key);
void EVE_CREATE_SQUARE(uint16_t x, uint16_t y, uint16_t height, const char* character, uint8_t tag);
void EVE_RECT_WITH_TEXT(uint16_t x, uint16_t y, uint16_t height, uint16_t width, const char* character, uint8_t tag);
void EVE_RECT_WITH_TEXT_BITMAP(uint16_t x, uint16_t y, uint16_t height, uint16_t width, uint16_t character, uint8_t tag);
void EVE_RECT_WITH_TEXT_COLOR_EDGE(uint16_t x, uint16_t y, uint16_t height, uint16_t width, const char* character, uint8_t tag, uint8_t red, uint8_t green, uint8_t blue,uint8_t edge);
void EVE_RECT(uint16_t x, uint16_t y, uint16_t height, uint16_t width, uint8_t tag);
void EVE_LINE(uint16_t x, uint16_t y, uint16_t fat,uint8_t red, uint8_t blue, uint8_t green, uint16_t height, uint16_t width);

#endif /* DISPLAY_API_H_ */
