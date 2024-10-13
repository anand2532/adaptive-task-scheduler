#include "data_fusion.h"
#include "sensor_tasks.h"
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define FUSION_INTERVAL_MS 2000  // Fuse data every 2 seconds

void dataFusionTask(void *pvParameters) {
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(FUSION_INTERVAL_MS);

    printf("Data Fusion Task started\n");

    // Initialize the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    while (1) {
        // Wait for the next cycle.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        printf("Data Fusion Task woke up\n");

        float fusedData = 0;
        int updatedSensors = 0;

        // Collect and fuse data from all sensors
        for (int i = 0; i < NUM_SENSORS; i++) {
            float sensorData = getLatestSensorData(i);
            if (sensorData != 0.0f) {
                fusedData += sensorData;
                updatedSensors++;
                printf("Using data from Sensor %d: %.2f\n", i, sensorData);
            } else {
                printf("Data from Sensor %d is not available\n", i);
            }
        }

        // Calculate average if we have data from at least one sensor
        if (updatedSensors > 0) {
            fusedData /= updatedSensors;
            printf("Fused data: %.2f (from %d sensors)\n", fusedData, updatedSensors);
        } else {
            printf("No sensor data available for fusion\n");
        }
    }
}