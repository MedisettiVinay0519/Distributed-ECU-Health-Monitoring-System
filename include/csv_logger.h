#ifndef CSV_LOGGER_H
#define CSV_LOGGER_H

#include "telemetry.h"

void csv_logger_init(void);

void csv_logger_write(
    TelemetryData *data,
    const char *state
);

#endif