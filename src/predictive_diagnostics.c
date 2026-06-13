#include "predictive_diagnostics.h"

void predictive_init(
    PredictiveMonitor *monitor
)
{
    int i;

    for(i = 0; i < HISTORY_SIZE; i++)
    {
        monitor->history[i] = 0.0f;
    }

    monitor->index = 0;
    monitor->count = 0;
}

void predictive_add_sample(
    PredictiveMonitor *monitor,
    float temperature
)
{
    monitor->history[
        monitor->index
    ] = temperature;

    monitor->index =
        (monitor->index + 1)
        % HISTORY_SIZE;

    if(monitor->count < HISTORY_SIZE)
    {
        monitor->count++;
    }
}

float predictive_average(
    PredictiveMonitor *monitor
)
{
    float sum = 0.0f;

    int i;

    if(monitor->count == 0)
    {
        return 0.0f;
    }

    for(i = 0; i < monitor->count; i++)
    {
        sum += monitor->history[i];
    }

    return
        sum /
        monitor->count;
}

int predictive_warning(
    PredictiveMonitor *monitor
)
{
    float average =
        predictive_average(
            monitor
        );

    if(
        monitor->count == HISTORY_SIZE &&
        average >= 70.0f
    )
    {
        return 1;
    }

    return 0;
}