
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "csv_logger.h"
#include "ecu.h"
#include "logger.h"
#include "ring_buffer.h"
#include "predictive_diagnostics.h"
#include "tasks.h"
#include "telemetry.h"
#include "logger_task.h"
#include "telemetry_queue.h"

#include "can.h"
#include "can_encoder.h"

int main()
{
    srand(time(NULL));

    ECU engine;
    ECU battery;
    ECU brake;

    RingBuffer eventBuffer;
    TelemetryQueue telemetryQueue;

    rb_init(&eventBuffer);
    queue_init(&telemetryQueue);

    /* CAN Initialization */
    can_init();
    csv_logger_init();
    ecu_init(&engine);
    ecu_init(&battery);
    ecu_init(&brake);
    PredictiveMonitor engineMonitor;
    PredictiveMonitor batteryMonitor;
    PredictiveMonitor brakeMonitor;

    predictive_init(&engineMonitor);
    predictive_init(&batteryMonitor);
    predictive_init(&brakeMonitor);

    while(1)
    {
        /* ECU Tasks */

        TelemetryData engineData =
            engine_task(&engine);

        TelemetryData batteryData =
            battery_task(&battery);

        TelemetryData brakeData =
    brake_task(&brake);

/* Predictive Diagnostics Data Collection */

predictive_add_sample(
    &engineMonitor,
    engine.temperature
);

predictive_add_sample(
    &batteryMonitor,
    battery.temperature
);

predictive_add_sample(
    &brakeMonitor,
    brake.temperature
);

/* CSV Logging */

csv_logger_write(
    &engineData,
    ecu_state_to_string(
        engine.state
    )
);

csv_logger_write(
    &batteryData,
    ecu_state_to_string(
        battery.state
    )
);

csv_logger_write(
    &brakeData,
    ecu_state_to_string(
        brake.state
    )
);

        CAN_Frame engineFrame =
            telemetry_to_can(&engineData);

        CAN_Frame batteryFrame =
            telemetry_to_can(&batteryData);

        CAN_Frame brakeFrame =
            telemetry_to_can(&brakeData);

        /* CAN Transmission */

        can_send(&engineFrame);
        can_send(&batteryFrame);
        can_send(&brakeFrame);

        /* Producer -> Queue */

        queue_enqueue(
            &telemetryQueue,
            engineData
        );

        queue_enqueue(
            &telemetryQueue,
            batteryData
        );

        queue_enqueue(
            &telemetryQueue,
            brakeData
        );

        /* Consumer -> Logger Task */

        TelemetryData receivedData;

        while(
            queue_dequeue(
                &telemetryQueue,
                &receivedData
            )
        )
        {
            logger_task(&receivedData);
        }

        printf("\n=================================\n");

        printf("Engine ECU\n");
        printf("Temp: %.1f\n", engine.temperature);
        printf("Voltage: %.1f\n", engine.voltage);
        printf("Current: %.1f\n", engine.current);
        printf("State: %s\n\n",
               ecu_state_to_string(engine.state));

        printf("Battery ECU\n");
        printf("Temp: %.1f\n", battery.temperature);
        printf("Voltage: %.1f\n", battery.voltage);
        printf("Current: %.1f\n", battery.current);
        printf("State: %s\n\n",
               ecu_state_to_string(battery.state));

        printf("Brake ECU\n");
        printf("Temp: %.1f\n", brake.temperature);
        printf("Voltage: %.1f\n", brake.voltage);
        printf("Current: %.1f\n", brake.current);
        printf("State: %s\n",
               ecu_state_to_string(brake.state));

        /* Predictive Diagnostics */

if(
    predictive_warning(
        &engineMonitor
    )
)
{
    printf(
        "\n[PREDICTIVE ALERT] "
        "Engine temperature trend rising\n"
    );
}

if(
    predictive_warning(
        &batteryMonitor
    )
)
{
    printf(
        "\n[PREDICTIVE ALERT] "
        "Battery temperature trend rising\n"
    );
}

if(
    predictive_warning(
        &brakeMonitor
    )
)
{
    printf(
        "\n[PREDICTIVE ALERT] "
        "Brake temperature trend rising\n"
    );
}

        /* Engine Diagnostics */

        if(engine.state == ECU_WARNING)
        {
            log_warning("Engine Temperature High");

            rb_add(
                &eventBuffer,
                "[WARNING] Engine Temperature High"
            );
        }
        else if(engine.state == ECU_FAULT)
        {
            log_fault("Engine Overheated");

            rb_add(
                &eventBuffer,
                "[FAULT] Engine Overheated"
            );
        }

        /* Battery Diagnostics */

        if(battery.state == ECU_WARNING)
        {
            log_warning("Battery Temperature High");

            rb_add(
                &eventBuffer,
                "[WARNING] Battery Temperature High"
            );
        }
        else if(battery.state == ECU_FAULT)
        {
            log_fault("Battery Overheated");

            rb_add(
                &eventBuffer,
                "[FAULT] Battery Overheated"
            );
        }

        /* Brake Diagnostics */

        if(brake.state == ECU_WARNING)
        {
            log_warning("Brake Temperature High");

            rb_add(
                &eventBuffer,
                "[WARNING] Brake Temperature High"
            );
        }
        else if(brake.state == ECU_FAULT)
        {
            log_fault("Brake Overheated");

            rb_add(
                &eventBuffer,
                "[FAULT] Brake Overheated"
            );
        }

        /* CAN Reception */

        CAN_Frame rxFrame;

        printf("\n----- CAN BUS TRAFFIC -----\n");

        while(
            can_receive(
                &rxFrame
            )
        )
        {
            printf(
                "CAN ID: 0x%X\n",
                rxFrame.id
            );

            printf(
                "Temp: %d\n",
                rxFrame.data[0]
            );

            printf(
                "Voltage: %d\n",
                rxFrame.data[1]
            );

            printf(
                "Current: %d\n\n",
                rxFrame.data[2]
            );
        }

        rb_print(&eventBuffer);

        Sleep(1000);
    }

    return 0;
}
