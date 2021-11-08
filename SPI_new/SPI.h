/*
 * SPI.h
 *
 * This file creates all the functions to send and receive signals
 * over SPI. It also creates and interrupt routing for sending and
 * receiving SPI.
 *
 *  Created on: Oct 28, 2021
 *      Author: Emory
 */

#ifndef SPI_H_
#define SPI_H_

#include "defs.h"

typedef enum SPI_ModeEnum{
    IDLE_MODE,
    TX_REG_ADDRESS_MODE,
    RX_REG_ADDRESS_MODE,
    TX_DATA_MODE,
    RX_DATA_MODE,
    TIMEOUT_MODE
} SPI_Mode;

SPI_Mode SPI_Master_WriteReg(uint8_t reg_addr, uint8_t *reg_data, uint8_t count);
SPI_Mode SPI_Master_Write(uint8_t *reg_data, uint8_t count);
uint8_t * SPI_Master_ReadReg(uint8_t reg_addr, uint8_t count);
void CopyArray(uint8_t *source, uint8_t *dest, uint8_t count);
void SendUCA0Data(uint8_t val);
void SPI_Init();
void CS_On();
void CS_Off();


#endif /* SPI_H_ */
