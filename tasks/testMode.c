/*******************************************************
 *
 * testMode.c
 *
 * Test mode functionality to adjust stepCount and
 * distance based on button pushes
 *
 * Authors: T.J. Mitchell
 * Last modified: 19/05/22
 *
 *******************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "inc/tm4c123gh6pm.h"
#include "systemData.h"
#include "testMode.h"
#include "buttons4.h"
#include "switch.h"
#include "kernel.h"
#include "types.h"
#include "sampler.h"
#include "fsm.h"

/*******************************************************
 * Initialize test mode
 *******************************************************/
void initTestMode (void)
{
    testModeEnabled = 0;
}

/*******************************************************
 * Test mode handler to check test mode conditions (task)
 *******************************************************/
void testModeHandler (void)
{
    uint8_t switchState = checkSwitch ();

    if (switchState == SW_DOWN && testModeEnabled) {
        // re-register current state handler task
        iDstateHandler = k_register_task (currentState.handler, STATE_PRIORITY, HANDLER_RATE);
        // re-register sampler
        iDsamplerTask = k_register_task (sampleTask, 0, SAMPLE_RATE);
        // unregister test mode task
        k_unregister_task (iDtestModeTask);
        testModeEnabled = false;
    }
    else if (switchState == SW_UP && !testModeEnabled) {
        // register test mode update task
        iDtestModeTask = k_register_task (updateTestMode, 0, HANDLER_RATE);
        // disable current state handler
        k_unregister_task (iDstateHandler);
        // disable sampler
        k_unregister_task (iDsamplerTask);
        testModeEnabled = true;
    }
}

/*******************************************************
 * Adjust stepCount and distance based on button pushes
 *******************************************************/
void updateTestMode (void)
{
    if (checkButton (UP) == PUSHED) {
        stepCount += 100;
        distance += 0.09;
    }

    if (checkButton (DOWN) == PUSHED) {
        stepCount -= 500;
        distance -= 0.45;
    }

    // prevent values decrementing below zero
    stepCount = (stepCount < 0) ? 0 : stepCount;
    distance = (distance < 0) ? 0 : distance;
}
