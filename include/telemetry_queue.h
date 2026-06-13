#ifndef TELEMETRY_QUEUE_H
#define TELEMETRY_QUEUE_H

#include "telemetry.h"

#define QUEUE_SIZE 20

typedef struct
{
    TelemetryData data[QUEUE_SIZE];

    int front;
    int rear;
    int count;

} TelemetryQueue;

/* Initialize Queue */
void queue_init(TelemetryQueue *q);

/* Add element to queue */
int queue_enqueue(
    TelemetryQueue *q,
    TelemetryData data
);

/* Remove element from queue */
int queue_dequeue(
    TelemetryQueue *q,
    TelemetryData *data
);

/* Utility Functions */
int queue_is_empty(
    const TelemetryQueue *q
);

int queue_is_full(
    const TelemetryQueue *q
);

int queue_size(
    const TelemetryQueue *q
);

#endif