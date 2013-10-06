/**
 * \file
 * <!--
 * This file is part of osal - OS abstraction layer.
 *
 *
 * Copyright 2009-2013 Phillip Yeager
 *
 * \brief memory interface
 *
 * This module provides memory heap functionality for osal
 *
 * \author Phillip Yeager <monstermoto@yahoo.com>
 */

#include <stdlib.h>

#include "osal/osal.h"
#include "osal/osal_memory.h"



#if defined(RMX_OSAL_PTHREAD)
#include <linux/kernel.h>
//#include <linux/sys.h>
#include <sys/sysinfo.h>


int osal_heapInit(void)
{
    return (RMX_SUCCESS);
}

inline size_t osal_getFreeHeapBytes(void)
{
    /* Obtain system statistics. */
    struct sysinfo si;
    sysinfo (&si);
//	/* Summarize interesting values. */
//	printf (“system uptime : %ld days, %ld:%02ld:%02ld\n”,
//	si.uptime / day, (si.uptime % day) / hour,
//	(si.uptime % hour) / minute, si.uptime % minute);
//	printf (“total RAM
//	: %5.1f MB\n”, si.totalram / megabyte);
//printf (“free RAM
//: %5.1f MB\n”, si.freeram / megabyte);

    return (si.freeram);
}


#elif defined(RMX_OSAL_BERTOS)

static Heap mHeap;

HEAP_DEFINE_BUF(osal_HeapBuffer, CFG_RMX_KERN_HEAP_BYTES);
STATIC_ASSERT(sizeof(osal_HeapBuffer) % sizeof(heap_buf_t) == 0);

inline int osal_heapInit(void)
{
    heap_init(&mHeap, osal_HeapBuffer, sizeof(osal_HeapBuffer));
    return (RMX_SUCCESS);
}

inline void* osal_malloc(size_t size)
{
    return (heap_malloc(&mHeap, size));
}

inline void osal_free(void* memP)
{
    heap_free(&mHeap, memP);
}

void* malloc(size_t size)
{
    return osal_malloc(size);
}

void free(void *p)
{
    osal_free(p);
}

inline size_t osal_getFreeHeapBytes(void)
{
    return (heap_freeSpace(&mHeap));
}


#elif defined(RMX_OSAL_COOCOX)

int osal_heapInit(void)
{
    return (RMX_SUCCESS);
}

void* malloc(size_t size)
{
    return osal_malloc(size);
}

void free(void *p)
{
    osal_free(p);
}



#elif defined(RMX_OSAL_FREERTOS)

int osal_heapInit(void)
{
    return (RMX_SUCCESS);
}

void* malloc(size_t size)
{
    return osal_malloc(size);
}

void free(void *p)
{
    osal_free(p);
}



#elif defined(RMX_OSAL_CHIBIOS)

static MemoryHeap mHeap;

HEAP_DEFINE_BUF(osal_HeapBuffer, CFG_RMX_KERN_HEAP_BYTES);
STATIC_ASSERT(sizeof(osal_HeapBuffer) % sizeof(heap_buf_t) == 0);

inline int osal_heapInit(void)
{
    chHeapInit(&mHeap, osal_HeapBuffer, sizeof(osal_HeapBuffer));
    return (RMX_SUCCESS);
}

inline void* osal_malloc(size_t size)
{
    return (chHeapAlloc(&mHeap, size));
}

inline void osal_free(void* memP)
{
    chHeapFree(memP);
}

void* malloc(size_t size)
{
    return osal_malloc(size);
}

void free(void *p)
{
    osal_free(p);
}

inline size_t osal_getFreeHeapBytes(void)
{
    size_t frags;
    size_t free_space;

    frags = chHeapStatus(&mHeap, &free_space);
    return (free_space);
}



#else
#error Please define a RMX_OSAL_XXXX

#endif
