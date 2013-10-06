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


#ifndef RMX_OSAL_TIMER_H
#define RMX_OSAL_TIMER_H


#include "osal/osal_thread.h"


#ifdef __cplusplus
extern "C"
{
#endif


    /*---------------------------- swTimer Types  --------------------------------*/
#define OSAL_TIMER_ONE_SHOT     0         /*!< Timer  type: One-shot     */
#define OSAL_TIMER_PERIODIC     1         /*!< Timer  type: Periodic     */



#if defined(RMX_OSAL_PTHREAD)

#include <pthread.h>

#define OSAL_TIMERFUNC_TYPE  void*

    typedef  struct
    {
        int	mType;
        int mData;
        int mDelay;
        OSAL_TIMERFUNC_TYPE (*mCallbackFunc) (void);
        osal_thread_T mThread;
    } osal_timer_T;

    typedef struct
    {
        uint64_t start;
        uint64_t finish;
        uint64_t interval;
    } osal_egg_timer_T;

    extern void osal_usleep(uint32_t usec);
    extern uint64_t osal_getUsecTime(void);
    extern void osal_eggTimerReset(osal_egg_timer_T *timer, uint64_t usec);
    extern bool osal_eggTimerExpired(osal_egg_timer_T *timer);
    extern uint64_t osal_eggTimerGetTime(osal_egg_timer_T *timer);

#elif defined(RMX_OSAL_BERTOS)

#include "bertos/drv/timer.h"


#define OSAL_TIMERFUNC_TYPE  void

    typedef  struct
    {
        int	mType;
        int mData;
        int mDelay;
        OSAL_TIMERFUNC_TYPE (*mCallbackFunc) (void);
        Timer mTimer;
    } osal_timer_T;


#elif defined(RMX_OSAL_COOCOX)

#include "kern/CoOS/coocox.h"

#define OSAL_TIMERFUNC_TYPE void

    typedef  struct
    {
        int	mType;
        int mData;
        int mDelay;
        OSAL_TIMERFUNC_TYPE (*mCallbackFunc) (void);
        OS_TCID mTimerID;
    } osal_timer_T;


#elif defined(RMX_OSAL_FREERTOS)

#include "kern/freertos/include/FreeRTOS.h"
#include "kern/freertos/include/timers.h"

#define OSAL_TIMERFUNC_TYPE  void

    typedef  struct
    {
        int	mType;
        int mData;
        int mDelay;
        OSAL_TIMERFUNC_TYPE (*mCallbackFunc) (void);
        xTimerHandle mTimerHandle;
    } osal_timer_T;


#else
#error Please define a RMX_OSAL_XXXX
#endif



    extern void osal_sleepTimerMsec(uint16_t msec);

    extern uint64_t osal_getMsecTicks(void);
    extern uint64_t osal_getUsecTicks(void);


    extern int osal_swTimerCreate(osal_timer_T* timerP, int timerType, int msec,
                                  OSAL_TIMERFUNC_TYPE (*funcP) (void));

    extern int osal_swTimerStart(osal_timer_T* timerP);
    extern int osal_swTimerStop(osal_timer_T* timerP);


#ifdef __cplusplus
}
#endif

#endif // RMX_OSAL_TIMER_H
