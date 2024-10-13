#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_initScheduler(void);
void test_adjustTaskPriority(void);
void test_dataFusion(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_initScheduler);
    RUN_TEST(test_adjustTaskPriority);
    RUN_TEST(test_dataFusion);
    return UNITY_END();
}