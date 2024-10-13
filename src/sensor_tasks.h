#ifndef SENSOR_TASKS_H
#define SENSOR_TASKS_H

#include "FreeRTOS.h"
#include "task.h"

// Sensor task function
void sensorTask(void *pvParameters);

// Get the queue handle for a specific sensor
QueueHandle_t getSensorQueue(int sensorId);

#endif // SENSOR_TASKS_H