/********************************************************
 *
 * switches.c
 *
 * Module to enable switch functionality
 *
 * Authors: T.J. Mitchell
 * Date modified: 27/04/2022
 *
 ********************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <switch.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "inc/tm4c123gh6pm.h"

/*******************************************************
 * configure switch
 *******************************************************/
void initSwitch (void)
{
    // Configure SW1
    SysCtlPeripheralEnable (SW1_PERIPH); // enable peripheral
    GPIOPinTypeGPIOInput (SW1_PORT_BASE, SW1_PIN); // specify pin as input
    // configure switch as weak pull down
    GPIOPadConfigSet (SW1_PORT_BASE, SW1_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
}

/*******************************************************
 * check switch state
 *******************************************************/
bool checkSwitch (void)
{
    // Return switch state; true means UP, false means DOWN
    return GPIOPinRead (SW1_PORT_BASE, SW1_PIN);
}
