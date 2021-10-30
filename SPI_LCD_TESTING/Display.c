/*
 * Display.c
 *
 *  Created on: Oct 30, 2021
 *      Author: Emory
 */
#include "Display.h"

void Display_Init()
{
    LCD_Write16(REG_HCYCLE, 548);
    LCD_Write16(REG_HOFFSET, 43);
    LCD_Write16(REG_HSYNC0, 0);
    LCD_Write16(REG_HSYNC1, 41);
    LCD_Write16(REG_VCYCLE, 292);
    LCD_Write16(REG_VOFFSET, 12);
    LCD_Write16(REG_VSYNC0, 0);
    LCD_Write16(REG_VSYNC1, 10);
    LCD_Write8(REG_SWIZZLE, 0);
    LCD_Write8(REG_PCLK_POL, 1);
    LCD_Write8(REG_CSPREAD, 1);
    LCD_Write16(REG_HSIZE, 480);
    LCD_Write16(REG_VSIZE, 272);

    LCD_Write32(RAM_DL+0, 0x02111000);
    LCD_Write32(RAM_DL + 4, 0x26111000);
    LCD_Write32(RAM_DL + 8, 0x00000000);

    /*LCD_Write8(REG_DLSWAP |= 0x10);

    gpio_dir = SPI_READ(REG_GPIO_DIR);
    gpio = SPI_READ(REG_GPIO)
    LCD_Write32(REG_GPIO_DIR |= (0x80 | gpio_dir));
    LCD_Write32(REG_GPIO |= (0x080 | gpio));
    LCD_Write32(REG_PCLK |= 0x500)*/
}
