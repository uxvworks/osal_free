/**
 * \file
 * <!--
 * This file is part of osal - OS abstraction layer.
 *
 * osal is not free software.
 *
 * Copyright 2009-2011 Phillip Yeager
 *
 * -->
 *
 * \brief Message Queueinterface
 *
 * This module provides message queue functionality for osal
 *
 * \author Phillip Yeager <monstermoto@yahoo.com>
 */

#include <stdio.h>


#include "osal_free/osal.h"
#include "osal_free/osal_memory.h"
#include "osal_free/osal_timer.h"
#include "osal_free/osal_msg_q.h"
#include "spsc_fifo/ptr_spsc_fifo.h"


#if defined(RMX_OSAL_PTHREAD)

#include <assert.h>


int osal_msg_qCreate(osal_msg_q_T* queueP, size_t depth)
{
    assert(queueP != NULL);

    if (!queueP->mNameP) queueP->mNameP = "nonameQ";

    if (osal_mutexInit(&queueP->mMutex) == RMX_SUCCESS)
    {
        queueP->mPostDrops = 0;
        /* allocate the list of pointers to queue items */
        queueP->mDataP = (ptr_SPSC_data_T) osal_malloc(depth * sizeof(ptr_SPSC_data_T));
        if (queueP->mDataP != NULL )
        {
            ptr_SPSC_init(&queueP->mPtrSPSC, queueP->mDataP, depth);
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}


inline int osal_msg_qPost(osal_msg_q_T* queueP, void* msgP)
{
    assert(queueP != NULL);

    int rval;

    osal_mutexLock(&queueP->mMutex);

    switch (queueP->mPostSvcType)
    {
    case OSAL_MSGQ_POSTSVC_MILK:
    case OSAL_MSGQ_POSTSVC_WINE:
        if (ptr_SPSC_isfull(&queueP->mPtrSPSC))
        {
            rval = RMX_FAIL;
            queueP->mPostDrops++;
        }
        else
        {
            ptr_SPSC_push(&queueP->mPtrSPSC, msgP);
            rval = RMX_SUCCESS;
        }
        break;

    case OSAL_MSGQ_POSTSVC_WAIT:
    default:
        while (ptr_SPSC_isfull(&queueP->mPtrSPSC))
        {
            osal_mutexUnlock(&queueP->mMutex);
            osal_sleepTimerMsec(1);
            osal_mutexLock(&queueP->mMutex);
        }
        ptr_SPSC_push(&queueP->mPtrSPSC, msgP);
        rval = RMX_SUCCESS;
    }

    osal_mutexUnlock(&queueP->mMutex);

    return (rval);
}

inline int osal_msg_qPostISR(osal_msg_q_T* queueP, void* msgP)
{
    return (osal_msg_qPost( queueP,  msgP));
}

inline void* osal_msg_qPend(osal_msg_q_T* queueP, int msTimeOut)
{
    void * msgP = NULL;

    assert(queueP != NULL);

    osal_mutexLock(&queueP->mMutex);
    while (ptr_SPSC_isempty(&queueP->mPtrSPSC))
    {
        osal_mutexUnlock(&queueP->mMutex);
        if (msTimeOut <= 0)
        {
            return (msgP);
        }
        osal_sleepTimerMsec(1);
        msTimeOut--;
        osal_mutexLock(&queueP->mMutex);
    }
    msgP = ptr_SPSC_pop(&queueP->mPtrSPSC);

    osal_mutexUnlock(&queueP->mMutex);

    return (msgP);  /* error or timeout */
}

int osal_msg_qDelete(osal_msg_q_T* queueP)
{
    assert(queueP != NULL);

    if (queueP->mDataP != NULL)
    {
        osal_free(queueP->mDataP);
        return (RMX_SUCCESS);
    }
    else
    {
        return (RMX_FAIL);
    }
}





#elif defined(RMX_OSAL_BERTOS)

/* the receiver of the messages should create the queue!!!  to receive the signals */
int osal_msg_qCreate(osal_msg_q_T* queueP, size_t depth)
{
    if ( queueP != NULL )
    {
        msg_initPort(&queueP->mMsgPort, event_createSignal(proc_current(), SIG_USER0));
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

inline int osal_msg_qPost(osal_msg_q_T* queueP, void* msgP)
{
    bertos_msg_wrap_T *bertosMsg = NULL;

    /* Create the bertos msg wrapper, ugghh! todo: use depth value and mempool to preallocate in the create function...*/
    bertosMsg = (bertos_msg_wrap_T *) osal_malloc(sizeof(bertos_msg_wrap_T));
    if (bertosMsg != NULL)
    {
        bertosMsg->mDataP = msgP;  /* the osal user message data! */
        bertosMsg->msg.replyPort = &queueP->mMsgPort;
        msg_put(&queueP->mMsgPort, &bertosMsg->msg);
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

inline int osal_msg_qPostISR(osal_msg_q_T* queueP, void* msgP)
{
    /* don't think this will work with a malloc inline... */
    return (RMX_FAIL);
}

inline void* osal_msg_qPend(osal_msg_q_T* queueP, int msTimeOut)
{
    void * msgP = NULL;
    bertos_msg_wrap_T *bertosMsg = NULL;

    //sig_wait(SIG_USER0);

    while (msTimeOut >= 0)
    {
        bertosMsg = NULL;
        if ((bertosMsg = containerof(msg_get(&queueP->mMsgPort), bertos_msg_wrap_T, msg)))
        {
            msgP = bertosMsg->mDataP;
            osal_free(bertosMsg);
            return(msgP);
        }
        osal_sleepTimerMsec(1);
        msTimeOut--;
    }
    return (NULL);
}

int osal_msg_qDelete(osal_msg_q_T* queueP)
{
    return (RMX_FAIL);
}




#elif defined(RMX_OSAL_COOCOX)

int osal_msg_qCreate(osal_msg_q_T* queueP, size_t depth)
{
    if ( queueP != NULL )
    {
        /* Create the list of pointers to queue items */
        queueP->mHeadP = (void *) osal_malloc(depth * sizeof(void*));
        if (queueP->mHeadP != NULL )
        {
            queueP->mQueueID = CoCreateQueue(&queueP->mHeadP, depth , EVENT_SORT_TYPE_FIFO);
            if (queueP->mQueueID != E_CREATE_FAIL)
            {
                return (RMX_SUCCESS);
            }
        }
    }
    return (RMX_FAIL);
}

inline int osal_msg_qPost(osal_msg_q_T* queueP, void* msgP)
{
    if (CoPostQueueMail(queueP->mQueueID, msgP ) == E_OK)
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

inline int osal_msg_qPostISR(osal_msg_q_T* queueP, void* msgP)
{
    if (isr_PostQueueMail(queueP->mQueueID, msgP ) == E_OK)
    {
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}

inline void* osal_msg_qPend(osal_msg_q_T* queueP, int msTimeOut)
{
    void * msgP = NULL;
    StatusType errV;

    msgP = CoPendQueueMail(queueP->mQueueID, (msTimeOut*CFG_SYSTICK_FREQ)/1000, &errV);
    if (msgP)
    {
        return (msgP);
    }
    return (msgP);  /* error or timeout */
}

int osal_msg_qDelete(osal_msg_q_T* queueP)
{
    if (CoDelQueue(queueP->mQueueID, OPT_DEL_NO_PEND) == E_OK)
    {
        osal_free(queueP->mHeadP);
        return (RMX_SUCCESS);
    }
    return (RMX_FAIL);
}




#elif defined(RMX_OSAL_FREERTOS)

int osal_msg_qCreate(osal_msg_q_T* queueP, size_t depth)
{
    if ( queueP != NULL )
    {
        queueP->mQueueHandle = xQueueCreate((unsigned portBASE_TYPE)depth, (unsigned portBASE_TYPE)sizeof(void*));
        if (queueP->mQueueHandle)
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}

inline int osal_msg_qPost(osal_msg_q_T* queueP, void* msgP)
{
    if (queueP->mQueueHandle)
    {
        if (xQueueSend( queueP->mQueueHandle, &msgP, portMAX_DELAY ) == pdPASS)
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}

inline int osal_msg_qPostISR(osal_msg_q_T* queueP, void* msgP)
{
    portBASE_TYPE xHigherPriorityTaskWoken;

    /* We have not woken a task at the start of the ISR.*/
    xHigherPriorityTaskWoken = pdFALSE;

    if (queueP->mQueueHandle)
    {
        if (xQueueSendFromISR( queueP->mQueueHandle, &msgP, &xHigherPriorityTaskWoken) == pdPASS)
        {
            return (RMX_SUCCESS);
        }
    }
    return (RMX_FAIL);
}

inline void* osal_msg_qPend(osal_msg_q_T* queueP, int msTimeOut)
{
    void * msgP = NULL;

    if ( xQueueReceive( queueP->mQueueHandle, &msgP, msTimeOut*portTICK_RATE_MS ) == pdPASS )
    {
        return (msgP);
    }
    return (msgP);  /* error or timeout */
}

int osal_msg_qDelete(osal_msg_q_T* queueP)
{
    vQueueDelete(queueP->mQueueHandle);
    return (RMX_SUCCESS);
}


#else
#error Please define a RMX_OSAL_XXXX

#endif
