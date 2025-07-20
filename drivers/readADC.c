/*******************************************************
 *
 * readADC.c
 *
 * Reads potentiometer value
 *
 * Authors: S.G. Jackson
 * Date modified: 27/04/2022
 *
 *******************************************************/

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
#include "readADC.h"

/*******************************************************
 * ADC interrupt handler for ADC interrupt
 *******************************************************/
void ADCIntHandler(void)
{
    ADCSequenceDataGet(ADC0_BASE, 3, &rawADC);
    ADCIntClear(ADC0_BASE, 3);
}

/*******************************************************
 * Initialize ADC
 *******************************************************/
void initADC (void)
{
    // The ADC0 peripheral must be enabled for configuration and use.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    
    // Configure step 0 on sequence 3
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);

    ADCSequenceEnable(ADC0_BASE, 3);

    ADCIntRegister (ADC0_BASE, 3, ADCIntHandler);

    ADCIntEnable(ADC0_BASE, 3);

    rawADC = 0;
}
