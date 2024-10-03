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

SemaphoreHandle_t semaphore;
int counter;

void setUp(void)
{
    semaphore = xSemaphoreCreateCounting(1, 1);
    counter = 0;
}

void tearDown(void)
{
    vSemaphoreDelete(semaphore);
}

void test_unavailable(void)
{
    int counter_out = 2;
    xSemaphoreTake(semaphore, portMAX_DELAY);
    for (int i = 0; i < 32; i++) {
        int result = counter_update_print("", &counter, semaphore, NULL);
        TEST_ASSERT_EQUAL(counter, 0);
        TEST_ASSERT_EQUAL(result, 0);
        result = counter_update_print("", &counter, semaphore, &counter_out);
        TEST_ASSERT_EQUAL(counter, 0);
        TEST_ASSERT_EQUAL(result, 0);
        TEST_ASSERT_EQUAL(counter_out, 2);
    }
    xSemaphoreGive(semaphore);
}

void test_counter_update(void)
{
    int counter_out = 2;
    for (int i = 0; i < 32; i++) {
        int result = counter_update_print("", &counter, semaphore, NULL);
        TEST_ASSERT_EQUAL(counter, 2*i+1);
        TEST_ASSERT_GREATER_THAN(result, 0);
        result = counter_update_print("", &counter, semaphore, &counter_out);
        TEST_ASSERT_EQUAL(counter, 2*i+2);
        TEST_ASSERT_GREATER_THAN(result, 0);
        TEST_ASSERT_EQUAL(counter_out, 2*i+1);
    }
}

void runner_thread (__unused void *args)
{
    for (;;) {
        printf("Starting test run.\n");
        UNITY_BEGIN();
        RUN_TEST(test_unavailable);
        RUN_TEST(test_counter_update);
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
