#ifndef LONGPRESS_H_
#define LONGPRESS_H_

/********************************************************
 *
 * longPress.h
 *
 * Supports longPress.c module
 *
 * Authors: T.J. Mitchell
 * Date modified: 27/04/2022
 *
 ********************************************************/
#include <stdint.h>

/*********************************************************
 * Constants
 *********************************************************/
#define LONG_PRESS_COUNT 30 // magic number

/*********************************************************
 * Global variables
 *********************************************************/
enum pressState {NOT_LONG_PRESS, LONG_PRESS};

/*********************************************************
 * Prototypes
 *********************************************************/

// Check whether long press condition satisfied and return result
uint8_t checkLongPress (uint8_t butName);

// Display 16 char long press animation
void updateAnimation (float percentLength);

// Clear animation from display and zero parameters
void clearAnimation (void);

#endif /* LONGPRESS_H_ */
