#ifndef TASKS_SYSTEMDATA_H_
#define TASKS_SYSTEMDATA_H_

/********************************************************
 *
 * systemData.h
 *
 * Supports systemData.c module
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 20/05/2022
 *
 ********************************************************/

/*******************************************************
 * Global variables
 *******************************************************/
int32_t stepCount; // step count in steps
int32_t stepGoal; // step goal in steps
float distance; // distance in km

/*******************************************************
 * Prototypes
 *******************************************************/

// Set data to default values
void resetData (void);

// Check whether goal has been completed
void checkGoal (void);

#endif /* TASKS_SYSTEMDATA_H_ */
