#ifndef DISPLAY_H_
#define DISPLAY_H_

/*******************************************************
 *
 * display.h
 *
 * Supports display.c module
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 31/03/2022
 * Provenance: 'readAcc.c' module by C.P. Moore on 11 Feb 2020
 *
 *******************************************************/

#include <stdint.h>

/*******************************************************
 * Prototypes
 *******************************************************/

// Function to initialize display
void initDisplay (void);

// Function to display 16 char long message on display
void displayInt (char *str1, int16_t num, char *str2, uint8_t line);

// Function to display float in message
void displayFloat (char *str1, float num, char *str2, uint8_t line);

// Function to clear display
void clearDisplay (void);

// Display string
void displayStr (char *str);

#endif /* DISPLAY_H_ */
