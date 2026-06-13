#include "can.h"

static CAN_Frame canQueue[CAN_QUEUE_SIZE];

static int front = 0;
static int rear = 0;
static int count = 0;

void can_init(void)
{
    front = 0;
    rear = 0;
    count = 0;
}

void can_send(CAN_Frame *frame)
{
    if(count >= CAN_QUEUE_SIZE)
    {
        return;
    }

    canQueue[rear] = *frame;

    rear =
        (rear + 1)
        % CAN_QUEUE_SIZE;

    count++;
}

int can_receive(CAN_Frame *frame)
{
    if(count == 0)
    {
        return 0;
    }

    *frame = canQueue[front];

    front =
        (front + 1)
        % CAN_QUEUE_SIZE;

    count--;

    return 1;
}