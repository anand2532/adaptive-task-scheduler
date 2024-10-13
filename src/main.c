#include <stdio.h>
#include <pthread.h>
#include "FreeRTOS.h"
#include "task.h"
#include "scheduler.h"
#include "sensor_tasks.h"
#include "data_fusion.h"
#include "config.h"

void startReceiverTask(void *pvParameters) {
    printf("Starting sensor receiver initialization\n");
    initializeSensorReceiver();
    printf("Sensor receiver initialization completed\n");
    vTaskDelete(NULL);
}

int main(void) {
    // Initialize the scheduler
    if (initScheduler() != pdPASS) {
        printf("Failed to initialize scheduler\n");
        return -1;
    }

    // Create sensor queues
    createSensorQueues();

    // Create sensor tasks
    for (int i = 0; i < NUM_SENSORS; i++) {
        xTaskCreate(sensorTask, "SensorTask", configMINIMAL_STACK_SIZE * 2, (void*)(intptr_t)i, tskIDLE_PRIORITY + 1, NULL);
        printf("Created task for Sensor %d\n", i + 1);
    }

    // Create data fusion task with higher priority
    xTaskCreate(dataFusionTask, "DataFusionTask", configMINIMAL_STACK_SIZE * 2, NULL, tskIDLE_PRIORITY + 2, NULL);
    printf("Created Data Fusion task\n");

    // Create a task to initialize the sensor receiver
    xTaskCreate(startReceiverTask, "ReceiverInitTask", configMINIMAL_STACK_SIZE * 2, NULL, tskIDLE_PRIORITY + 3, NULL);
    printf("Created Receiver Init task\n");

    printf("Starting FreeRTOS scheduler\n");
    // Start the scheduler
    vTaskStartScheduler();

    // We should never get here
    printf("Scheduler has stopped unexpectedly\n");
    for (;;);

    return 0;
}