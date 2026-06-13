#ifndef TELEMETRY_H
#define TELEMETRY_H

typedef struct
{
    int ecu_id;

    float temperature;
    float voltage;
    float current;

} TelemetryData;

#endif