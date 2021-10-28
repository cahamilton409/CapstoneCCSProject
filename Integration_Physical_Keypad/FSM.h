/*
 * FSM.h
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 */

#ifndef FSM_H_
#define FSM_H_


// Type Definitions
typedef enum {
    Idle,
    ChangePage,
    SendKey,
    MoveKey,
} FSMState;

typedef struct {
    FSMState     CurrentState;      // Current state of the FSM
} FSMType;

// Function Prototypes
void Key_Press_FSM_Init(FSMType *FSM);
void Change_State(FSMType *FSM, FSMState);

#endif /* FSM_H_ */
