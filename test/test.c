#include <stdio.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>

#include <stdint.h>
#include <unity.h>
#include "unity_config.h"

#include "util.h"

#define TEST_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define TEST_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define TEST_RUNNER_PRIORITY      ( tskIDLE_PRIORITY + 2UL )
#define TEST_RUNNER_STACK_SIZE configMINIMAL_STACK_SIZE

void setUp(void) {}

void tearDown(void) {}

void test_variable_assignment()
{
    int x = 1;
    TEST_ASSERT_TRUE_MESSAGE(x == 1,"Variable assignment failed.");
}

void test_multiplication(void)
{
    int x = 30;
    int y = 6;
    int z = x / y;
    TEST_ASSERT_TRUE_MESSAGE(z == 5, "Multiplication of two integers returned incorrect value.");
}

void runner_thread (__unused void *args)
{
    for (;;) {
        printf("Starting test run.\n");
        UNITY_BEGIN();
        RUN_TEST(test_variable_assignment);
        RUN_TEST(test_multiplication);
        UNITY_END();
        sleep_ms(5000);
    }
}

int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);
    printf("Launching runner\n");
    xTaskCreate(runner_thread, "TestRunner",
                TEST_RUNNER_STACK_SIZE, NULL, TEST_RUNNER_PRIORITY, NULL);
    vTaskStartScheduler();
    return 0;
}
