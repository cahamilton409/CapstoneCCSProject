/*
 * Audio.h
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <status_fsm.h>

void Audio_Init(void);

void Play_Sound(FSMState State);

#endif /* AUDIO_H_ */
