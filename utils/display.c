/*********************************************************
 *
 * display.c
 *
 * Enables display functionality for fitness monitor
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 31/03/2022
 * Provenance: 'readAcc.c' module by C.P. Moore on 11 Feb 2020
 *
 *********************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../OrbitOLED/OrbitOLEDInterface.h"
#include "driverlib/sysctl.h"
#include "utils/ustdlib.h"

/*********************************************************
 * Initialize display
 *********************************************************/
void initDisplay (void)
{
    // Initialize the Orbit OLED display
    OLEDInitialise ();
}

/*********************************************************
 * Display 16 char long message on display
 *********************************************************/
void displayInt (char *str1, int16_t num, char *str2, uint8_t line)
{
    // Display fits 16 characters wide
    char textBuffer[17];

    // Clear line
    OLEDStringDraw ("                ", 0, line);

    // Format right justified line
    usnprintf(textBuffer, sizeof(textBuffer), "%s %5d %s", str1, num, str2);

    // Update line on display
    OLEDStringDraw (textBuffer, 0, line);
}

/*********************************************************
 * Display message containing float on display
 *********************************************************/
void displayFloat (char *str1, float num, char *str2, uint8_t line)
{
    int16_t LH, RH;

    // type casting to get integers left and right of floating decimal point
    LH = (int) num; // integer value
    RH = (int) ((num - LH) * 100); // decimal value

    // Display fits 16 characters wide
    char textBuffer[17];

    // Clear line
    OLEDStringDraw ("                ", 0, line);

    // Format right justified line


    if (RH < 10) {
        usnprintf(textBuffer, sizeof(textBuffer), "%s  %d.0%d   %s", str1, LH, RH, str2);
    } else {
        usnprintf(textBuffer, sizeof(textBuffer), "%s  %d.%d   %s", str1, LH, RH, str2);
    }

    // Update line on display
    OLEDStringDraw (textBuffer, 0, line);
}

/*********************************************************
 * Clear all text from display
 *********************************************************/
void clearDisplay (void)
{
    uint8_t i;

    for (i = 0; i < 4; i++) { // clear all 4 rows
        OLEDStringDraw ("                ", 0, i);
    }
}


/*********************************************************
 * Display string
 *********************************************************/
void displayStr (char *str)
{
    clearDisplay ();
    OLEDStringDraw (str, 0, 1);
    SysCtlDelay (SysCtlClockGet() / 3);
    clearDisplay ();
}
