#include <stdint.h>
#include <stdio.h>
#include "Clock.h"
#include <msp430.h>

void initClocks(uint32_t mclkFreq)
{
    UCS_initClockSignal(
       UCS_FLLREF,
       UCS_REFOCLK_SELECT,
       UCS_CLOCK_DIVIDER_1);

    UCS_initClockSignal(
       UCS_ACLK,
       UCS_REFOCLK_SELECT,
       UCS_CLOCK_DIVIDER_1);

    UCS_initFLLSettle(
        mclkFreq/1000,
        mclkFreq/32768);
}

void Clock_Delay1us(uint32_t n){
    n = (961 * n) / 1000; // 1 us, tuned at 25 MHz
    volatile uint32_t i;
    for(i=n; i > 0; i--){
        // Nothing
    }
}

void Clock_Delay1ms(uint32_t n){
    n = 960.83 * n; // 1 ms, tuned at 25 MHz
    volatile uint32_t i;
    for(i=n; i > 0; i--){
        // Nothing
    }
}
