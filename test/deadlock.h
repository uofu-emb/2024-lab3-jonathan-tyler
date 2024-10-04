#include <stdio.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

struct semaphores {
    SemaphoreHandle_t semaA;
    SemaphoreHandle_t semaB;
};

void task1(void* args);
void task2(void* args);
void orphaned_lock(void *args);
void count_evens(void *args);
