#ifndef READADC_H_
#define READADC_H_

/*******************************************************
 *
 * readADC.h
 *
 * Supports adc module.c
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 27/04/2022
 *
 *******************************************************/
#include <stdint.h>
/*******************************************************
 * Global variables
 *******************************************************/
uint32_t rawADC;

/*******************************************************
 * Prototypes
 *******************************************************/
void initADC (void); // Initialize ADC

#endif /* READADC_H_ */
