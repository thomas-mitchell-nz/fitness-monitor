#ifndef TESTMODE_H_
#define TESTMODE_H_

/*******************************************************
 *
 * testMode.h
 *
 * Supports testMode.c module
 *
 * Authors: T.J. Mitchell
 * Last modified:  19/05/22
 *
 *******************************************************/

#include "kernel.h"

/*******************************************************
 * Global variables
 *******************************************************/
taskId_t iDtestModeTask;

/*******************************************************
 * Prototypes
 *******************************************************/

// Initialize test mode
void initTestMode (void);

// Test mode handler to check test mode conditions (task)
void testModeHandler (void);

// Adjust stepCount and distance based on button pushes
void updateTestMode (void);

#endif /* TESTMODE_H_ */
