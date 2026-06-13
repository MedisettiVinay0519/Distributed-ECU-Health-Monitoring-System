#ifndef CAN_ENCODER_H
#define CAN_ENCODER_H

#include "telemetry.h"
#include "can.h"

CAN_Frame telemetry_to_can(
    TelemetryData *data
);

#endif