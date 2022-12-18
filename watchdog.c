/*
"Implementation of driver functions for Watch dog timer on the FRDM-KL25Z development board" Created by Ashfaq Khan*/


#include "watchdog.h"
#include <MKL25Z4.h>

//Select 1kHz clock and 1024 cycle time out

void configure_watchdog()    // Configuring COP
{
	SIM->COPC = SIM_COPC_COPT(2) | SIM_COPC_COPCLKS(1)
			| SIM_COPC_COPW(0);
}

// twos complement to feed
void service_watchdog()
{
	SIM->SRVCOP = 0X55;
	SIM->SRVCOP = 0XAA;
}
