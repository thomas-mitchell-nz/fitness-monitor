/*******************************************************
 *
 * sampler.c
 *
 * Samples accelerometer to get step count
 *
 * Authors: T.J. Mitchell
 * Last modified: 19/05/22
 *
 *******************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "../OrbitOLED/OrbitOLEDInterface.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "orientation.h"
#include "accelerometer.h"
#include "systemData.h"
#include "display.h"
#include "sampler.h"
#include "types.h"
#include "buffer.h"
#include "math.h"

/*******************************************************
 * Global variables
 *******************************************************/
static buffer3_t buffer3;
static angles_t prevAngles;

/*******************************************************
 * Initialize Sampler
 *******************************************************/
void initSampler (void)
{
    setReference(getAccData());

    prevAngles = referenceOri;

    // initialize 3d buffer for acc readings
    initBuffer(&buffer3.x);
    initBuffer(&buffer3.y);
    initBuffer(&buffer3.z);
}

/*******************************************************
 * Fill buffer with real-time acceleration data
 *******************************************************/
void fillBuffer (void)
{
    // get acceleration data from acc utility
    vector3_t rawAcc = getAccData();

    // write x y z coordinates to buffer
    writeBuffer(&buffer3.x, rawAcc.x);
    writeBuffer(&buffer3.y, rawAcc.y);
    writeBuffer(&buffer3.z, rawAcc.z);
}

/*******************************************************
 * Detect step from acceleration data
 *******************************************************/
void sampleTask (void)
{
    static uint8_t counter = 0;
    static int16_t prevAccMag;
    int16_t threshold = 4;
    int16_t accMag;
    vector3_t accAvg;

    // get the current buffer averages in x y z directions
    accAvg.x = getBufferAverage (&buffer3.x);
    accAvg.y = getBufferAverage (&buffer3.y);
    accAvg.z = getBufferAverage (&buffer3.z);

    // skip first few runs while buffer gets filled
    if (counter > 12) {
        // get the magnitude of acceleration vector
        accMag = sqrt(accAvg.x*accAvg.x+accAvg.y*accAvg.y+accAvg.z*accAvg.z);
    } else {
        accMag = 0;
        counter++;
    }

    // check for step
    if (accMag - prevAccMag > threshold) {
        stepCount += 1; // increase step count
        distance += STEP_DIST;
    }

    // store previous acceleration magnitude
    prevAccMag = accMag;
}

/*
void sampleTask (void)
{
    static bool stepDetected = false;
    static int16_t prevPaceRate = 0;
    static int16_t counter = 0;
    int16_t currentPaceRate;
    int16_t paceDiff;
    vector3_t rawAcc;
    vector3_t accAvg;
    angles_t angles;

    // get acceleration data from acc utility
    rawAcc = getAccData();

    // write x y z coordinates to buffer
    writeBuffer(&buffer3.x, rawAcc.x);
    writeBuffer(&buffer3.y, rawAcc.y);
    writeBuffer(&buffer3.z, rawAcc.z);

    // get the current buffer averages in x y z directions
    accAvg.x = getBufferAverage (&buffer3.x);
    accAvg.y = getBufferAverage (&buffer3.y);
    accAvg.z = getBufferAverage (&buffer3.z);

    // get pitch and roll from acc readings
    angles = getOrientation (accAvg);

    // pace frequency pre-scaled by 100, roll provides more reliable angle readings
    currentPaceRate = abs (angles.roll - prevAngles.roll) * SAMPLE_RATE / 360 * 100;

    // low-pass filter current pace
    lowPass (&currentPaceRate, 0.6);

    // use differentiator to search for transition
    paceDiff = getDiff (currentPaceRate, prevPaceRate);

    // store previous angles
    prevAngles = angles;

    // store previous pace rate
    prevPaceRate = currentPaceRate;

    // check for step
    stepDetected = checkStep (currentPaceRate, paceDiff);

    // counter to filter out high frequencies so repeated steps are not recorded
    counter += 1;
    if (counter > 5 && stepDetected) {
        counter = 0;
        stepCount += 1; // increase step count
        distance += STEP_DIST;
    }
}*/

/*******************************************************
 * Implement differentiator to account for transition
 *******************************************************/
float getDiff (int16_t currentInput, int16_t prevInput)
{
    return abs((currentInput - prevInput) * SAMPLE_RATE);
}

/*******************************************************
 * Determine if step criteria is met
 *******************************************************/
int16_t checkStep (int16_t signal, int16_t change)
{
    if (abs(signal) > 50 && change > 60) {
        return 1;
    }

    return 0;
}

/*******************************************************
 * Implement low-pass noise filter
 *******************************************************/
void lowPass (int16_t *input, float a)
{
    static int16_t prevOut = 0;
    int16_t output;

    output = a*prevOut + (1-a)*(*input);

    *input = output;

    prevOut = output;
}

/*******************************************************
 * Check whether current orientation close to reference orientation
 *******************************************************/
bool withinReferenceTol (angles_t angles)
{
    return ((angles.roll - referenceOri.roll) > 45 || (angles.pitch - referenceOri.pitch) > 45);
}
