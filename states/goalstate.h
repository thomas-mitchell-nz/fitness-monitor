#ifndef GOALSTATE_H_
#define GOALSTATE_H_

/*******************************************************
 *
 * goalstate.h
 *
 * Supports goalstate.c module
 *
 * Authors: S.G. Jackson & T.J. Mitchell
 * Last modified: 26/04/22
 *
 *******************************************************/

/*******************************************************
 * Prototypes
 *******************************************************/
void goalUpdate (void); // update
void goalHandler (void); // event handler
void goalDraw (void); // renderer
void goalCleanup (void); // on state exit

#endif /* GOALSTATE_H_ */
