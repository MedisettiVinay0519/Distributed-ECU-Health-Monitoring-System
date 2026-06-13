#include "telemetry_queue.h"

void queue_init(TelemetryQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

int queue_is_empty(
    const TelemetryQueue *q
)
{
    return (q->count == 0);
}

int queue_is_full(
    const TelemetryQueue *q
)
{
    return (q->count == QUEUE_SIZE);
}

int queue_size(
    const TelemetryQueue *q
)
{
    return q->count;
}

int queue_enqueue(
    TelemetryQueue *q,
    TelemetryData data
)
{
    if(queue_is_full(q))
    {
        return 0;
    }

    q->data[q->rear] = data;

    q->rear =
        (q->rear + 1) % QUEUE_SIZE;

    q->count++;

    return 1;
}

int queue_dequeue(
    TelemetryQueue *q,
    TelemetryData *data
)
{
    if(queue_is_empty(q))
    {
        return 0;
    }

    *data = q->data[q->front];

    q->front =
        (q->front + 1) % QUEUE_SIZE;

    q->count--;

    return 1;
}