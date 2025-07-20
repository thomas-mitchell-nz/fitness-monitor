/**********************************************************
 *
 * buffer.c
 *
 * Circular buffer functionality
 *
 * Authors: T.J. Mitchell and S.G. Jackson
 * Date modified: 31/03/2022
 * Provenance: 'circBufT.c' module by P.J. Bones on 8 Mar 2017
 *
 **********************************************************/

#include "buffer.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************
 * Initialize Buffer function, allocate data location for array
 *******************************************************************/

void initBuffer (buffer_t *buffer)
{
    buffer->size = 20; /////
    buffer->windex = 0;
    buffer->rindex = 0;
    buffer->data = (int32_t *) calloc(buffer->size, sizeof(int32_t));
}

/*******************************************************************
 * Read the current step for buffers
 *******************************************************************/
int32_t readBuffer (buffer_t *buffer)
{
    int32_t elem = buffer->data[buffer->rindex];
    buffer->rindex++;

     if (buffer->rindex >= buffer->size) {
         buffer->rindex = 0;
     }

     return elem;
}

/*******************************************************************
 * Write to buffer windex
 *******************************************************************/
void writeBuffer (buffer_t *buffer, int32_t elem)
{
    buffer->data[buffer->windex] = elem;
    buffer->windex++;

    if (buffer->windex >= buffer->size) {
        buffer->windex = 0;
    }
}

/*******************************************************************
 * Calculate moving average
 *******************************************************************/
int32_t getBufferAverage (buffer_t *buffer)
{
    int32_t sum = 0;
    int32_t average;
    int32_t elem;
    int32_t i;

    for (i = 0; i <= buffer->size; i++) {
        //int32_t value = readBuffer(buffer);
        elem = buffer->data[i];
        sum += elem;
    }

    average = (2 * sum + buffer->size) / 2 / buffer->size;
    return average;
}

/*******************************************************************
 * Deallocate buffer memory
 *******************************************************************/
void freeCircBuf (buffer_t *buffer)
{
    buffer->windex = 0;
    buffer->rindex = 0;
    buffer->size = 0;
    free (buffer->data);
    buffer->data = NULL;
}


