/*******************************************************
 *
 * fsm.c
 *
 * Implements finite state machine for milestone2
 *
 * Authors: S.G. Jackson & T.J. Mitchell
 * Last modified:  26/04/22
 *
 *******************************************************/

#include "types.h"
#include "fsm.h"
#include "kernel.h"
#include "buttons4.h"
#include "stepstate.h"
#include "diststate.h"
#include "goalstate.h"

/*******************************************************
 * Global variables
 *******************************************************/

// State types containing function pointers
state_t stepState = {STEP_STATE, stepHandler, stepUpdate, stepDraw, stepCleanup};
state_t distState = {DIST_STATE, distHandler, distUpdate, distDraw, distCleanup};
state_t goalState = {GOAL_STATE, goalHandler, goalUpdate, goalDraw, goalCleanup};

/*******************************************************
 * Configure FSM globals
 *******************************************************/
void initFSM (void)
{
    currentState = stepState;
    registerState (currentState);
}

/*******************************************************
 * Manage state transitions (task)
 *******************************************************/
void stateManager (void)
{
    if (checkButton (LEFT) == PUSHED) {
        changeState(LEFT_BUTTON);
    }

    if (checkButton (RIGHT) == PUSHED) {
        changeState(RIGHT_BUTTON);
    }
}

/*******************************************************
 * Trigger state transition upon function call
 *******************************************************/
void changeState (event_t event)
{
    state_t prevState = currentState;

    currentState = getNewState (prevState, event);

    prevState.cleanup ();

    unregisterState (prevState);

    registerState (currentState);
}

/*******************************************************
 * Finite state machine table for state transitions
 *******************************************************/
state_t getNewState (state_t prevState, event_t e)
{
    state_t newState;

    // Finite state machine
    switch ( prevState.id )
    {
    case STEP_STATE:
        if ( e == LEFT_BUTTON ) newState = distState;
        else if ( e == RIGHT_BUTTON ) newState = goalState;
        break;
    case DIST_STATE:
        if ( e == LEFT_BUTTON ) newState = goalState;
        else if ( e == RIGHT_BUTTON ) newState = stepState;
        break;
    case GOAL_STATE:
        if ( e == LEFT_BUTTON) newState = stepState;
        else if ( e == RIGHT_BUTTON ) newState = distState;
        else if ( e == DOWN_BUTTON ) newState = stepState;
        break;
    default: // state on startup
        newState =  stepState;
    }

    return newState;
}

/*******************************************************
 * Register state functions as individual tasks
 *******************************************************/
void registerState (state_t newState)
{
    iDstateUpdate = k_register_task (newState.update, STATE_PRIORITY, UPDATE_RATE);
    iDstateDraw = k_register_task (newState.draw, STATE_PRIORITY, DRAW_RATE);
    if (!testModeEnabled) {
        iDstateHandler = k_register_task (newState.handler, STATE_PRIORITY, HANDLER_RATE);
    }
}

/*******************************************************
 * Unregister state functions
 *******************************************************/
void unregisterState (state_t prevState)
{
    k_unregister_task (iDstateHandler);
    k_unregister_task (iDstateUpdate);
    k_unregister_task (iDstateDraw);
}

