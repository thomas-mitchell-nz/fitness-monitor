#ifndef DISTSTATE_H_
#define DISTSTATE_H_

/*******************************************************
 *
 * diststate.h
 *
 * Supports diststate.c module
 *
 * Authors: S.G. Jackson & T.J. Mitchell
 * Last modified:  26/04/22
 *
 *******************************************************/

/*******************************************************
 * Typedefs
 *******************************************************/
typedef enum {
    KM,
    MILES
} distUnit_t;

/*******************************************************
 * Prototypes
 *******************************************************/
void distUpdate (void); // update
void distHandler (void); // event handler
void distDraw (void); // renderer
void distCleanup (void); // on state exit

#endif /* DISTSTATE_H_ */
