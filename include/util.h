#include <stdio.h>
#include <FreeRTOS.h>
#include <semphr.h>

/*!
 * \brief Increase the counter value and print a message with the thread name and previous counter value.
 * \note The counter update is protected by the given semaphore, but the print is not. While \ref printf is atomic,
 * calling this from different threads may still print out of order.
 *
 * \param name name to use for printing
 * \param counter pointer to the counter to read and update
 * \param semaphore semaphore used to protect counter access
 * \param counter_out out param for the read counter value
 *
 * \return 0 if the semaphore could not be acquired, otherwise printf return value
 */
int counter_update_print(char* name, int* counter, SemaphoreHandle_t semaphore, int* counter_out);