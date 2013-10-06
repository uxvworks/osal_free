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



#include "osal/osal.h"
#include "osal/osal_mutex.h"


#if defined(RMX_OSAL_PTHREAD)

#include <assert.h>

int osal_mutexInit(osal_mutex_T* mutexP)
{
    assert (mutexP != NULL);

    if (pthread_mutex_init(&mutexP->mMutex, NULL) == 0)
    {
        return (RMX_SUCCESS);
    }
    else
    {
        return (RMX_FAIL);
    }
}

inline int osal_mutexLock(osal_mutex_T* mutexP)
{
    assert (mutexP != NULL);

    if (pthread_mutex_lock(&mutexP->mMutex) == 0)
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

inline int osal_mutexUnlock(osal_mutex_T* mutexP)
{
    assert (mutexP != NULL);

    if (pthread_mutex_unlock(&mutexP->mMutex) == 0)
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}


#elif defined(RMX_OSAL_BERTOS)

int osal_mutexInit(osal_mutex_T* mutexP)
{
    if ( mutexP != NULL )
    {
        sem_init(&mutexP->mSemaphore);
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

inline int osal_mutexLock(osal_mutex_T* mutexP)
{
    sem_obtain(&mutexP->mSemaphore);
    return (RMX_SUCCESS);
}

inline int osal_mutexUnlock(osal_mutex_T* mutexP)
{
    sem_release(&mutexP->mSemaphore);
    return (RMX_SUCCESS);
}


#elif defined(RMX_OSAL_COOCOX)

int osal_mutexInit(osal_mutex_T* mutexP)
{
    if ( mutexP != NULL )
    {
        mutexP->mMutexID = CoCreateMutex();
        if (mutexP->mMutexID != E_CREATE_FAIL)
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}

inline int osal_mutexLock(osal_mutex_T* mutexP)
{
    if (CoEnterMutexSection(mutexP->mMutexID) == E_OK)
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

inline int osal_mutexUnlock(osal_mutex_T* mutexP)
{
    if (CoLeaveMutexSection(mutexP->mMutexID) == E_OK)
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}



#elif defined(RMX_OSAL_FREERTOS)

int osal_mutexInit(osal_mutex_T* mutexP)
{
    if ( mutexP != NULL )
    {
        mutexP->mMutexHandle = xSemaphoreCreateMutex();
        if ( mutexP->mMutexHandle != NULL )
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}

inline int osal_mutexLock(osal_mutex_T* mutexP)
{
    if (xSemaphoreTake( mutexP->mMutexHandle, (portTickType) portMAX_DELAY ) == pdTRUE )
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

inline int osal_mutexUnlock(osal_mutex_T* mutexP)
{
    if (xSemaphoreGive( mutexP->mMutexHandle ) == pdTRUE)
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}



#elif defined(RMX_OSAL_CHIBIOS)

int osal_mutexInit(osal_mutex_T* mutexP)
{
    if ( mutexP != NULL )
    {
        chMtxInit(&mutexP->mMutex);
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

inline int osal_mutexLock(osal_mutex_T* mutexP)
{
    chMtxLock(&mutexP->mMutex);
    return (RMX_SUCCESS);
}

inline int osal_mutexUnlock(osal_mutex_T* mutexP)
{
    chMtxUnlock();
    return (RMX_SUCCESS);
}


#else
#error Please define a RMX_OSAL_XXXX

#endif
