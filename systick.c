/*
 "Implementation of driver functions for SysTick  timer on the FRDM-KL25Z development board"  Created by Ashfaq Khan*/

#include "systick.h"
#include <MKL25Z4.h>
#include <stdbool.h>
#define SYSTICK_FREQ 1000 // in Hz
#define SYSTICK_TOP (SYS_CLOCK/SYSTICK_FREQ-1)

static volatile _Bool systick_interrupt_has_occurred = 0;

void configure_systick()
{
	SysTick->LOAD = SYSTICK_TOP;       
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;                 
}
_Bool systick_has_fired()
{
	_Bool retval;
	uint32_t masking_state = __get_PRIMASK();
	__disable_irq();
	
	retval = systick_interrupt_has_occurred;
	systick_interrupt_has_occurred = 0;
	__enable_irq();
	return retval;
}
void Systick_Handler()
{
	systick_interrupt_has_occurred = 1; // automatically clears IRQ flag
} 
