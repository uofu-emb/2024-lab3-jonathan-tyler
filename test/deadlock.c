#include "deadlock.h"

//creating deadlock

void task1(void *args) {
    //we are casting a pointer to struct and we using args to refrence a struct
    struct semaphores *sems = (struct semaphores *) args;
    //we call the semaA to call a semaphore
    xSemaphoreTake(sems->semaA, portMAX_DELAY);
    vTaskDelay(1000);
    //we are taki
    xSemaphoreTake(sems->semaB, portMAX_DELAY);
    while (1);
}

void task2(void *args) {
    struct semaphores *sems = (struct semaphores *) args;
    xSemaphoreTake(sems->semaB, portMAX_DELAY);
    vTaskDelay(1000);
    xSemaphoreTake(sems->semaA, portMAX_DELAY);
    //make sures it does not drop off the stack.
    while (1);
}
