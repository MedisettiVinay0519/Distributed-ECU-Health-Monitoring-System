#include <stdio.h>
#include "logger_task.h"

void logger_task(TelemetryData *data)
{
    printf(
        "\n[LOGGER TASK]\n"
        "ECU ID: %d\n"
        "Temperature: %.1f\n"
        "Voltage: %.1f\n"
        "Current: %.1f\n",
        data->ecu_id,
        data->temperature,
        data->voltage,
        data->current
    );
}