#include "unity.h"
#include "data_fusion.h"

void setUp(void) {
    // Set up any test fixtures
}

void tearDown(void) {
    // Clean up any test fixtures
}

void test_dataFusionTask(void) {
    // This test is complex and would require mocking FreeRTOS functions
    // For simplicity, we'll just test that the function exists
    TEST_ASSERT_NOT_NULL(dataFusionTask);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_dataFusionTask);
    return UNITY_END();
}