#include <stdio.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>

bool thread_update_print(int* counter, SemaphoreHandle_t semaphore) {
    int cval;
    bool gotsema = (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE);
    if (gotsema) {
        *counter += *counter + 1;
        cval = *counter;
        xSemaphoreGive(semaphore);

        printf("hello world from % 6s! Count % d\n", "thread", cval);
    }
    return gotsema;
}

bool main_update_print(int* counter, SemaphoreHandle_t semaphore) {
    int cval;
    bool gotsema = (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE);
    if (gotsema) {
        cval = (*counter)++;
        xSemaphoreGive(semaphore);

        printf("hello world from % 6s! Count % d\n", "main", cval);
    }
    return gotsema;
}