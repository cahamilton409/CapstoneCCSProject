/*
 * Audio.h
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <stdint.h>

extern volatile uint8_t g_volume_level;

void audio_init(void);
void play_sound(void);
void stop_sound(void);
void check_volume(void);

#endif /* AUDIO_H_ */
