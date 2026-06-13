#include "can_encoder.h"

CAN_Frame telemetry_to_can(
    TelemetryData *data
)
{
    CAN_Frame frame;

    frame.id = data->ecu_id;

    frame.dlc = 3;

    frame.data[0] =
        (unsigned char)data->temperature;

    frame.data[1] =
        (unsigned char)data->voltage;

    frame.data[2] =
        (unsigned char)data->current;

    return frame;
}