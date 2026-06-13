#ifndef ECU_H
#define ECU_H

typedef enum
{
    ECU_INIT,
    ECU_RUNNING,
    ECU_WARNING,
    ECU_FAULT
} ECU_State;

typedef struct
{
    float temperature;
    float voltage;
    float current;

    int error_count;

    ECU_State state;
} ECU;

void ecu_init(ECU *ecu);
void ecu_update(ECU *ecu);

const char* ecu_state_to_string(ECU_State state);

#endif