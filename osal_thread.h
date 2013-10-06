/**
 * \file
 * <!--
 * This file is part of osal - OS abstraction layer.
 *
 *
 * Copyright 2009-2013 Phillip Yeager
 *
 *
 * \brief Trread interface
 *
 * This module provides thread functionality for osal
 *
 * \author Phillip Yeager <monstermoto@yahoo.com>
 */


#ifndef UXV_OSAL_THREAD_H
#define UXV_OSAL_THREAD_H




#ifdef __cplusplus
extern "C"
{
#endif


#if defined(RMX_OSAL_PTHREAD)

#include <pthread.h>

#define OSAL_THREADFUNC_TYPE  				void*
#define OSAL_THREADFUNC_ARG_TYPE			void*
#define OSAL_THREADFUNC_ARG_NAME			dataP


    typedef enum
    {
        OSAL_THREAD_PRIORITY_LOWEST=1,
        OSAL_THREAD_PRIORITY_LOWER=2,
        OSAL_THREAD_PRIORITY_LOW=3,
        OSAL_THREAD_PRIORITY_NORMAL=4,
        OSAL_THREAD_PRIORITY_HIGH=5,
        OSAL_THREAD_PRIORITY_HIGHER=6,
        OSAL_THREAD_PRIORITY_HIGHEST=7      // (this could be MAX_RT_PRIO-1) == 99
    } osal_thread_priority_T;



    typedef  struct
    {
        const char*			nameP;
        pthread_attr_t 	mAttr;
        pthread_t 		mThreadID;
    } osal_thread_T;



#elif defined(RMX_OSAL_BERTOS)

#include "bertos/kern/proc.h"

#define OSAL_THREADFUNC_TYPE  				void NORETURN
#define OSAL_THREADFUNC_ARG_TYPE			void
#define OSAL_THREADFUNC_ARG_NAME


    typedef enum
    {
        OSAL_THREAD_PRIORITY_LOWEST=-10,
        OSAL_THREAD_PRIORITY_LOWER=-7,
        OSAL_THREAD_PRIORITY_LOW=-3,
        OSAL_THREAD_PRIORITY_NORMAL=0,
        OSAL_THREAD_PRIORITY_HIGH=3,
        OSAL_THREAD_PRIORITY_HIGHER=7,
        OSAL_THREAD_PRIORITY_HIGHEST=10
    } osal_thread_priority_T;

    typedef  struct
    {
        char*			nameP;
        struct Process* mProcess_P;
    } osal_thread_T;



#elif defined(RMX_OSAL_COOCOX)

#include "kern/CoOS/coocox.h"

#define OSAL_THREADFUNC_TYPE  				void
#define OSAL_THREADFUNC_ARG_TYPE			void*
#define OSAL_THREADFUNC_ARG_NAME			dataP

    typedef enum
    {
        OSAL_THREAD_PRIORITY_LOWEST=CFG_LOWEST_PRIO-1,
        OSAL_THREAD_PRIORITY_LOWER=CFG_LOWEST_PRIO-2,
        OSAL_THREAD_PRIORITY_LOW=CFG_LOWEST_PRIO-3,
        OSAL_THREAD_PRIORITY_NORMAL=CFG_LOWEST_PRIO-4,
        OSAL_THREAD_PRIORITY_HIGH=CFG_LOWEST_PRIO-5,
        OSAL_THREAD_PRIORITY_HIGHER=CFG_LOWEST_PRIO-6,
        OSAL_THREAD_PRIORITY_HIGHEST=CFG_LOWEST_PRIO-7
    } osal_thread_priority_T;

    typedef  struct
    {
        char*			nameP;
        OS_STK* 		mStack_P;
        int 			mStackSize;
        OS_TID 			mTaskID;
    } osal_thread_T;


#elif defined(RMX_OSAL_FREERTOS)

#include "kern/freertos/include/FreeRTOS.h"
#include "kern/freertos/include/task.h"

#define OSAL_THREADFUNC_TYPE  				void
#define OSAL_THREADFUNC_ARG_TYPE			void*
#define OSAL_THREADFUNC_ARG_NAME			dataP


    typedef enum
    {
        OSAL_THREAD_PRIORITY_LOWEST=tskIDLE_PRIORITY+1,
        OSAL_THREAD_PRIORITY_LOWER=tskIDLE_PRIORITY+2,
        OSAL_THREAD_PRIORITY_LOW=tskIDLE_PRIORITY+3,
        OSAL_THREAD_PRIORITY_NORMAL=tskIDLE_PRIORITY+4,
        OSAL_THREAD_PRIORITY_HIGH=tskIDLE_PRIORITY+5,
        OSAL_THREAD_PRIORITY_HIGHER=tskIDLE_PRIORITY+6,
        OSAL_THREAD_PRIORITY_HIGHEST=tskIDLE_PRIORITY+7
    } osal_thread_priority_T;

    typedef  struct
    {
        char*			nameP;
        xTaskHandle 	mTaskHandle;
    } osal_thread_T;


#else
#error Please define a RMX_OSAL_XXXX
#endif




#define OSAL_THREADFUNC(thread)    OSAL_THREADFUNC_TYPE thread(OSAL_THREADFUNC_ARG_TYPE   OSAL_THREADFUNC_ARG_NAME)


    extern	int osal_threadInit(osal_thread_T* threadP,
                                const char* nameP,
                                OSAL_THREADFUNC_TYPE (*funcP) (OSAL_THREADFUNC_ARG_TYPE),
                                void* dataP,
                                osal_thread_priority_T priority,
                                size_t stackSize);


    extern int osal_threadSetPriority(osal_thread_T* threadP, osal_thread_priority_T priority );


#ifdef __cplusplus
}
#endif

#endif // UXV_OSAL_THREAD_H
