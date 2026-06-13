#include "tasks.h"
#include "telemetry.h"

TelemetryData brake_task(ECU *brake)
{
    TelemetryData data;

    ecu_update(brake);

    data.ecu_id = 3;

    data.temperature = brake->temperature;
    data.voltage = brake->voltage;
    data.current = brake->current;

    return data;
}