#include "unity.h"
#include "scheduler.h"
#include "FreeRTOS.h"
#include "task.h"

void test_initScheduler(void) {
    TEST_ASSERT_EQUAL(pdPASS, initScheduler());
}

void test_adjustTaskPriority(void) {
    TaskHandle_t testTask;
    xTaskCreate(NULL, "TestTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &testTask);
    
    UBaseType_t originalPriority = uxTaskPriorityGet(testTask);
    adjustTaskPriority(testTask);
    UBaseType_t newPriority = uxTaskPriorityGet(testTask);
    
    TEST_ASSERT_NOT_EQUAL(originalPriority, newPriority);
    
    vTaskDelete(testTask);
}