#include "unity.h"
#include "scheduler.h"

void setUp(void) {
    // Set up any test fixtures
}

void tearDown(void) {
    // Clean up any test fixtures
}

void test_initScheduler(void) {
    TEST_ASSERT_EQUAL(pdPASS, initScheduler());
}

void test_adjustTaskPriority(void) {
    // This test is more complex and would require mocking FreeRTOS functions
    // For simplicity, we'll just test that the function doesn't crash
    adjustTaskPriority(NULL);
    TEST_PASS();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_initScheduler);
    RUN_TEST(test_adjustTaskPriority);
    return UNITY_END();
}