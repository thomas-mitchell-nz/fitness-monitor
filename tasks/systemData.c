/********************************************************
 *
 * systemData.c
 *
 * Stores and manipulates system data
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 20/05/2022
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
#include "display.h"

/*******************************************************
 * Set data to default values
 *******************************************************/
void resetData (void)
{
    stepCount = 0;
    distance = 0;
    stepGoal = 1000;
}

/*******************************************************
 * Check whether goal has been completed
 *******************************************************/
void checkGoal (void)
{
    static bool handled = false;

    if (stepCount < stepGoal && handled) {
        handled = false;
    }

    if (stepCount >= stepGoal && !handled) {
        displayStr (" Goal Complete! ");
        handled = true;
    }
}
