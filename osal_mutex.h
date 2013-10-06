/**
 * \file
 * <!--
 * This file is part of osal - OS abstraction layer.
 *
 *
 * Copyright 2009-2013 Phillip Yeager
 *
 *
 * \brief Mutex interface
 *
 * This module provides mutex functionality for osal
 *
 * \author Phillip Yeager <monstermoto@yahoo.com>
 */


#ifndef RMX_OSAL_MUTEX_H
#define RMX_OSAL_MUTEX_H




#ifdef __cplusplus
extern "C"
{
#endif


#if defined(RMX_OSAL_PTHREAD)

#include <pthread.h>

    typedef  struct
    {
        pthread_mutex_t mMutex;
    } osal_mutex_T;


#elif defined(RMX_OSAL_BERTOS)

#include "bertos/kern/sem.h"

    typedef  struct
    {
        Semaphore mSemaphore;
    } osal_mutex_T;


#elif defined(RMX_OSAL_COOCOX)

#include "kern/CoOS/coocox.h"

    typedef  struct
    {
        OS_MutexID mMutexID;
    } osal_mutex_T;


#elif defined(RMX_OSAL_FREERTOS)

#include "kern/freertos/include/FreeRTOS.h"
#include "kern/freertos/include/semphr.h"

    typedef  struct
    {
        xSemaphoreHandle mMutexHandle;
    } osal_mutex_T;


#elif defined(RMX_OSAL_CHIBIOS)

#include "kern/chibios/os/kernel/include/ch.h"

    typedef  struct
    {
        Mutex mMutex;
    } osal_mutex_T;


#else
#error Please define a RMX_OSAL_XXXX
#endif

    extern int osal_mutexInit(osal_mutex_T* mutexP);
    extern int osal_mutexLock(osal_mutex_T* mutexP);
    extern int osal_mutexUnlock(osal_mutex_T* mutexP);


#ifdef __cplusplus
}
#endif

#endif // RMX_OSAL_MUTEX_H
