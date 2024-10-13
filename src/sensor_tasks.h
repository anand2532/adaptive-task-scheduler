#ifndef SENSOR_TASKS_H
#define SENSOR_TASKS_H

#include "FreeRTOS.h"
#include "queue.h"

void sensorTask(void *pvParameters);
QueueHandle_t getSensorQueue(int sensorId);
float getLatestSensorData(int sensorId);
void createSensorQueues();
void initializeSensorReceiver();

#endif // SENSOR_TASKS_H