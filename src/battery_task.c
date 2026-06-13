#include "tasks.h"
#include "telemetry.h"

TelemetryData battery_task(ECU *battery)
{
    TelemetryData data;

    ecu_update(battery);

    data.ecu_id = 2;

    data.temperature = battery->temperature;
    data.voltage = battery->voltage;
    data.current = battery->current;

    return data;
}