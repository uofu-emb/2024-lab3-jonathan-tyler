#include <stdio.h>
#include <FreeRTOS.h>
#include <semphr.h>

bool thread_update_print(int* counter, SemaphoreHandle_t semaphore);
bool main_update_print(int* counter, SemaphoreHandle_t semaphore);