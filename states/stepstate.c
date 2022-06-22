/********************************************************
 *
 * steps.c
 *
 * Module to display number of steps
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 26/04/2022
 *
 ********************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../OrbitOLED/OrbitOLEDInterface.h"
#include "buttons4.h"
#include "display.h"
#include "longPress.h"
#include "stepstate.h"
#include "types.h"
#include "systemData.h"

/*******************************************************
 * Global variables
 *******************************************************/
stepUnit_t stepUnit = MAGNITUDE;

/*******************************************************
 * State functions: eventHandler, update, draw, cleanup
 *******************************************************/
void stepHandler (void)
{
    /* event handler for step state */
    if (checkButton (UP) == PUSHED) {
        switch ( stepUnit ) // toggles stepUnit
        {
        case MAGNITUDE: stepUnit = PERCENT;
            break;
        case PERCENT: stepUnit = MAGNITUDE;
            break;
        }
    }

    if (checkLongPress (DOWN) == LONG_PRESS) {
        // zero stepCount and distance
        displayStr ("     Reset!     ");
        resetData ();
    }
}

/*******************************************************/
void stepUpdate (void) {}

/*******************************************************/
void stepDraw (void)
{
    /* renderer for step state */
    char *str;
    int num;

    switch (stepUnit)
    {
    case MAGNITUDE:
        str = "Steps";
        num = stepCount;
        break;
    case PERCENT:
        str = "%Goal";
        num = stepCount * 100 / stepGoal;
        break;
    }

    OLEDStringDraw ("Step Count:", 0, 1);
    displayInt ("->", num, str, 2); // print to display
}

/*******************************************************/
void stepCleanup ()
{
    /* on state exit functionality for distance state */
    clearDisplay ();
}
