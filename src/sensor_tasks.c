#include "sensor_tasks.h"
#include "scheduler.h"
#include "config.h"

static QueueHandle_t sensorQueues[NUM_SENSORS];

void sensorTask(void *pvParameters) {
    int sensorId = (int)pvParameters;
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(SENSOR_PERIOD_MS);

    // Create queue for this sensor
    sensorQueues[sensorId] = xQueueCreate(10, sizeof(float));

    xLastWakeTime = xTaskGetTickCount();
    for (;;) {
        float sensorData = (float)rand() / RAND_MAX; // Simulate sensor reading

        // Send data to queue
        xQueueSend(sensorQueues[sensorId], &sensorData, 0);

        // Adjust task priority
        adjustTaskPriority(NULL);

        // Wait for the next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

QueueHandle_t getSensorQueue(int sensorId) {
    if (sensorId >= 0 && sensorId < NUM_SENSORS) {
        return sensorQueues[sensorId];
    }
    return NULL;
}