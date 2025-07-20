#ifndef FSM_H_
#define FSM_H_

/*******************************************************
 *
 * fsm.h
 *
 * Supports fsm.c module
 *
 * Authors: S.G. Jackson & T.J. Mitchell
 * Last modified:  26/04/22
 *
 *******************************************************/

#include "types.h"
#include "kernel.h"

/*******************************************************
 * Constants
 *******************************************************/
#define STATE_PRIORITY  0
#define HANDLER_RATE    20
#define UPDATE_RATE     20
#define DRAW_RATE       10

/*******************************************************
 * Global variables
 *******************************************************/
// State ids for state tasks
taskId_t iDstateHandler;
taskId_t iDstateUpdate;
taskId_t iDstateDraw;

/*******************************************************
 * Prototypes
 *******************************************************/

// Configure FSM globals
void initFSM (void);

// Manage state transitions (task)
void stateManager (void);

// Trigger state transition upon function call
void changeState (event_t event);

// Finite state machine table for state transitions
state_t getNewState (state_t prevState, event_t e);

// Register state functions as individual tasks
void registerState (state_t newState);

// Unregister state functions
void unregisterState (state_t prevState);

#endif /* FSM_H_ */
