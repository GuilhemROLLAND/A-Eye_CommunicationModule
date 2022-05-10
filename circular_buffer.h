#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef _CIRCULARBUFFER_H
#define _CIRCULARBUFFER_H

    // Opaque circular buffer structure
    typedef struct circular_buf_t
    {
        char *buffer;
        int head;
        int tail;
        int max; // of the buffer
        bool full;
    } circular_buf_t;

    // Handle type, the way users interact with the API
    typedef circular_buf_t *cbuf_handle_t;

    /// Pass in a storage buffer and size
    /// Returns a circular buffer handle
    cbuf_handle_t circular_buf_init(char *buffer, int size);

    /// Free a circular buffer structure.
    /// Does not free data buffer; owner is responsible for that
    void circular_buf_free(cbuf_handle_t me);

    /// Reset the circular buffer to empty, head == tail
    void circular_buf_reset(cbuf_handle_t me);

    /// Put version 1 continues to add data if the buffer is full
    /// Old data is overwritten
    void circular_buf_put(cbuf_handle_t me, char *data);

    /// Retrieve a value from the buffer
    /// Returns 0 on success, -1 if the buffer is empty
    int circular_buf_get(cbuf_handle_t me, char *data);

    /// Returns true if the buffer is empty
    bool circular_buf_empty(cbuf_handle_t me);

    /// Returns true if the buffer is full
    bool circular_buf_full(cbuf_handle_t me);

    /// Returns the maximum capacity of the buffer
    int circular_buf_capacity(cbuf_handle_t me);

    /// Returns the current number of elements in the buffer
    int circular_buf_size(cbuf_handle_t me);

#endif