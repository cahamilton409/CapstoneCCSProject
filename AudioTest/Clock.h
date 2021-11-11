#include "driverlib.h"
#include "msp430.h"
#include <stdbool.h>
#include <stdint.h>

/*
 *  @ details   Initialize the MCLK
 *  @ param mclkFreq
 *  @ return none
 *  @ note assumes 25 MHz
 */
void initClocks(uint32_t mclkFreq);

/*
 *  @ details    Delay operation by 1 or more microseconds
 *  @ param t, number of microseconds to delay
 *  @ return none
 */
void Clock_Delay1us(uint32_t t);

/*
 *  @ details    Delay operation by 1 or more milliseconds
 *  @ param t, number of milliseconds to delay
 *  @ return none
 */
void Clock_Delay1ms(uint32_t t);
