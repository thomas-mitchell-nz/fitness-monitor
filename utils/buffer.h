#ifndef BUFFER_H_
#define BUFFER_H_

/*******************************************************
 *
 * buffer.h
 *
 * Support for c ircular buffer functionality
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 31/03/2022
 * Provenance: 'circBufT.h' module by P.J. Bones on 7 Mar 2017
 *
 *******************************************************/

#include <stdint.h>
#include "types.h"

/*******************************************************
 * Typedefs
 *******************************************************/
typedef struct {
    int32_t size;
    uint32_t windex;
    uint32_t rindex;
    int32_t *data;
} buffer_t;

typedef struct {
    buffer_t x;
    buffer_t y;
    buffer_t z;
} buffer3_t;

/*******************************************************
 * Prototypes
 *******************************************************/

// Initialize circular buffer
void initBuffer(buffer_t *buffer);

// Deallocates buffer memory
void freeCircBuf (buffer_t *buffer);

// Calculate moving average
int32_t getBufferAverage(buffer_t *buffer);

// Reads from buffer rindex
int32_t readBuffer(buffer_t *buffer);

// Writes to buffer windex
void writeBuffer(buffer_t *buffer,int32_t data);

#endif
