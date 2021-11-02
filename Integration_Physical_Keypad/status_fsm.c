/*
 * FSM.c
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 */

#include <status_fsm.h>

void status_fsm_init(status_fsm_t *fsm)
{
    fsm->current_state = idle;
}





