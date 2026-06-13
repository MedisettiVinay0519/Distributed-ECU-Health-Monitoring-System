#include "tasks.h"
#include "telemetry.h"

TelemetryData engine_task(ECU *engine)
{
    TelemetryData data;

    ecu_update(engine);

    data.ecu_id = 1;
    data.temperature = engine->temperature;
    data.voltage = engine->voltage;
    data.current = engine->current;

    return data;
}