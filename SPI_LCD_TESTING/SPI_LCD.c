/*
 * SPI_LCD.c
 *
 *  Created on: Oct 30, 2021
 *      Author: Emory
 */
#include "SPI_LCD.h"

const uint32_t write_base = 0x80302000;
const uint32_t zeros = 0x00000000;

void LCD_Write32(uint16_t offset, uint32_t data_in)
{
    CS_Off();

    //address write
    uint32_t address = write_base;
    address |= offset;
    uint8_t address_broken[4] = {address >> 24, address >> 16, address >> 8, address};
    SPI_Master_Write(address_broken, 4);

    //data write
    uint32_t data = zeros;
    data |= data_in;
    uint8_t data_broken[4] = {data >> 24, data >> 16, data >> 8, data};
    SPI_Master_Write(data_broken, 4);

    CS_On();
}

void LCD_Write16(uint16_t offset, uint16_t data_in)
{
    CS_Off();

    //address write
    uint32_t address = write_base;
    address |= offset;
    uint8_t address_broken[4] = {address >> 24, address >> 16, address >> 8, address};
    SPI_Master_Write(address_broken, 4);

    //data write
    uint16_t data = zeros;
    data |= data_in;
    uint8_t data_broken[2] = {data >> 8, data};
    SPI_Master_Write(data_broken, 2);

    CS_On();
}

void LCD_Write8(uint16_t offset, uint8_t data_in)
{
    CS_Off();

    //address write
    uint32_t address = write_base;
    address |= offset;
    uint8_t address_broken[4] = {address >> 24, address >> 16, address >> 8, address};
    SPI_Master_Write(address_broken, 4);

    //data write
    uint8_t data = zeros;
    data |= data_in;
    uint8_t data_broken[1] = {data};
    SPI_Master_Write(data_broken, 1);

    CS_On();
}

void LCD_Read()
{

}

void LCD_Command(uint8_t command[])
{
    CS_Off();
    SPI_Master_Write(command, 3);

    CS_On();
}
