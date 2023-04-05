//
// Created by bruno on 18/03/23.
//

#ifndef HAL_RING_BUFFER_H
#define HAL_RING_BUFFER_H

#include "hal_defs.h"

typedef struct{
    uint8_t *buffer;
    int head;
    int tail;
    size_t count;
    size_t size;
}RingBuffer;

void ring_buffer_initialize(RingBuffer *rbuf, int size, uint8_t *buffer);
bool ring_buffer_push(RingBuffer *rbuf, uint8_t data);
bool ring_buffer_pull(RingBuffer *rbuf, uint8_t *data);
bool ring_buffer_get_last(RingBuffer *rbuf, uint8_t *data);
size_t ring_buffer_count(RingBuffer *rbuf);

#endif //HAL_RING_BUFFER_H
