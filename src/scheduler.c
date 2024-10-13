#include "scheduler.h"
#include "FreeRTOS.h"
#include "task.h"

BaseType_t initScheduler(void) {
    // Initialize any scheduler-specific data structures
    return pdPASS;
}

void adjustTaskPriority(TaskHandle_t task) {
    UBaseType_t currentPriority = uxTaskPriorityGet(task);
    
    // Simple adaptive algorithm: alternate between increasing and decreasing priority
    static BaseType_t increase = pdTRUE;
    
    if (increase) {
        if (currentPriority < configMAX_PRIORITIES - 1) {
            vTaskPrioritySet(task, currentPriority + 1);
        }
    } else {
        if (currentPriority > tskIDLE_PRIORITY) {
            vTaskPrioritySet(task, currentPriority - 1);
        }
    }
    
    increase = !increase;
}

UBaseType_t getTaskPriority(TaskHandle_t task) {
    return uxTaskPriorityGet(task);
}