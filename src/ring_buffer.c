#include <stdio.h>
#include <string.h>

#include "ring_buffer.h"

void rb_init(RingBuffer *rb)
{
    rb->head = 0;
    rb->count = 0;
}

void rb_add(RingBuffer *rb, const char *msg)
{
    strncpy(
        rb->logs[rb->head],
        msg,
        MAX_MSG_LEN - 1
    );

    rb->logs[rb->head][MAX_MSG_LEN - 1] = '\0';

    rb->head = (rb->head + 1) % MAX_LOGS;

    if(rb->count < MAX_LOGS)
    {
        rb->count++;
    }
}

void rb_print(const RingBuffer *rb)
{
    printf("\n===== EVENT LOG =====\n");

    int start;

    if(rb->count < MAX_LOGS)
    {
        start = 0;
    }
    else
    {
        start = rb->head;
    }

    for(int i = 0; i < rb->count; i++)
    {
        int index = (start + i) % MAX_LOGS;

        printf("%s\n", rb->logs[index]);
    }

    printf("=====================\n");
}