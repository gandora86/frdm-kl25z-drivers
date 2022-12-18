/*
"Implementation of driver functions for uart on the FRDM-KL25Z development board" Created by Ashfaq Khan*/
#include <uart0_txirq.h>
#include <MKL25Z4.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef TXBUFSIZE
#define TXBUFSIZE 256 //must be power of 2
#endif
#define TXBUF_IS_POWER_OF_2(N) (((N)&((N)-1)) == 0)
#if !TXBUF_IS_POWER_OF_2(TXBUFSIZE)
#error TX_BUF_SIZE must be a power of 2
#endif

#ifndef RXBUFSIZE
#define RXBUFSIZE 256 //must be power of 2
#endif
#define RXBUF_IS_POWER_OF_2(N) (((N)&((N)-1)) == 0)
#if !RXBUF_IS_POWER_OF_2(TXBUFSIZE)
#error RX_BUF_SIZE must be a power of 2
#endif

static volatile uint32_t head_tx, tail_tx;
static volatile uint8_t tx_buf[TXBUFSIZE];
static volatile uint32_t head_rx, tail_rx;
static volatile uint8_t rx_buf[RXBUFSIZE];
#define next_head_tx() ((head_tx+1) & (TXBUFSIZE-1))
#define next_tail_tx() ((tail_tx+1) & (TXBUFSIZE-1))
#define next_head_rx() ((head_rx+1) & (RXBUFSIZE-1))
#define next_tail_rx() ((tail_rx+1) & (RXBUFSIZE-1))
static _Bool txbuf_empty(){
	return head_tx == tail_tx;
}
static _Bool txbuf_full(){
	return next_head_tx() == tail_tx;
}
static void txbuf_enqueue(uint8_t data){
	uint32_t mask = __get_PRIMASK();
	__disable_irq();
	tx_buf[head_tx] = data;
	head_tx = next_head_tx();
	__set_PRIMASK(mask);
}
static uint8_t txbuf_dequeue(){
	uint32_t mask = __get_PRIMASK();
	__disable_irq();
	uint8_t retval = tx_buf[tail_tx];
	tail_tx = next_tail_tx();
	__set_PRIMASK(mask);
	return retval;
}

static _Bool rxbuf_empty(){
	return head_rx == tail_rx;
}
static _Bool rxbuf_full(){
	return next_head_rx() == tail_rx;
}
static void rxbuf_enqueue(uint8_t data){
	uint32_t mask = __get_PRIMASK();
	__disable_irq();
	rx_buf[head_rx] = data;
	head_rx = next_head_rx();
	__set_PRIMASK(mask);
}
static uint8_t rxbuf_dequeue(){
	uint32_t mask = __get_PRIMASK();
	__disable_irq();
	uint8_t retval = rx_buf[tail_rx];
	tail_rx = next_tail_rx();
	__set_PRIMASK(mask);
	return retval;
}
void configure_uart0()    // Configuring uart
{
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[1] = PORT_PCR_MUX(2);
	PORTA->PCR[2] = PORT_PCR_MUX(2);
	SIM->SOPT2 |= (SIM_SOPT2_UART0SRC(1) | SIM_SOPT2_PLLFLLSEL(1));
	UART0-> BDH = 0;
	UART0-> BDL = 25; //115.2KBd
	UART0->C1=0;
	UART0->C2=UART0_C2_TE_MASK | UART0_C2_RE_MASK;
	
}
// change to use interrupts
_Bool send_data_to_uart0(uint8_t data)
{
	if(txbuf_full()) { //Buffer full
		return false;
	}
	txbuf_enqueue(data);
	UART0->C2 |= UART_C2_TIE_MASK;  // Turn on Tx interrupts
	return true;
}
_Bool receive_data_from_uart0(uint8_t *data)
{
	if(rxbuf_empty()){
		return false;
	}
	*data=rxbuf_dequeue();
	UART0->C2 |= UART_C2_RIE_MASK;           // Turn on Rx interrupt
	return true;
}

_Bool print_str(char* printer)
{
	int i;
	for (i = 0; printer[i] != '\0'; ++i){
		send_data_to_uart0(printer[i]);
	}
	
	return true;
}



void UART0_IRQHandler(void)
{
    int status;
    
    status = UART0->S1;
    
    // If transmit data register emtpy, and data in the transmit buffer,
    // send it.  If it leaves the buffer empty, disable the transmit interrupt.
    if ((status & UART0_S1_TDRE_MASK) && !txbuf_empty()) {
        UART0->D = txbuf_dequeue();
        if(txbuf_empty())
            UART0->C2 &= ~UART_C2_TIE_MASK;
    }
    
    // If there is received data, read it into the receive buffer.  If the
    // buffer is full, disable the receive interrupt.
    if ((status & UART_S1_RDRF_MASK) && !rxbuf_full()) {
        rxbuf_enqueue(UART0->D);
        if(rxbuf_full())
            UART0->C2 &= ~UART_C2_RIE_MASK;
    }
}
