#ifndef ORIENTATION_H_
#define ORIENTATION_H_

/*******************************************************
 *
 * orientation.h
 *
 * Supports orientation calculation
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 31/03/2022
 *
 *******************************************************/

#include "types.h"

/*******************************************************
 * Typedefs
 *******************************************************/
typedef struct {
    float roll;
    float pitch;
} angles_t;


/*******************************************************
 * Global variables
 *******************************************************/
angles_t referenceOri;

/*******************************************************
 * Prototypes
 *******************************************************/

// Calculate and return the current orientation
angles_t getOrientation(vector3_t acc);

// Store current orientation as reference
void setReference (vector3_t acc);

// Display current reference orientation
void displayReference ();

#endif
