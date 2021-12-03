/*
 * FSM.h
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 */

#ifndef STATUS_FSM_H_
#define STATUS_FSM_H_


// Type Definitions
typedef enum {
    idle,
    change_page,
    send_key,
    move_key,
} status_fms_state_t;

typedef struct {
    status_fms_state_t     current_state;      // Current state of the FSM
} status_fsm_t;

// Function Prototypes
void status_fsm_init(status_fsm_t *fsm);

#endif /* STATUS_FSM_H_ */
