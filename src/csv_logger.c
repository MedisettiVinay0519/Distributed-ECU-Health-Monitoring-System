#include <stdio.h>

#include "csv_logger.h"

#define CSV_FILE "ecu_log.csv"

void csv_logger_init(void)
{
    FILE *fp =
        fopen(
            CSV_FILE,
            "w"
        );

    if(fp == NULL)
    {
        return;
    }

    fprintf(
        fp,
        "ECU_ID,Temperature,Voltage,Current,State\n"
    );

    fclose(fp);
}

void csv_logger_write(
    TelemetryData *data,
    const char *state
)
{
    FILE *fp =
        fopen(
            CSV_FILE,
            "a"
        );

    if(fp == NULL)
    {
        return;
    }

    fprintf(
        fp,
        "%d,%.1f,%.1f,%.1f,%s\n",
        data->ecu_id,
        data->temperature,
        data->voltage,
        data->current,
        state
    );

    fclose(fp);
}