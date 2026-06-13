#ifndef PREDICTIVE_DIAGNOSTICS_H
#define PREDICTIVE_DIAGNOSTICS_H

#define HISTORY_SIZE 5

typedef struct
{
    float history[HISTORY_SIZE];

    int index;
    int count;

} PredictiveMonitor;

void predictive_init(
    PredictiveMonitor *monitor
);

void predictive_add_sample(
    PredictiveMonitor *monitor,
    float temperature
);

float predictive_average(
    PredictiveMonitor *monitor
);

int predictive_warning(
    PredictiveMonitor *monitor
);

#endif