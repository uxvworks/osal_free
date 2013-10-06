/**
 * \file
 * <!--
 * This file is part of osal - OS abstraction layer.
 *
 *
 * Copyright 2009-2013 Phillip Yeager
 *
 *
 * \brief Timer interface
 *
 * This module provides time delay functionality for osal
 *
 * \author Phillip Yeager <monstermoto@yahoo.com>
 */

#include "osal_free/osal.h"
#include "osal_free/osal_timer.h"


#if defined(RMX_OSAL_PTHREAD)

#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>


void osal_sleepTimerMsec(uint16_t msec)
{
    struct timespec ts;

    //usleep(msec * 1000);  OLD WAY

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * (1000 * 1000);
    nanosleep(&ts,NULL);
}


void osal_usleep(uint32_t usec)
{
    struct timespec ts;

    ts.tv_sec = usec / 1000000;
    ts.tv_nsec = (usec % 1000000) * (1000);
    nanosleep(&ts,NULL);
}

// this is intended for intervals measurement
// note the difference between CLOCK_REALTIME and CLOCK_MONOTONIC
inline uint64_t osal_getMsecTicks(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t) ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}


// this is intended for intervals measurement, not timestamping
// note the difference between CLOCK_REALTIME and CLOCK_MONOTONIC
inline uint64_t osal_getUsecTicks(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t) ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}


// this is intended for timestamping, not intervals measurement
// note the difference between CLOCK_REALTIME and CLOCK_MONOTONIC
inline uint64_t osal_getUsecTime(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (uint64_t) ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}




inline bool osal_eggTimerExpired(osal_egg_timer_T *ti)
{
    assert (ti != NULL);

    uint64_t sample = osal_getUsecTicks();

    if ((sample - ti->start) >= ti->interval)
    {
        ti->start = ti->finish;
        ti->finish = ti->start + ti->interval;
        return (true);
    }
    else
    {
        return (false);
    }
}


inline void osal_eggTimerReset(osal_egg_timer_T *ti, uint64_t usec)
{
    assert (ti != NULL);

    ti->interval = usec;
    ti->start = osal_getUsecTicks();
    ti->finish = ti->start + ti->interval;
}


inline uint64_t osal_eggTimerGetTime(osal_egg_timer_T *ti)
{
    assert (ti != NULL);

    uint64_t sample = osal_getUsecTicks();
    return (sample - ti->start);
}



static OSAL_THREADFUNC_TYPE osal_timerThreadFunc(void* dataP)
{
    osal_timer_T* timerP = NULL;
    timerP = (osal_timer_T*)dataP;

    while (!osal_program_interrupted)
    {
        osal_sleepTimerMsec(timerP->mDelay);  // TODO:  use an eggTimer
        timerP->mCallbackFunc();
    }
    return NULL;
}

int osal_swTimerCreate(osal_timer_T* timerP, int timerType, int msec, OSAL_TIMERFUNC_TYPE (*func) (void))
{
    if ( timerP != NULL )
    {
        timerP->mType = timerType;
        timerP->mCallbackFunc = func;
        timerP->mDelay = msec;
        osal_threadInit(&timerP->mThread, "TIMER", osal_timerThreadFunc, timerP, OSAL_THREAD_PRIORITY_HIGH, 1024);
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

int osal_swTimerStart(osal_timer_T* timerP)
{
    (void)timerP; // gets rid of unused parameter warning
    return (RMX_SUCCESS);
}



#elif defined(RMX_OSAL_BERTOS)

#include "bertos/drv/timer.h"

void osal_sleepTimerMsec(uint16_t msec)
{
    timer_delay(msec);
}


static void bertos_timer_hook(iptr_t dataP)
{
    osal_timer_T *timerP = (osal_timer_T *)(void *)dataP;

    timerP->mCallbackFunc(/*&timerP->mData*/);

    if (timerP->mType == OSAL_TIMER_PERIODIC)
    {
        timer_add(&timerP->mTimer);
    }
}

int osal_swTimerCreate(osal_timer_T* timerP, int timerType, int msec, OSAL_TIMERFUNC_TYPE (*func) (void))
{
    if ( timerP != NULL )
    {
        timerP->mType = timerType;
        timerP->mCallbackFunc = func;
        timerP->mDelay = msec;
        timer_setDelay(&timerP->mTimer, ms_to_ticks(msec));
        timer_setSoftint(&timerP->mTimer, bertos_timer_hook, (iptr_t)timerP);
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

int osal_swTimerStart(osal_timer_T* timerP)
{
    timer_add(&timerP->mTimer);
    return (RMX_SUCCESS);
}

int osal_swTimerStop(osal_timer_T* timerP)
{

    return (RMX_FAIL);
}



#elif defined(RMX_OSAL_COOCOX)

#include "kern/CoOS/coocox.h"

void osal_sleepTimerMsec(uint16_t msec)
{
    CoTimeDelay(0,0,msec/1000,msec%1000);
}

uint64_t osal_getUsecTicks(void)
{
    uint64_t ticks = CoGetOSTime();
    ticks = ticks * ( 1000000 / CFG_SYSTICK_FREQ);
    return(ticks);
}


int osal_swTimerCreate(osal_timer_T* timerP, int timerType, int msec, OSAL_TIMERFUNC_TYPE (*func) (void))
{
    if ( timerP != NULL )
    {
        timerP->mType = timerType;
        timerP->mCallbackFunc = func;
        timerP->mDelay = msec;

        timerP->mTimerID = CoCreateTmr((timerType == OSAL_TIMER_ONE_SHOT) ? TMR_TYPE_ONE_SHOT : TMR_TYPE_PERIODIC,
                                       (msec*CFG_SYSTICK_FREQ)/1000,
                                       (msec*CFG_SYSTICK_FREQ)/1000, func);
        if (timerP->mTimerID != E_CREATE_FAIL)
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}

int osal_swTimerStart(osal_timer_T* timerP)
{
    if (CoStartTmr(timerP->mTimerID) == E_OK)
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

int osal_swTimerStop(osal_timer_T* timerP)
{
    if (CoStopTmr(timerP->mTimerID) == E_OK)
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}


#elif defined(RMX_OSAL_FREERTOS)

#include "kern/freertos/include/FreeRTOS.h"
#include "kern/freertos/include/task.h"
#include "kern/freertos/include/timers.h"

void osal_sleepTimerMsec(uint16_t msec)
{
    vTaskDelay( (portTickType)(msec) / portTICK_RATE_MS);
}

uint64_t osal_getUsecTicks(void)
{
    uint64_t ticks = xTaskGetTickCount();
    ticks = ticks * ( 1000000 / configTICK_RATE_HZ);
    return(ticks);
}


static void freertos_timer_hook(xTimerHandle xTimer)
{

    osal_timer_T *timerP;
    timerP = ( osal_timer_T * ) pvTimerGetTimerID( xTimer );
    timerP->mCallbackFunc();

}


int osal_swTimerCreate(osal_timer_T* timerP, int timerType, int msec, OSAL_TIMERFUNC_TYPE (*func) (void))
{
    if ( timerP != NULL )
    {
        timerP->mType = timerType;
        timerP->mCallbackFunc = func;
        timerP->mDelay = msec;

        timerP->mTimerHandle = xTimerCreate( ( const signed char * ) "Timer",
                                             (portTickType)(msec) / portTICK_RATE_MS,
                                             (timerType == OSAL_TIMER_ONE_SHOT) ? pdFALSE : pdTRUE,
                                             (void *) timerP,
                                             freertos_timer_hook );
        if ( timerP->mTimerHandle != NULL )
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}

int osal_swTimerStart(osal_timer_T* timerP)
{
    if (xTimerStart( timerP->mTimerHandle, (portTickType) 0 ) == pdTRUE )
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

int osal_swTimerStop(osal_timer_T* timerP)
{
    if (xTimerStop( timerP->mTimerHandle, (portTickType) 0 ) == pdTRUE )
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}



#elif defined(RMX_OSAL_CHIBIOS)

#include "kern/chibios/os/kernel/include/ch.h"

void osal_sleepTimerMsec(uint16_t msec)
{
    chThdSleepMilliseconds(msec);
}

uint32_t osal_getUsecTicks(void)
{
    uint32_t ticks = xTaskGetTickCount();
    ticks = ticks * ( 1000000 / configTICK_RATE_HZ);
    return(ticks);
}


static void freertos_timer_hook(xTimerHandle xTimer)
{

    osal_timer_T *timerP;
    timerP = ( osal_timer_T * ) pvTimerGetTimerID( xTimer );
    timerP->mCallbackFunc();

}


int osal_swTimerCreate(osal_timer_T* timerP, int timerType, int msec, OSAL_TIMERFUNC_TYPE (*func) (void))
{
    if ( timerP != NULL )
    {
        timerP->mType = timerType;
        timerP->mCallbackFunc = func;
        timerP->mDelay = msec;

        timerP->mTimerHandle = xTimerCreate( ( const signed char * ) "Timer",
                                             (portTickType)(msec) / portTICK_RATE_MS,
                                             (timerType == OSAL_TIMER_ONE_SHOT) ? pdFALSE : pdTRUE,
                                             (void *) timerP,
                                             freertos_timer_hook );
        if ( timerP->mTimerHandle != NULL )
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}

int osal_swTimerStart(osal_timer_T* timerP)
{
    if (xTimerStart( timerP->mTimerHandle, (portTickType) 0 ) == pdTRUE )
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

int osal_swTimerStop(osal_timer_T* timerP)
{
    if (xTimerStop( timerP->mTimerHandle, (portTickType) 0 ) == pdTRUE )
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}



#else
#error Please define a RMX_OSAL_XXXX

#endif
