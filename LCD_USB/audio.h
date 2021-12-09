/*
 * Audio.h
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <status_fsm.h>

void audio_init(void);
void play_sound(status_fms_state_t state);
void play_sound_(void);
void stop_sound(void);
void check_volume(void);

#endif /* AUDIO_H_ */
