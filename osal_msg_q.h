/**
 * \file
 * <!--
 * This file is part of osal - OS abstraction layer.
 *
 *
 * Copyright 2009-2013 Phillip Yeager
 *
 *
 * \brief Message Queue interface
 *
 * This module provides message queue functionality for osal
 *
 * \author Phillip Yeager <monstermoto@yahoo.com>
 */


#ifndef RMX_OSAL_MSG_Q_H
#define RMX_OSAL_MSG_Q_H




#ifdef __cplusplus
extern "C"
{
#endif



#if defined(RMX_OSAL_PTHREAD)

#define OSAL_MSGQ_POSTSVC_WAIT     0  /* wait/block until space on the queue */
#define OSAL_MSGQ_POSTSVC_MILK     1  /* throw away the old */
#define OSAL_MSGQ_POSTSVC_WINE     2  /* throw away the new */


#include <pthread.h>
#include "rmx/osal/osal.h"
#include "rmx/osal/osal_mutex.h"
#include "rmx/spsc_fifo/ptr_spsc_fifo.h"

    typedef  struct
    {
        osal_mutex_T    mMutex;
        const char*     mNameP;
        int32_t         mPostSvcType;
        uint32_t        mPostDrops;
        ptr_SPSC_fifo_T mPtrSPSC;
        ptr_SPSC_data_T mDataP;
    } osal_msg_q_T;


#elif defined(RMX_OSAL_BERTOS)

#include "bertos/kern/msg.h"

    typedef struct
    {
        Msg msg;
        void * mDataP;
    } bertos_msg_wrap_T;

    typedef  struct
    {
        MsgPort mMsgPort;
    } osal_msg_q_T;


#elif defined(RMX_OSAL_COOCOX)

#include "kern/CoOS/coocox.h"

    typedef  struct
    {
        OS_EventID mQueueID;
        void * mHeadP;
    } osal_msg_q_T;


#elif defined(RMX_OSAL_FREERTOS)

#include "kern/freertos/include/FreeRTOS.h"
#include "kern/freertos/include/queue.h"

    typedef  struct
    {
        xQueueHandle mQueueHandle;
    } osal_msg_q_T;


#else
#error Please define a RMX_OSAL_XXXX
#endif

    extern int osal_msg_qCreate(osal_msg_q_T* queueP, size_t depth);
    extern int osal_msg_qPost(osal_msg_q_T* queueP, void * msgP);
    extern int osal_msg_qPostISR(osal_msg_q_T* queueP, void * msgP);
    extern void* osal_msg_qPend(osal_msg_q_T* queueP, int msTimeOut);
    extern int osal_msg_qDelete(osal_msg_q_T* queueP);

#ifdef __cplusplus
}
#endif

#endif /* UXV_OSAL_MSG_Q_H */
