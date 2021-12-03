/**
 @file eve_example.c
 */
/*
 * ============================================================================
 * History
 * =======
 * Nov 2019		Initial beta for FT81x and FT80x
 * Mar 2020		Updated beta - added BT815/6 commands
 * Mar 2021		Beta with BT817/8 support added
 *
 *
 *
 *
 *
 * (C) Copyright,  Bridgetek Pte. Ltd.
 * ============================================================================
 *
 * This source code ("the Software") is provided by Bridgetek Pte Ltd
 * ("Bridgetek") subject to the licence terms set out
 * http://www.ftdichip.com/FTSourceCodeLicenceTerms.htm ("the Licence Terms").
 * You must read the Licence Terms before downloading or using the Software.
 * By installing or using the Software you agree to the Licence Terms. If you
 * do not agree to the Licence Terms then do not download or use the Software.
 *
 * Without prejudice to the Licence Terms, here is a summary of some of the key
 * terms of the Licence Terms (and in the event of any conflict between this
 * summary and the Licence Terms then the text of the Licence Terms will
 * prevail).
 *
 * The Software is provided "as is".
 * There are no warranties (or similar) in relation to the quality of the
 * Software. You use it at your own risk.
 * The Software should not be used in, or for, any medical device, system or
 * appliance. There are exclusions of Bridgetek liability for certain types of loss
 * such as: special loss or damage; incidental loss or damage; indirect or
 * consequential loss or damage; loss of income; loss of business; loss of
 * profits; loss of revenue; loss of contracts; business interruption; loss of
 * the use of money or anticipated savings; loss of information; loss of
 * opportunity; loss of goodwill or reputation; and/or loss of, damage to or
 * corruption of data.
 * There is a monetary cap on Bridgetek's liability.
 * The Software may have subsequently been amended by another user and then
 * distributed by that other user ("Adapted Software").  If so that user may
 * have additional licence terms that apply to those amendments. However, Bridgetek
 * has no liability in relation to those amendments.
 * ============================================================================
 */

#include <stdint.h>

#include "EVE.h"
#include "../include/HAL.h"
#include "MCU.h"
#include <string.h>

#include "eve_example.h"
extern const uint8_t font0[];
const EVE_GPU_FONT_HEADER *font0_hdr = (const EVE_GPU_FONT_HEADER *)font0;


void EVE_CREATE_SQUARE(uint16_t x, uint16_t y, uint16_t height, const char* character, uint8_t tag) {
    EVE_TAG(tag);
    EVE_COLOR_RGB(255, 255, 255);
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
    EVE_CMD_TEXT(x,y, 30, EVE_OPT_CENTERX | EVE_OPT_CENTERY,character);
}

void EVE_RECT_WITH_TEXT(uint16_t x, uint16_t y, uint16_t height, uint16_t width, const char* character, uint8_t tag) {
    EVE_BEGIN(EVE_BEGIN_RECTS);
    EVE_COLOR_RGB(255, 255, 255);
    EVE_LINE_WIDTH(10*16);
    EVE_TAG(tag);
    EVE_VERTEX2F(x*16+width*8,y*16+height*8);
    EVE_VERTEX2F(x*16-width*8,y*16-height*8);
    EVE_COLOR_RGB(35, 45, 75);
    EVE_CMD_TEXT(x,y, 30, EVE_OPT_CENTERX | EVE_OPT_CENTERY,character);
}

void EVE_RECT_WITH_TEXT_COLOR(uint16_t x, uint16_t y, uint16_t height, uint16_t width, const char* character, uint8_t tag, uint8_t red, uint8_t green, uint8_t blue) {
    EVE_BEGIN(EVE_BEGIN_RECTS);
    EVE_COLOR_RGB(red, green, blue);
    EVE_TAG(tag);
    EVE_LINE_WIDTH(10*16);
    EVE_VERTEX2F(x*16+width*8,y*16+height*8);
    EVE_VERTEX2F(x*16-width*8,y*16-height*8);
    EVE_COLOR_RGB(35, 45, 75);
    EVE_CMD_TEXT(x,y, 30, EVE_OPT_CENTERX | EVE_OPT_CENTERY,character);
}

void EVE_RECT(uint16_t x, uint16_t y, uint16_t height, uint16_t width, uint8_t tag) {
    EVE_BEGIN(EVE_BEGIN_RECTS);
    EVE_COLOR_RGB(35, 45, 75);
    EVE_TAG(tag);
    EVE_LINE_WIDTH(10*16);
    EVE_VERTEX2F(x*16+width*8,y*16+height*8);
    EVE_VERTEX2F(x*16-width*8,y*16-height*8);
}

void box_create(void) {

    uint8_t key;
    uint16_t selected;
    int num = 0;

    const uint16_t x_buttons[9] = {80,240,400,80,240,400,80,240,400};
    const uint16_t y_buttons[9] = {300,300,300,500,500,500,700,700,700};
    char * french[9] = {"a","b","c","d","e","f","g","h","i"};
    char * spanish[9] = {"1","2","3","4","5","6","7","8","9"};
    uint8_t language_select = 0;
    const uint16_t height = 120;
    const uint16_t width = 120;
    const uint16_t french_button_x = 140;
    const uint16_t french_button_y = 120;
    const uint16_t spanish_button_x = 340;
    const uint16_t spanish_button_y = 120;
    const uint16_t language_select_height = 100;
    const uint16_t language_select_width = 150;

    do {
        switch (num) {
            case 0:

                EVE_LIB_BeginCoProList();
                EVE_CMD_DLSTART();
                EVE_CLEAR_COLOR_RGB(229, 114, 0);
                EVE_CLEAR(1,1,1);
                EVE_CMD_SETROTATE(3);
                uint8_t i = 1;

                if (language_select == 0) {
                    for (i = 1; i < 10; i++) {
                        EVE_RECT_WITH_TEXT(x_buttons[i-1],y_buttons[i-1],height,width,french[i-1],i);
                    }

                    EVE_RECT_WITH_TEXT_COLOR(french_button_x,french_button_y,language_select_height,language_select_width,"French",10,255,255,0);
                    EVE_RECT_WITH_TEXT_COLOR(spanish_button_x,spanish_button_y,language_select_height,language_select_width,"Spanish",11,255,255,255);
                }
                else {
                    for (i = 1; i < 10; i++) {
                        EVE_RECT_WITH_TEXT(x_buttons[i-1],y_buttons[i-1],height,width,spanish[i-1],i);
                    }
                    EVE_RECT_WITH_TEXT_COLOR(french_button_x,french_button_y,language_select_height,language_select_width,"French",10,255,255,255);
                    EVE_RECT_WITH_TEXT_COLOR(spanish_button_x,spanish_button_y,language_select_height,language_select_width,"Spanish",11,255,255,0);
                }
                EVE_DISPLAY();
                EVE_CMD_SWAP();
                EVE_LIB_EndCoProList();
                EVE_LIB_AwaitCoProEmpty();

                while ((selected = eve_read_tag_real(&key)) == 0);
                num = 1;
                break;
            case 1:
                if (selected == 10) {
                    language_select = 0;
                }
                if (selected == 11) {
                    language_select = 1;
                }
                EVE_LIB_BeginCoProList();
                EVE_CMD_DLSTART();
                EVE_CLEAR_COLOR_RGB(229, 114, 0);
                EVE_CLEAR(1,1,1);
                EVE_CMD_SETROTATE(3);
                i = 1;
                if (language_select == 0) {

                    for (i = 1; i < 10; i++) {
                        if (i != selected) {
                            EVE_RECT_WITH_TEXT(x_buttons[i-1],y_buttons[i-1],height,width,french[i-1],i);
                        }
                        if (i == selected) {
                            EVE_RECT(x_buttons[selected-1],y_buttons[selected-1],height,width,selected);
                        }
                    }
                    EVE_RECT_WITH_TEXT_COLOR(french_button_x,french_button_y,language_select_height,language_select_width,"French",10,255,255,0);
                    EVE_RECT_WITH_TEXT_COLOR(spanish_button_x,spanish_button_y,language_select_height,language_select_width,"Spanish",11,255,255,255);
                }
                else {
                    for (i = 1; i < 10; i++) {
                        if (i != selected) {
                            EVE_RECT_WITH_TEXT(x_buttons[i-1],y_buttons[i-1],height,width,spanish[i-1],i);
                        }
                        if (i == selected) {
                            EVE_RECT(x_buttons[selected-1],y_buttons[selected-1],height,width,selected);
                        }
                    }
                    EVE_RECT_WITH_TEXT_COLOR(french_button_x,french_button_y,language_select_height,language_select_width,"French",10,255,255,255);
                    EVE_RECT_WITH_TEXT_COLOR(spanish_button_x,spanish_button_y,language_select_height,language_select_width,"Spanish",11,255,255,0);
                }

                EVE_DISPLAY();
                EVE_CMD_SWAP();
                EVE_LIB_EndCoProList();
                EVE_LIB_AwaitCoProEmpty();
                num = 0;
                break;
        }


        } while (1);

}

void eve_display(void)
{
	uint32_t counter = 0;
	uint8_t key;
	int8_t i;
	uint32_t units;

	do {
		// Comment this line if the counter needs to increment continuously.
		// Uncomment and it will increment by one each press.
		//while (eve_read_tag(&key) != 0);

		EVE_LIB_BeginCoProList();
		EVE_CMD_DLSTART();
		EVE_CLEAR_COLOR_RGB(0, 0, 0);
		EVE_CLEAR(1,1,1);
		EVE_COLOR_RGB(255, 255, 255);

		EVE_BEGIN(EVE_BEGIN_BITMAPS);
#if (defined EVE2_ENABLE || defined EVE3_ENABLE || defined EVE4_ENABLE)
		// Set origin on canvas using EVE_VERTEX_TRANSLATE.
		EVE_VERTEX_TRANSLATE_X(((EVE_DISP_WIDTH/2)-(eve_img_bridgetek_logo_width/2)) * 16);
		EVE_VERTEX2II(0, 0, BITMAP_BRIDGETEK_LOGO, 0);
		EVE_VERTEX_TRANSLATE_X(0);
#else
		// Place directly on canvas EVE_VERTEX_TRANSLATE not available.
		EVE_VERTEX2II((EVE_DISP_WIDTH/2)-(eve_img_bridgetek_logo_width/2), 0, BITMAP_BRIDGETEK_LOGO, 0);
#endif

		EVE_CMD_TEXT(EVE_DISP_WIDTH/2, eve_img_bridgetek_logo_height,
				28, EVE_OPT_CENTERX, "Touch the counter");

		EVE_TAG(100);

		EVE_COLOR_RGB(255, 0, 0);

		EVE_BEGIN(EVE_BEGIN_BITMAPS);
		units = 1;

#if (defined EVE2_ENABLE || defined EVE3_ENABLE || defined EVE4_ENABLE)
		EVE_VERTEX_TRANSLATE_Y((EVE_DISP_HEIGHT / 2) * 16);
		for (i = 0; i < 5; i++)
		{
			EVE_VERTEX_TRANSLATE_X((((EVE_DISP_WIDTH - (font0_hdr->FontWidthInPixels * 5)) / 2) - (font0_hdr->FontWidthInPixels) + (font0_hdr->FontWidthInPixels * (5 - i))) * 16);
			EVE_VERTEX2II(0, 0, FONT_CUSTOM, ((counter / units) % 10)+1); //+1 as in the converted font the number '0' is in position 1 in the font table
			units *= 10;
		}
#else
		for (i = 0; i < 5; i++)
		{
			EVE_VERTEX2II((((EVE_DISP_WIDTH - (font0_hdr->FontWidthInPixels * 5)) / 2) - (font0_hdr->FontWidthInPixels) + (font0_hdr->FontWidthInPixels * (5 - i))),
					(EVE_DISP_HEIGHT / 2), FONT_CUSTOM, ((counter / units) % 10)+1); //+1 as in the converted font the number '0' is in position 1 in the font table
			units *= 10;
		}
#endif

		EVE_DISPLAY();
		EVE_CMD_SWAP();
		EVE_LIB_EndCoProList();
		EVE_LIB_AwaitCoProEmpty();

		while (eve_read_tag(&key) == 0);

		if (key == 100)
		{
			counter++;
			if (counter == 100000)
			{
				counter = 0;
			}
		}
	} while (1);
}

void eve_example(void)
{
	uint32_t font_end;

	// Initialise the display
	EVE_Init();

	// Calibrate the display
	//eve_calibrate();

	// Load fonts and images
	font_end = eve_init_fonts();

	eve_load_images(font_end);

	// Start example code
	box_create();
}
