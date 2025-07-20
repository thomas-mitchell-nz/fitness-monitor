/*******************************************************
 *
 * main.c
 *
 * Main program file for fitness monitor
 *
 * Authors: S.G. Jackson & T.J. Mitchell
 * Last modified:  20/05/22
 *
 *******************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"
#include "../OrbitOLED/OrbitOLEDInterface.h"
#include "utils/ustdlib.h"
#include "accelerometer.h"
#include "buttons4.h"
#include "switch.h"
#include "readADC.h"
#include "display.h"
#include "longPress.h"
#include "sampler.h"
#include "systemData.h"
#include "stepstate.h"
#include "diststate.h"
#include "goalstate.h"
#include "testMode.h"
#include "kernel.h"
#include "types.h"
#include "fsm.h"

/*******************************************************
 * Constants
 *******************************************************/
#define MAX_TASKS       20
#define SYSTICK_RATE    20

/*******************************************************
 * Prototypes
 *******************************************************/
void init_modules (void);
void register_tasks (void);

/*******************************************************
 * Support functions
 *******************************************************/
void init_modules (void)
{
    /* initialize background tasks */
    resetData ();
    initDisplay ();
    initButtons ();
    initSwitch ();
    initTestMode ();
    initADC ();
    initAcc ();
    initSampler ();
    initFSM ();
}

/*******************************************************/
void register_tasks (void)
{
    /* register background tasks with kernel */
    iDbuttonsTask = k_register_task (updateButtons, 0, SYSTICK_RATE);
    iDstateManager = k_register_task (stateManager, 0, HANDLER_RATE);
    iDtestHandler = k_register_task (testModeHandler, 0, HANDLER_RATE);
    iDbufferTask = k_register_task (fillBuffer, 0, SYSTICK_RATE);
    iDsamplerTask = k_register_task (sampleTask, 0, SAMPLE_RATE);
    iDgoalTask = k_register_task (checkGoal, 0, HANDLER_RATE);
}

/*******************************************************
 * Main
 *******************************************************/
int main (void)
  {
    k_init (MAX_TASKS, SYSTICK_RATE); // initialize kernel

    init_modules (); // initialize modules

    register_tasks (); // register tasks with kernel

    k_start (); // start the kernel (forever)
}
