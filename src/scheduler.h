#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "FreeRTOS.h"
#include "task.h"

// Initialize the scheduler
BaseType_t initScheduler(void);

// Adjust task priority based on execution pattern
void adjustTaskPriority(TaskHandle_t task);

// Get the current priority of a task
UBaseType_t getTaskPriority(TaskHandle_t task);

#endif // SCHEDULER_H