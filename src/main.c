#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "scheduler.h"
#include "sensor_tasks.h"
#include "data_fusion.h"
#include "config.h"

extern void initializeSensorReceiver();

int main(void) {
    // Initialize the scheduler
    if (initScheduler() != pdPASS) {
        printf("Failed to initialize scheduler\n");
        return -1;
    }

    // Initialize the sensor receiver
    initializeSensorReceiver();

    // Create sensor tasks
    for (int i = 0; i < NUM_SENSORS; i++) {
        xTaskCreate(sensorTask, "SensorTask", configMINIMAL_STACK_SIZE, (void*)(intptr_t)i, tskIDLE_PRIORITY, NULL);
    }

    // Create data fusion task
    xTaskCreate(dataFusionTask, "DataFusionTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // We should never get here
    for (;;);

    return 0;
}