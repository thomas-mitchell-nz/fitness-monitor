#ifndef TASKS_SAMPLER_H_
#define TASKS_SAMPLER_H_

/*******************************************************
 *
 * sampler.h
 *
 * Supports sampler.h module
 *
 * Authors: T.J. Mitchell
 * Last modified: 19/05/22
 *
 *******************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "orientation.h"

/*******************************************************
 * Constants
 *******************************************************/
#define STEP_DIST       0.0007;
#define SAMPLE_RATE     3

/*******************************************************
 * Prototypes
 *******************************************************/

// Initialize Sampler
void initSampler (void);

// Fill buffer
void fillBuffer (void);

// Detect step from acceleration data (task)
void sampleTask (void);

// Implement differentiator to account for transition
float getDiff (int16_t currentInput, int16_t prevInput);

// Determine if step criteria is met
int16_t checkStep (int16_t signal, int16_t change);

// Implement low-pass noise filter
void lowPass (int16_t *input, float a);

// Check whether current orientation close to reference orientation
bool withinReferenceTol (angles_t angles);

#endif /* TASKS_SAMPLER_H_ */
