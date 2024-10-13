#include "scheduler.h"
#include "config.h"

static TaskStatus_t taskStatus[NUM_SENSORS];

BaseType_t initScheduler(void) {
    // Initialize any scheduler-specific data structures
    return pdPASS;
}

void adjustTaskPriority(TaskHandle_t task) {
    UBaseType_t currentPriority = uxTaskPriorityGet(task);
    TickType_t runtime;
    
    vTaskGetInfo(task, &taskStatus[0], pdTRUE, eInvalid);
    runtime = taskStatus[0].ulRunTimeCounter;

    // Simple adaptive algorithm: increase priority if task is running for too long
    if (runtime > RUNTIME_THRESHOLD) {
        vTaskPrioritySet(task, currentPriority + 1);
    } else if (currentPriority > tskIDLE_PRIORITY && runtime < RUNTIME_THRESHOLD / 2) {
        vTaskPrioritySet(task, currentPriority - 1);
    }
}

UBaseType_t getTaskPriority(TaskHandle_t task) {
    return uxTaskPriorityGet(task);
}