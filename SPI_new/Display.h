/*
 * Display.h
 *
 * This file utilizes SPI.h to create a library of display functions
 * to display on an LCD display.
 *
 *  Created on: Oct 30, 2021
 *      Author: Emory
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "SPI_LCD.h"
#include "defs.h"

void display_init();
uint32_t begin(uint8_t type);
uint32_t end();
uint32_t display();
uint32_t clear(uint8_t c, uint8_t s, uint8_t t);
uint32_t vertex_2_ii(uint8_t X, uint8_t Y, uint8_t handle, uint8_t cell);


#endif /* DISPLAY_H_ */
