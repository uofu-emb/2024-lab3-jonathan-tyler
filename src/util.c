#include <stdio.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>

int counter_update_print(char* name, int* counter, SemaphoreHandle_t semaphore, int* counter_out) {
    int cval;
    if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE) {
        cval = (*counter)++;
        xSemaphoreGive(semaphore);

        if (counter_out) *counter_out = cval;
        return printf("hello world from % 6s! Count % d\n", name, cval);
    }
    return 0;
}