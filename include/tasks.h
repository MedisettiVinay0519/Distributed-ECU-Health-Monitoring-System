#ifndef TASKS_H
#define TASKS_H

#include "ecu.h"
#include "telemetry.h"

TelemetryData engine_task(ECU *engine);

TelemetryData battery_task(ECU *battery);

TelemetryData brake_task(ECU *brake);

#endif