/*
 "Implementation of driver functions for SysTick  timer on the FRDM-KL25Z development board"  Created by Ashfaq Khan*/

#include "systick.h"
#include <MKL25Z4.h>
#include <stdbool.h>
#define SYSTICK_FREQ 1000 // in Hz
#define SYSTICK_TOP (SYS_CLOCK/SYSTICK_FREQ-1)

void configure_systick()
{
	SysTick->LOAD = SYSTICK_TOP;       
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk  |     SysTick_CTRL_CLKSOURCE_Msk;               
}
_Bool systick_has_fired()
{
	return SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk;
}
