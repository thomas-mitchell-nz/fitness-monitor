#ifndef SWITCH_H_
#define SWITCH_H_

/********************************************************
 *
 * switches.h
 *
 * Supports switches.c module
 *
 * Authors: T.J. Mitchell
 * Date modified: 27/04/2022
 *
 ********************************************************/

#include <stdint.h>
#include <stdbool.h>

/*******************************************************
 * Constants
 *******************************************************/
#define SW1_PERIPH      SYSCTL_PERIPH_GPIOA
#define SW1_PORT_BASE   GPIO_PORTA_BASE
#define SW1_PIN         GPIO_PIN_7

/*******************************************************
 * Global variables
 *******************************************************/
enum switchStates {SW_DOWN, SW_UP}; // possible switch states

/*******************************************************
 * Prototypes
 *******************************************************/

// configure switch
void initSwitch (void);

// check switch state
bool checkSwitch (void);

#endif /* SWITCH_H_ */
