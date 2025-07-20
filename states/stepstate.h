#ifndef STEPSTATE_H_
#define STEPSTATE_H_

/*******************************************************
 *
 * stepstate.h
 *
 * Supports stepstate.c module
 *
 * Authors: S.G. Jackson & T.J. Mitchell
 * Last modified:  26/04/22
 *
 *******************************************************/

/*******************************************************
 * Typedefs
 *******************************************************/
typedef enum {
    MAGNITUDE,
    PERCENT
} stepUnit_t;

/*******************************************************
 * Prototypes
 *******************************************************/
void stepUpdate (void); // update
void stepHandler (void); // event handler
void stepDraw (void); // renderer
void stepCleanup (void); // on state exit

#endif /* STEPSTATE_H_ */
