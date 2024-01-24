/********************************************************
 *
 * goalstate.c
 *
 * Module to set goals
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 27/04/2022
 *
 ********************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "utils/ustdlib.h"
#include "OrbitOLED/OrbitOLEDInterface.h"
#include "systemData.h"
#include "buttons4.h"
#include "readADC.h"
#include "display.h"
#include "fsm.h"
#include "types.h"

/*******************************************************
 * Global variables
 *******************************************************/
#define MAX_STEP_GOAL 20000
uint32_t scaledADC = 0;

/*******************************************************
 * State functions: eventHandler, update, draw, cleanup
 *******************************************************/
void goalDraw()
{
    /* renderer for goal state */
    OLEDStringDraw ("Current Goal:", 0, 0);
    displayInt ("->", stepGoal, "Steps",1);
    OLEDStringDraw ("New Goal:", 0, 2);
    displayInt ("->", scaledADC, "Steps", 3);
}

/*******************************************************/
void goalUpdate ()
{
    ADCProcessorTrigger(ADC0_BASE, 3); // trigger ADC

    uint32_t tmp = 0; // temp

    // Calculates step value from ADC resolution
    tmp = rawADC * (MAX_STEP_GOAL / 4000) / 100 ;

    // Sets value to max if above max
    tmp = (tmp > 200) ? 200 : tmp;

    // Sets stepValue
    scaledADC = tmp * 100;
}

/*******************************************************/
void goalHandler ()
{
    /* event handler for goal state */
    if (checkButton (DOWN) == PUSHED) {
        stepGoal = scaledADC; // set step goal
        changeState (DOWN_BUTTON); // change state
    }
}

/*******************************************************/
void goalCleanup ()
{
    /* on state exit functionality for goal state */
    clearDisplay ();
}
