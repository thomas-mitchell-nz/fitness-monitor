/*********************************************************
 *
 * orientation.c
 *
 * Calculate orientation of Tiva board from accelerometer data
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 31/03/2022
 *
 *********************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "orientation.h"
#include "accelerometer.h"
#include "display.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "../OrbitOLED/OrbitOLEDInterface.h"

/*******************************************************
 * Calculate roll and pitch of Tiva board
 *******************************************************/
angles_t getOrientation(vector3_t acc)
{
    angles_t angles;

    // flip sign if -ve for correct quadrant
    if (acc.z > 0) {
        acc.z *= -1;
    }

    // pre-scale angles
    acc.x *= 1000;
    acc.y *= 1000;
    acc.z *= 1000;

    // calculate angles
    angles.roll = atan2(acc.y, acc.z) * 180 / 3.14;
    angles.pitch = atan2(-acc.x, sqrt((acc.y)^2+(acc.z)^2)) * 180 / 3.14;

    return angles;
}

/*******************************************************
 * Stores current orientation as reference
 *******************************************************/
void setReference (vector3_t acc) {
    referenceOri = getOrientation(acc);
}

/*******************************************************
 * Display current reference orientation
 *******************************************************/
void displayReference ()
{
    SysTickIntDisable();

    OLEDStringDraw ("Orientation", 0, 0);
    displayInt ("X",  referenceOri.roll, "Deg", 1);
    displayInt ("Y",  referenceOri.pitch,"Deg", 2);
    OLEDStringDraw ("                ", 0, 3);

    SysCtlDelay (SysCtlClockGet());  // Pause for 3 sec

    SysTickIntEnable();
}
