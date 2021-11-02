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

#endif /* AUDIO_H_ */
