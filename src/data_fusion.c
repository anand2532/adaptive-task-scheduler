#include "data_fusion.h"
#include "sensor_tasks.h"
#include "config.h"
#include <stdio.h>

void dataFusionTask(void *pvParameters) {
    float sensorData[NUM_SENSORS];
    float fusedData;

    for (;;) {
        // Collect data from all sensors
        for (int i = 0; i < NUM_SENSORS; i++) {
            xQueueReceive(getSensorQueue(i), &sensorData[i], portMAX_DELAY);
        }

        // Simple fusion algorithm (average)
        fusedData = 0;
        for (int i = 0; i < NUM_SENSORS; i++) {
            fusedData += sensorData[i];
        }
        fusedData /= NUM_SENSORS;

        // Print fused data (in a real application, you might send this to another task or external system)
        printf("Fused data: %f\n", fusedData);

        // Small delay to prevent flooding the console
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}