/********************************************************
 *
 * longPress.c
 *
 * Enables long press functionality
 *
 * Authors: T.J. Mitchell
 * Date modified: 27/04/2022
 *
 ********************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "../OrbitOLED/OrbitOLEDInterface.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "buttons4.h"
#include "longPress.h"
#include "display.h"

/*********************************************************
 * Global variables
 *********************************************************/
static int8_t currentLength = 0; // current animation length
static int8_t prevLength = 0; // previous animation length
static int32_t counter = 0;
static float percent;

static char animation[17]; // animation str
static char chr = '=';

/*********************************************************
 * Check whether long press condition satisfied and return result
 *********************************************************/
uint8_t checkLongPress (uint8_t butName)
{
    switch ( checkButton (butName) ) // check desired button for press
    {
    case PUSHED:
        counter = 1; // set counter
        break;
    case RELEASED:
        counter = 0; // zero counter
        clearAnimation ();
        break;
    case NO_CHANGE:
        if (counter > 0) counter++; // increment counter
        break;
    }

    // counter % to long press threshold
    percent = (float) counter / LONG_PRESS_COUNT;

    if (counter > 0 && percent <= 1) { // if long press condition
        updateAnimation (percent);
    }

    if (counter > LONG_PRESS_COUNT) { // if long press condition satisfied
        clearAnimation (); // clear animation from display
        counter = 0;
        return LONG_PRESS;
    }

    return NOT_LONG_PRESS;
}

/*********************************************************
 * Display 16 char long press animation
 *********************************************************/
void updateAnimation (float percentLength)
{
    currentLength = 16 * percentLength; // update current length

    if (currentLength > prevLength) { // if extra character
        strncat (animation, &chr, 1); // add extra character to animation str
        OLEDStringDraw (animation, 0, 3); // draw animation
        prevLength = currentLength; // store previous animation length
    }
}

/*********************************************************
 * Clear animation from display and zero parameters
 *********************************************************/
void clearAnimation (void)
{
    OLEDStringDraw ("                ", 0, 3); // clear row
    strcpy(animation, ""); // empty animation str
    // zero animation parameters
    currentLength = 0;
    prevLength = 0;
    percent = 0;
}
