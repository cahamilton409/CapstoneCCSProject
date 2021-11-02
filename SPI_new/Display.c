/*
 * Display.c
 *
 *  Created on: Oct 30, 2021
 *      Author: Emory
 */
#include "Display.h"

//Runs through the LCD initialization routine.
void display_init()
{
    lcd_write_16(REG_HCYCLE, 548);
    lcd_write_16(REG_HOFFSET, 43);
    lcd_write_16(REG_HSYNC0, 0);
    lcd_write_16(REG_HSYNC1, 41);
    lcd_write_16(REG_VCYCLE, 292);
    lcd_write_16(REG_VOFFSET, 12);
    lcd_write_16(REG_VSYNC0, 0);
    lcd_write_16(REG_VSYNC1, 10);
    lcd_write_8(REG_SWIZZLE, 0);
    lcd_write_8(REG_PCLK_POL, 1);
    lcd_write_8(REG_CSPREAD, 1);
    lcd_write_16(REG_HSIZE, 480);
    lcd_write_16(REG_VSIZE, 272);

    lcd_write_32(RAM_DL+0, 0x02111000);
    lcd_write_32(RAM_DL + 4, 0x26111000);
    lcd_write_32(RAM_DL + 8, 0x00000000);

    // add reads

    lcd_write_8(REG_PCLK, 5);

}

//Begins a display list.
uint32_t begin(uint8_t type)
{
    uint32_t return_val = 0x00000000;   //create a value to modify
    return_val |= 0x1F000000;           //set top two bytes
    return_val |= type;                 //set lower two bytes based on input
    return return_val;
}

//Finishes a display list.
uint32_t end()
{
    return 0x21000000;                  //returns this value, chosen to be a function and not a define for consistency
}

//Display current display list.
uint32_t display()
{
    return 0x00000000;                  //returns 0, chosen to be a function and not a define for consistency
}

//Clears the lcd based on c, s, t.
uint32_t clear(uint8_t c, uint8_t s, uint8_t t)
{
    uint32_t return_val = 0x00000000;   //create a value to modify
    return_val |= 0x26000000;           //set top two bytes
    return_val |= c << 2;               //set c bit
    return_val |= s << 1;               //set s bit
    return_val |= t;                    //set t bit
    return return_val;
}

//Specifies a location on the LCD with unsigned position coordinates.
uint32_t vertex_2_ii(uint8_t X, uint8_t Y, uint8_t handle, uint8_t cell)
{
    uint32_t return_val = 0x20000000;   //create a value to modify
    return_val |= (X << 21);            //set X bits
    return_val |= (Y << 12);            //set Y bits
    return_val |= (handle << 7);        //set handle bits
    return_val |= cell;                 //set cell bits
    return return_val;
}

