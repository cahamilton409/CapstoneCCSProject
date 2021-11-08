/*
 * SPI_LCD.h
 *
 *  This file creates command types for sending data and commands
 *  to the LCD.
 *
 *  Created on: Oct 30, 2021
 *      Author: Emory
 */


#ifndef SPI_LCD_H_
#define SPI_LCD_H_

#include "SPI.h"
#include "defs.h"

void lcd_write_32(uint16_t offset, uint32_t data_in);
void lcd_write_16(uint16_t offset, uint16_t data_in);
void lcd_write_8(uint16_t offset, uint8_t data_in);
uint32_t lcd_read_32();
uint16_t lcd_read_16();
uint8_t lcd_read_8();

void lcd_Command(uint8_t command[]);


#endif /* SPI_LCD_H_ */
