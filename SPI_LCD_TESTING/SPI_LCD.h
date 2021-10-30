/*
 * SPI_LCD.h
 *
 *  Created on: Oct 30, 2021
 *      Author: Emory
 */


#ifndef SPI_LCD_H_
#define SPI_LCD_H_

#include "SPI.h"

void LCD_Write32(uint16_t offset, uint32_t data_in);
void LCD_Write16(uint16_t offset, uint16_t data_in);
void LCD_Write8(uint16_t offset, uint8_t data_in);
void LCD_Read();
void LCD_Command(uint8_t command[]);


#endif /* SPI_LCD_H_ */
