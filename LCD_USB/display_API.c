/*
 * display_API.c
 *
 *  Created on: Dec 7, 2021
 *      Author: Emory
 */

#include <stdint.h>
#include "lib/eve/include/EVE.h"
#include "lib/eve/include/HAL.h"
#include "MCU.h"
#include <string.h>

extern const uint8_t font0[];
const EVE_GPU_FONT_HEADER *font0_hdr = (const EVE_GPU_FONT_HEADER *)font0;


uint8_t eve_read_tag(uint8_t *key)
{
    uint8_t Read_tag;
    uint8_t key_detect = 0;

    Read_tag = HAL_MemRead8(EVE_REG_TOUCH_TAG);

    if (!(HAL_MemRead16(EVE_REG_TOUCH_RAW_XY) & 0x8000))
    {
        key_detect = 1;
        *key = Read_tag;
    }

    return key_detect;
}

uint8_t eve_read_tag_real(uint8_t *key)
{
    uint8_t Read_tag;
    uint8_t key_detect = 0;

    Read_tag = HAL_MemRead8(EVE_REG_TOUCH_TAG);

    if (!(HAL_MemRead16(EVE_REG_TOUCH_SCREEN_XY) & 0x8000))
    {
        key_detect = Read_tag;
        *key = Read_tag;
    }


    return key_detect;
}


void eve_create_square(uint16_t x, uint16_t y, uint16_t height, const char* character, uint8_t tag)
{
    EVE_COLOR_RGB(35, 45, 75);
    EVE_BEGIN(EVE_BEGIN_LINES);
    EVE_LINE_WIDTH(40);
    EVE_VERTEX2F(x*16+height*8,y*16+height*8);
    EVE_VERTEX2F(x*16+height*8,y*16-height*8);
    EVE_VERTEX2F(x*16+height*8,y*16-height*8);
    EVE_VERTEX2F(x*16-height*8,y*16-height*8);
    EVE_VERTEX2F(x*16-height*8,y*16-height*8);
    EVE_VERTEX2F(x*16-height*8,y*16+height*8);
    EVE_VERTEX2F(x*16-height*8,y*16+height*8);
    EVE_VERTEX2F(x*16+height*8,y*16+height*8);
}

void eve_rect_with_text(uint16_t x, uint16_t y, uint16_t height, uint16_t width, const char* character, uint8_t tag) {
    EVE_BEGIN(EVE_BEGIN_RECTS);
    EVE_COLOR_RGB(255, 255, 255);
    EVE_LINE_WIDTH(10*16);
    EVE_TAG(tag);
    EVE_VERTEX2F(x*16+width*8,y*16+height*8);
    EVE_VERTEX2F(x*16-width*8,y*16-height*8);
    EVE_COLOR_RGB(35, 45, 75);
    EVE_CMD_TEXT(x,y, 8, EVE_OPT_CENTERX | EVE_OPT_CENTERY,character);
}

void eve_rect_with_text_bitmap(uint16_t x, uint16_t y, uint16_t height, uint16_t width, uint16_t character, uint8_t tag) {
    EVE_BEGIN(EVE_BEGIN_RECTS);
    EVE_COLOR_RGB(255, 255, 255);
    EVE_LINE_WIDTH(10*16);
    EVE_TAG(tag);
    EVE_VERTEX2F(x*16+width*8,y*16+height*8);
    EVE_VERTEX2F(x*16-width*8,y*16-height*8);
    EVE_COLOR_RGB(35, 45, 75);
    EVE_BEGIN(EVE_BEGIN_BITMAPS);
    EVE_BITMAP_HANDLE(8);
    EVE_CELL(character);
    EVE_VERTEX2F(x*16-24*8,y*16-50*8);
    EVE_END();
}

void eve_rect_with_text_color_edge(uint16_t x, uint16_t y, uint16_t height, uint16_t width, const char* character, uint8_t tag, uint8_t red, uint8_t green, uint8_t blue,uint8_t edge) {
    EVE_BEGIN(EVE_BEGIN_RECTS);
    EVE_COLOR_RGB(red, green, blue);
    EVE_TAG(tag);
    EVE_LINE_WIDTH(edge*16);
    EVE_VERTEX2F(x*16+width*8,y*16+height*8);
    EVE_VERTEX2F(x*16-width*8,y*16-height*8);
    EVE_COLOR_RGB(35, 45, 75);
    EVE_CMD_TEXT(x,y, 30, EVE_OPT_CENTERX | EVE_OPT_CENTERY,character);
}

void eve_rect(uint16_t x, uint16_t y, uint16_t height, uint16_t width, uint8_t tag) {
    EVE_BEGIN(EVE_BEGIN_RECTS);
    EVE_COLOR_RGB(35, 45, 75);
    EVE_TAG(tag);
    EVE_LINE_WIDTH(10*16);
    EVE_VERTEX2F(x*16+width*8,y*16+height*8);
    EVE_VERTEX2F(x*16-width*8,y*16-height*8);
}

void eve_line(uint16_t x, uint16_t y, uint16_t fat,uint8_t red, uint8_t blue, uint8_t green, uint16_t height, uint16_t width) {
    EVE_BEGIN(EVE_BEGIN_LINES);
    EVE_LINE_WIDTH(fat);
    EVE_COLOR_RGB(red, blue, green);
    EVE_VERTEX2F(x*16,y*16);
    EVE_VERTEX2F(x*16+width*16,y*16+height*16);
}
