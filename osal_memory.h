/**
 * \file
 * <!--
 * This file is part of osal - OS abstraction layer.
 *
 *
 * Copyright 2009-2013 Phillip Yeager
 *
 *
 * \brief Memory heap interface
 *
 * This module provides memory heap functionality for osal
 *
 * \author Phillip Yeager <monstermoto@yahoo.com>
 */


#ifndef OSAL_MEMORY_H
#define OSAL_MEMORY_H



#ifdef __cplusplus
extern "C"
{
#endif



#if defined(RMX_OSAL_PTHREAD)

#include <stdlib.h>

#define osal_malloc(size) 		malloc(size)
#define osal_free(pMem) 		free(pMem)

    extern int 		osal_heapInit(void);
    extern size_t 	osal_getFreeHeapBytes(void);


#elif defined(RMX_OSAL_BERTOS)

#include "bertos/struct/heap.h"

    extern int 		osal_heapInit(void);
    extern void*  	osal_malloc(size_t bytes);
    extern void 	osal_free(void* memP);
    extern size_t 	osal_getFreeHeapBytes(void);


#elif defined(RMX_OSAL_COOCOX)

#include "kern/CoOS/coocox.h"

#if CFG_KHEAP_EN < 1
#error Set CFG_KHEAP_EN in Coocox OSConfig.h to use heap functions
#warning Also check the KHEAP_SIZE setting in Coocox OSConfig.h
#endif

#define osal_malloc(size) 			CoKmalloc(size)
#define osal_free(pMem) 			CoKfree(pMem)
#define osal_getFreeHeapBytes()		0

    extern int 	osal_heapInit(void);


#elif defined(RMX_OSAL_FREERTOS)

#include "kern/freertos/include/FreeRTOS.h"
#include "kern/freertos/include/task.h"

#define osal_malloc(size) 			pvPortMalloc(size)
#define osal_free(pMem) 			vPortFree(pMem)
#define osal_getFreeHeapBytes() 	xPortGetFreeHeapSize()

    extern int 	osal_heapInit(void);


#elif defined(RMX_OSAL_CHIBIOS)

#include "kern/chibios/os/kernel/include/ch.h"

    extern int 		osal_heapInit(void);
    extern void*  	osal_malloc(size_t bytes);
    extern void 	osal_free(void* memP);
    extern size_t 	osal_getFreeHeapBytes(void);



#else
#error Please define a RMX_OSAL_XXXX
#endif




#ifdef __cplusplus
}
#endif

#endif // OSAL_MEMORY_H
