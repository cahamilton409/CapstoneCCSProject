/*
 * SPI_LCD.c
 *
 *  Created on: Oct 30, 2021
 *      Author: Emory
 */
#include "SPI_LCD.h"

const uint32_t write_base = 0x80302000;
const uint32_t read_base = 0x00302000;
const uint32_t zeros = 0x00000000;

//Writes 32 bits to a specific register.
// what it does, who calls, how often, variables used, what returns
void lcd_write_32(uint16_t offset, uint32_t data_in)
{
    CS_Off();                                                      //toggle transmit pin

    //address write
    uint32_t address = write_base;                                 //grab base address
    address |= offset;                                             //set offset bits of base
    uint8_t address_broken[4] = {address >> 24, address >> 16,     //breaks 32 bit value into 4, 8 bit chunks
                                 address >> 8, address};
    SPI_Master_Write(address_broken, 4);                           //send desired address over SPI

    //data write
    uint32_t data = zeros;                                         //create a zero variable
    data |= data_in;                                               //set data bits
    uint8_t data_broken[4] = {data >> 24, data >> 16,              //breaks 32 bit value into 4, 8 bit chunks
                              data >> 8, data};
    SPI_Master_Write(data_broken, 4);                              //send desired data over SPI

    CS_On();                                                       //toggle transmit pin
}

//Write 16 bits to a specific register.
void lcd_write_16(uint16_t offset, uint16_t data_in)
{
    CS_Off();                                                      //toggle transmit pin

    //address write
    uint32_t address = write_base;                                 //grab base address
    address |= offset;                                             //set offset bits of base
    uint8_t address_broken[4] = {address >> 24, address >> 16,     //breaks 32 bit value into 4, 8 bit chunks
                                 address >> 8, address};
    SPI_Master_Write(address_broken, 4);                           //send desired address over SPI

    //data write
    uint16_t data = zeros;                                         //create a zero variable
    data |= data_in;                                               //set data bits
    uint8_t data_broken[2] = {data >> 8, data};                    //breaks 16 bit value into 2, 8 bit chunks
    SPI_Master_Write(data_broken, 2);                              //send desired data over SPI

    CS_On();                                                       //toggle transmit pin
}

//Write 8 bits to a specific register.
void lcd_write_8(uint16_t offset, uint8_t data_in)
{
    CS_Off();                                                      //toggle transmit pin

    //address write
    uint32_t address = write_base;                                 //grab base address
    address |= offset;                                             //set offset bits of base
    uint8_t address_broken[4] = {address >> 24, address >> 16,     //breaks 32 bit value into 4, 8 bit chunks
                                 address >> 8, address};
    SPI_Master_Write(address_broken, 4);                           //send desired address over SPI

    //data write
    uint8_t data = zeros;                                          //create a zero variable
    data |= data_in;                                               //set data bits
    uint8_t data_broken[1] = {data};                               //put the 8 bits to be sent into an array
    SPI_Master_Write(data_broken, 1);                              //send desired data over SPI

    CS_On();                                                       //toggle transmit pin
}

//Reads a specific register of the LCD.
uint32_t lcd_read_32(uint16_t offset)
{
    CS_Off();

    uint32_t address = read_base;                                 //grab base address
    address |= offset;                                            //set offset bits of base
    uint8_t address_broken[3] = {address >> 24, address >> 16,    //breaks 32 bit value into 4, 8 bit chunks
                                 address >> 8};
    SPI_Master_Write(address_broken, 3);                          //send desired address over SPI

    uint8_t * buffer = SPI_Master_ReadReg(address, 4);
    uint32_t return_val = zeros;
    return_val |= (buffer[0] << 24);
    return_val |= (buffer[1] << 16);
    return_val |= (buffer[2] << 8);
    return_val |= buffer[3];

    CS_On();

    return return_val;
}

uint16_t lcd_read_16(uint16_t offset)
{
    CS_Off();

    uint32_t address = read_base;                                 //grab base address
    address |= offset;                                            //set offset bits of base
    uint8_t address_broken[2] = {address >> 24, address >> 16,    //breaks 32 bit value into 4, 8 bit chunks
                                 address >> 8};
    SPI_Master_Write(address_broken, 3);                          //send desired address over SPI

    uint8_t * buffer = SPI_Master_ReadReg(address, 2);
    uint16_t return_val = zeros;
    return_val |= (buffer[0] << 8);
    return_val |= buffer[1];

    CS_On();

    return return_val;
}

uint8_t lcd_read_8(uint16_t offset)
{
    CS_Off();

    uint32_t address = read_base;                                 //grab base address
    address |= offset;                                            //set offset bits of base
    uint8_t address_broken[3] = {address >> 24, address >> 16,    //breaks 32 bit value into 4, 8 bit chunks
                                 address >> 8};
    SPI_Master_Write(address_broken, 3);                          //send desired address over SPI

    uint8_t * buffer = SPI_Master_ReadReg(address, 4);
    uint8_t return_val = zeros;
    return_val |= buffer[0];

    CS_On();

    return return_val;
}

//Send a preset command to the LCD.
void lcd_command(uint8_t command[])
{
    CS_Off();                                                      //toggle transmit pin

    SPI_Master_Write(command, 3);                                  //send command from list of predefined commands

    CS_On();                                                       //toggle transmit pin
}
