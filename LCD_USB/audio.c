/*
 * Audio.c
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 */

#include <audio.h>
#include <stdint.h>
#include <stdio.h>
#include "driverlib.h"
#include "msp430.h"
#include "display.h"

#define TIMER_PERIOD 1000

volatile uint8_t g_volume_level;


uint16_t duties[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
uint8_t aLastState; // Previous state (0 or 1) of Pin A
uint8_t bLastState; // Previous state (0 or 1) of Pin B
uint8_t aState; // Current state of Pin A (0 or 1)
uint8_t bState; // Current state of Pin B (0 or 1)
uint8_t volume; // A test variable to track whether turning the encoder increases or decreases this value
extern Timer_A_outputPWMParam param = {0};

void audio_init(void)
{
    GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN0); // P4.0 is an input
    GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN7); // P3.7 is an input
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN0); // P2.0 is a buzzer output

    param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_32; //
    param.timerPeriod = TIMER_PERIOD;
    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
}


void play_sound(void)
{
    Timer_A_outputPWM(TIMER_A1_BASE, &param);
}

void stop_sound(void)
{
    Timer_A_stop(TIMER_A1_BASE);

}

void check_volume(void)
{
    aState = GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN7);
    bState = GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN0);
    if(aState == 1 && bState == 1)
    {
        param.dutyCycle = 0;
        g_volume_level = 0;
    }
    else if(aState == 0 && bState == 1)
    {
        param.dutyCycle = duties[4];
        g_volume_level = 1;
    }
    else if(aState == 0 && bState == 0)
    {
        param.dutyCycle = duties[6];
        g_volume_level = 2;
    }
    else
    { // 10
        param.dutyCycle = duties[9];
        g_volume_level = 3;
    }
}

