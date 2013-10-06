/**
 * \file
 * <!--
 * This file is part of osal - OS abstraction layer.
 *
 *
 * Copyright 2009-2013 Phillip Yeager
 *
 *
 * \brief  osal interface
 *
 * This module provides config and defs for osal
 *
 * \author Phillip Yeager <monstermoto@yahoo.com>
 */


#ifndef _FREE__OSAL_H
#define _FREE__OSAL_H


#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C"
{
#endif


extern volatile int osal_program_interrupted;


#if defined(RMX_OSAL_PTHREAD)

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


extern void osal_init(void);
#define osal_start()
extern void osal_exit(void);


#define RMX_KERN_STRING 	"PTHREAD"



#elif defined(RMX_OSAL_BERTOS)

#include "bertos/kern/proc.h"

#define osal_init() 		 IRQ_ENABLE;timer_init();proc_init()
#define osal_start()
#define osal_exit()

#define RMX_KERN_STRING 	"BeRTOS"


#elif defined(RMX_OSAL_COOCOX)

#include "kern/CoOS/coocox.h"

#define osal_init() 		CoInitOS()
#define osal_start() 		CoStartOS()
#define osal_exit()

#define RMX_KERN_STRING 	"CoOS"


#elif defined(RMX_OSAL_FREERTOS)

#include "kern/freertos/include/FreeRTOS.h"
#include "kern/freertos/include/task.h"

#define osal_init()
#define osal_start() 		vTaskStartScheduler()
#define osal_exit()

#define RMX_KERN_STRING 	"FreeRTOS"


#elif defined(RMX_OSAL_CHIBIOS)

#include "kern/chibios/os/kernel/include/ch.h"

#define osal_init()			chSysInit()
#define osal_start()
#define osal_exit()

#define RMX_KERN_STRING 	"ChibiOS"

#else
#error Please define a RMX_OSAL_XXXX
#endif


#ifdef __cplusplus
}
#endif

#endif // _FREE_OSAL_H
