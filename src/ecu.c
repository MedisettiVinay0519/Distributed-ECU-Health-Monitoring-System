#include <stdlib.h>
#include "ecu.h"

void ecu_init(ECU *ecu)
{
    ecu->temperature = 25.0f;
    ecu->voltage = 12.0f;
    ecu->current = 0.0f;
    ecu->error_count = 0;
    ecu->state = ECU_INIT;
}

void ecu_update(ECU *ecu)
{
    float tempNoise;
    float voltageNoise;
    float currentNoise;

    /* Base Sensor Values */

    ecu->temperature =
        25 + (rand() % 95);

    ecu->voltage =
        11.0f +
        (rand() % 20) / 10.0f;

    ecu->current =
        rand() % 20;

    /* Sensor Noise */

    tempNoise =
        (
            (rand() % 1000) / 1000.0f
            - 0.5f
        ) * 10.0f;

    voltageNoise =
        (
            (rand() % 1000) / 1000.0f
            - 0.5f
        ) * 1.0f;

    currentNoise =
        (
            (rand() % 1000) / 1000.0f
            - 0.5f
        ) * 4.0f;

    ecu->temperature += tempNoise;
    ecu->voltage += voltageNoise;
    ecu->current += currentNoise;

    /* Multi-Parameter Health Assessment */

    if(
        ecu->temperature >= 95.0f ||
        ecu->voltage <= 10.5f ||
        ecu->current >= 18.0f
    )
    {
        ecu->state = ECU_FAULT;
    }
    else if(
        ecu->temperature >= 70.0f ||
        ecu->voltage <= 11.2f ||
        ecu->current >= 15.0f
    )
    {
        ecu->state = ECU_WARNING;
    }
    else
    {
        ecu->state = ECU_RUNNING;
    }
}

const char* ecu_state_to_string(ECU_State state)
{
    switch(state)
    {
        case ECU_INIT:
            return "INIT";

        case ECU_RUNNING:
            return "RUNNING";

        case ECU_WARNING:
            return "WARNING";

        case ECU_FAULT:
            return "FAULT";

        default:
            return "UNKNOWN";
    }
}