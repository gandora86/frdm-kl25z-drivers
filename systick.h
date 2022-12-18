/*
 "Implementation of driver for SysTick Timer(As a Iterrupt) on the FRDM-KL25Z development board"  Created by Ashfaq Khan*/

#ifndef SYSTICK_h
#define SYSTICK_h
#include <stdbool.h>

void configure_systick();
_Bool systick_has_fired();
void Systick_Handler();

#endif







