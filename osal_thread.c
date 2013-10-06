/**
 * \file
 * <!--
 * This file is part of osal - OS abstraction layer.
 *
 * Copyright 2009-2013 Phillip Yeager
 *
 * \brief Thread interface
 *
 * This module provides thread functionality for osal
 *
 * \author Phillip Yeager <monstermoto@yahoo.com>
 */


#include "osal_free/osal.h"
#include "osal_free/osal_thread.h"
#include "osal_free/osal_memory.h"



#if defined(RMX_OSAL_PTHREAD)

#include <pthread.h>
#include <assert.h>

#define OSAL_PTHREAD_MIN_STACK	(1024*1024)

int osal_threadInit(osal_thread_T* threadP,
                    const char* nameP,
                    OSAL_THREADFUNC_TYPE (*funcP) (OSAL_THREADFUNC_ARG_TYPE),
                    void* dataP,
                    osal_thread_priority_T priority,
                    size_t stackSize)
{
    int ret = 0;

    assert (threadP != NULL);
    assert (funcP != NULL);

    if ( threadP != NULL )
    {
        threadP->nameP = (char*)nameP;

        pthread_attr_init(&threadP->mAttr);
        if (stackSize < OSAL_PTHREAD_MIN_STACK) stackSize = OSAL_PTHREAD_MIN_STACK;
        pthread_attr_setstacksize(&threadP->mAttr, stackSize);
        ret = pthread_create(&threadP->mThreadID, &threadP->mAttr, funcP, dataP);
        if (ret == 0)
        {
            osal_threadSetPriority(threadP, priority );
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}


/* Note: this won't take without root priviledges */
int osal_threadSetPriority(osal_thread_T* threadP, osal_thread_priority_T priority )
{
    (void)priority; // remove unused parameter warning

    //int ret = 0;

    //struct sched_param param;
    //param.sched_priority = (int)priority;

    assert (threadP != NULL);

    if (threadP != NULL)
    {
       // ret = pthread_setschedparam(threadP->mThreadID, SCHED_RR, &param);
       // if (ret == 0)
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}



#elif defined(RMX_OSAL_BERTOS)

int osal_threadInit(osal_thread_T* threadP,
                    const char* nameP,
                    OSAL_THREADFUNC_TYPE (*funcP) (OSAL_THREADFUNC_ARG_TYPE),
                    void* dataP,
                    osal_thread_priority_T priority,
                    size_t stackSize)
{
    if ( threadP != NULL )
    {
        threadP->nameP = nameP;
        threadP->mProcess_P = proc_new(funcP, dataP, stackSize, NULL);
        osal_threadSetPriority(threadP, priority );
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}


int osal_threadSetPriority(osal_thread_T* threadP, osal_thread_priority_T priority )
{
    if (threadP != NULL)
    {
        proc_setPri(threadP->mProcess_P, (int)priority);
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}



#elif defined(RMX_OSAL_COOCOX)

int osal_threadInit(osal_thread_T* threadP,
                    const char* nameP,
                    OSAL_THREADFUNC_TYPE (*funcP) (OSAL_THREADFUNC_ARG),
                    void* dataP,
                    osal_thread_priority_T priority,
                    size_t stackSize)

{
    if ( threadP != NULL )
    {
        threadP->nameP = nameP;
        stackSize = stackSize/(sizeof(OS_STK));  // coos wants stacksize in words
        threadP->mStack_P = (OS_STK*)osal_malloc(sizeof(OS_STK) * stackSize);
        if (threadP->mStack_P != NULL)
        {
            threadP->mTaskID = CoCreateTask(funcP,
                                            dataP, (U8)priority,
                                            (OS_STK*)&threadP->mStack_P[stackSize-1],
                                            (U16) stackSize);

            if (threadP->mTaskID != E_CREATE_FAIL)
            {
                return (RMX_SUCCESS);
            }
        }
    }
    return (RMX_FAIL);
}

int osal_threadSetPriority(osal_thread_T* threadP, osal_thread_priority_T priority )
{
    StatusType ret;

    if (threadP != NULL)
    {
        ret = CoSetPriority(threadP->mTaskID, (U8)priority);
        if (ret == E_OK)
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}


#elif defined(RMX_OSAL_FREERTOS)

int osal_threadInit(osal_thread_T* threadP,
                    const char* nameP,
                    OSAL_THREADFUNC_TYPE (*funcP) (OSAL_THREADFUNC_ARG),
                    void* dataP,
                    osal_thread_priority_T priority,
                    size_t stackSize)

{
    portBASE_TYPE ret;

    if ( threadP != NULL )
    {
        threadP->nameP = nameP;
        stackSize = stackSize/(sizeof(portSTACK_TYPE));  // freertos wants stacksize in words
        if (stackSize < configMINIMAL_STACK_SIZE) stackSize = configMINIMAL_STACK_SIZE;

        ret = xTaskCreate( funcP, ( signed portCHAR * ) nameP, stackSize, dataP, priority, &threadP->mTaskHandle );
        if ( ret == pdPASS)
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}

int osal_threadSetPriority(osal_thread_T* threadP, osal_thread_priority_T priority )
{
    if (threadP != NULL)
    {
        //proc_setPri(threadP->mProcess_P, (int)priority);
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
    /* This function will get called if a task overflows its stack. */

    ( void ) pxTask;
    ( void ) pcTaskName;

    for( ;; );
}
/*-----------------------------------------------------------*/



#elif defined(RMX_OSAL_CHIBIOS)

int osal_threadInit(osal_thread_T* threadP,
                    const char* nameP,
                    OSAL_THREADFUNC_TYPE (*funcP) (OSAL_THREADFUNC_ARG),
                    void* dataP,
                    osal_thread_priority_T priority,
                    size_t stackSize)

{
    portBASE_TYPE ret;

    if ( threadP != NULL )
    {
        threadP->nameP = nameP;
        stackSize = stackSize/(sizeof(portSTACK_TYPE));  // freertos wants stacksize in words
        if (stackSize < configMINIMAL_STACK_SIZE) stackSize = configMINIMAL_STACK_SIZE;

        ret = xTaskCreate( funcP, ( signed portCHAR * ) nameP, stackSize, dataP, priority, &threadP->mTaskHandle );
        if ( ret == pdPASS)
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}

int osal_threadSetPriority(osal_thread_T* threadP, osal_thread_priority_T priority )
{
    if (threadP != NULL)
    {
        //proc_setPri(threadP->mProcess_P, (int)priority);
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
    /* This function will get called if a task overflows its stack. */

    ( void ) pxTask;
    ( void ) pcTaskName;

    for( ;; );
}
/*-----------------------------------------------------------*/



#else
#error Please define a RMX_OSAL_XXXX

#endif
