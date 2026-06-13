#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#define MAX_LOGS 10
#define MAX_MSG_LEN 100

typedef struct
{
    char logs[MAX_LOGS][MAX_MSG_LEN];

    int head;
    int count;

} RingBuffer;

void rb_init(RingBuffer *rb);

void rb_add(RingBuffer *rb, const char *msg);

void rb_print(const RingBuffer *rb);

#endif