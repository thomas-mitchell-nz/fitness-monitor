/********************************************************
 *
 * diststate.c
 *
 * State to display distance traveled
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 26/04/2022
 *
 ********************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../OrbitOLED/OrbitOLEDInterface.h"
#include "buttons4.h"
#include "display.h"
#include "longPress.h"
#include "diststate.h"
#include "systemData.h"
#include "types.h"

/*******************************************************
 * Global variables
 *******************************************************/
static distUnit_t distUnit = KM;

/*******************************************************
 * State functions: eventHandler, update, draw, cleanup
 *******************************************************/
void distHandler()
{
    /* event handler for distance state */
    if (checkButton (UP) == PUSHED) {
        switch ( distUnit ) // toggles distUnit
        {
        case KM: distUnit = MILES;
            break;
        case MILES: distUnit = KM;
            break;
        }
    }

    if (checkLongPress (DOWN) == LONG_PRESS) {
        // zero stepCount and distance
        displayStr ("     Reset!     ");
        stepCount = 0;
        distance = 0;
        stepGoal = 1000;
    }
}
/*******************************************************/
void distUpdate() { }

/*******************************************************/
void distDraw()
{
    /* renderer for distance state */
    char *str;
    float num = 5.23;

    switch (distUnit)
    {
    case KM:
        num = distance;
        str = "Km";
        break;
    case MILES:
        num = distance / 1.61; // convert to miles
        str = "Miles";
        break;
    }

    OLEDStringDraw ("Distance:", 0, 1);
    displayFloat ("->", num, str, 2); // print to display
}

/*******************************************************/
void distCleanup ()
{
    /* on state exit functionality for distance state */
    clearDisplay ();
}
