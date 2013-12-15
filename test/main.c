#include <stdio.h>

#include "osal_free/osal.h"


static osal_thread_T Thread1;
static osal_thread_T Thread2;



OSAL_THREADFUNC_TYPE Thread1Func(OSAL_THREADFUNC_ARG_TYPE dataP)
{
    while (!osal_program_interrupted)
    {
        printf("%lu - Thread1: running...\n", osal_getUsecTime());
        osal_usleep(1000000);
    }
    printf("Thread1: exiting...\n");
    return NULL;
}



OSAL_THREADFUNC_TYPE Thread2Func(OSAL_THREADFUNC_ARG_TYPE dataP)
{
    while (!osal_program_interrupted)
    {
        printf("%lu - Thread2: running...\n", osal_getUsecTime());
        osal_sleepTimerMsec(1000);
    }
    printf("Thread2: exiting...\n");
    return NULL;
}



int main(int argc, char **argv)
{
    osal_heapInit();
    osal_init();

    printf("Main: starting...\n");

    if (osal_threadInit(&Thread1, "Thread1", Thread1Func, NULL, OSAL_THREAD_PRIORITY_NORMAL, 512) != RMX_SUCCESS)
    {
        printf("Main: Thread1 init FAIL.\n");
    }
    if (osal_threadInit(&Thread2, "Thread2", Thread2Func, NULL, OSAL_THREAD_PRIORITY_NORMAL, 512) != RMX_SUCCESS)
    {
        printf("Main: Thread2 init FAIL.\n");
    }
    
    osal_start();
    while (!osal_program_interrupted) // check the signal flag for clean shutdown
    {
        // OS dependent whether one arrives here or not...
        osal_sleepTimerMsec(1000);
        printf("%lu - Main: looping...\n", osal_getUsecTime());
    }

    printf("Main: exiting...\n");
    osal_exit();
    return 0;
}
