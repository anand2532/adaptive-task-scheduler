#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "scheduler.h"
#include "sensor_tasks.h"
#include "data_fusion.h"
#include "config.h"

int main(void) {
    // Initialize the scheduler
    if (initScheduler() != pdPASS) {
        printf("Failed to initialize scheduler\n");
        return -1;
    }

    // Create sensor tasks
    for (int i = 0; i < NUM_SENSORS; i++) {
        xTaskCreate(sensorTask, "SensorTask", configMINIMAL_STACK_SIZE, (void*)i, tskIDLE_PRIORITY, NULL);
    }

    // Create data fusion task
    xTaskCreate(dataFusionTask, "DataFusionTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // We should never get here
    for (;;);

    return 0;
}