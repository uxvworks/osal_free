/**
 * \file
 * <!--
 * This file is part of osal - OS abstraction layer.
 *
 *
 * Copyright 2009-2013 Phillip Yeager
 *
 *
 * \brief OS and program(process) signaling
 *
 * This module provides program(process) functionality for osal
 *
 * \author Phillip Yeager <monstermoto@yahoo.com>
 */


#include "osal_free/osal.h"

volatile int osal_program_interrupted = 0;     //  app signal handler sets this global to indicate osal threads should clean up and exit

#if defined(RMX_OSAL_PTHREAD)

#include <assert.h>
#include <signal.h>



#if !defined(OSAL_CFG_CUSTOM_SIGNAL_HANDLER)
static void osal_signal_handler (int signal_value)
{
    osal_program_interrupted = 1;
    (void)signal_value; // gets rid of unused parameter warning
    //printf("osal_signal_handler: received signal %d\n", signal_value);
}

static void osal_install_signal_handler(void)
{
    struct sigaction action;
    action.sa_handler = osal_signal_handler;
    action.sa_flags = 0;
    sigemptyset (&action.sa_mask);
    action.sa_flags =  SA_SIGINFO;

    sigaction (SIGINT, &action, NULL);
    sigaction (SIGTERM, &action, NULL);
    sigaction (SIGABRT, &action, NULL);
    sigaction (SIGSEGV, &action, NULL);
    sigaction (SIGFPE, &action, NULL);
    sigaction (SIGILL, &action, NULL);
    sigaction (SIGSTKFLT, &action, NULL);
    sigaction (SIGUSR1, &action, NULL);
    sigaction (SIGUSR2, &action, NULL);
}
#else  // custom signal handler used
extern void osal_install_signal_handler();
#endif



void osal_init(void)
{
    osal_install_signal_handler();
}

void osal_exit(void)
{

}


#elif defined(RMX_OSAL_BERTOS)

#elif defined(RMX_OSAL_COOCOX)

#elif defined(RMX_OSAL_FREERTOS)

#elif defined(RMX_OSAL_CHIBIOS)

#else

#error Please define a RMX_OSAL_XXXX

#endif
