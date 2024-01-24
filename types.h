#ifndef TYPES_H_
#define TYPES_H_

/*******************************************************
 *
 * types.h
 *
 * Supports typedefs globally
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 26/04/2022
 *
 *******************************************************/

#include <stdint.h>
#include "kernel.h"
#include "buffer.h"

/*******************************************************
 * Typedefs
 *******************************************************/
typedef void (*action)(); // function pointer type

typedef enum {
    STEP_STATE,
    DIST_STATE,
    GOAL_STATE
} stateId_t; // possible states

typedef enum {
    RESET = -1,
    LEFT_BUTTON,
    RIGHT_BUTTON,
    DOWN_BUTTON
} event_t; // possible events

typedef struct {
    stateId_t id; // state index
    action handler; // events handler
    action update;
    action draw;
    action cleanup;
} state_t; // state data type

typedef enum {
    RAW,
    GRAVITY,
    SI
} unit_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} vector3_t;

/*******************************************************
 * Global variables
 *******************************************************/
state_t currentState; // current system state
bool testModeEnabled;

// task ids
taskId_t iDbuttonsTask;
taskId_t iDstateManager;
taskId_t iDtestHandler;
taskId_t iDsamplerTask;
taskId_t iDgoalTask;
taskId_t iDbufferTask;

#endif /* TYPES_H_ */
