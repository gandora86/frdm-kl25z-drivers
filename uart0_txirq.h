/*
 "Implementation of driver for SysTick Timer(As a Iterrupt) on the FRDM-KL25Z development board"  Created by Ashfaq Khan*/

#ifndef UART0_TXIRQ_H
#define UART0_TXIRQ_H
#include <stdint.h>
#include <stdbool.h>

void configure_uart0();
_Bool send_data_to_uart0(uint8_t data);
_Bool receive_data_from_uart0(uint8_t *data);
 void UART0_IRQHandler();
 
#endif
