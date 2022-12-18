/*Driver for all colors on the RGBLED */
/* Ashfaq Khan */
#include <rgbled.h>
#include <MKL25Z4.h>
#define RED_LED_LOC 18 // port b
#define GREEN_LED_LOC 19 // port b
#define BLUE_LED_LOC 1 // port d

void set_rgbled_color_to(RGBLED_COLOR color)
{
	switch(color)
	{
		case RGBLED_COLOR_RED:
		turn_on_red_led();
		turn_off_green_led();
		turn_off_blue_led();
		break;
		case RGBLED_COLOR_GREEN:
		turn_off_red_led();
		turn_on_green_led();
		turn_off_blue_led();
		break;
		case RGBLED_COLOR_BLUE:
		turn_off_red_led();
		turn_off_green_led();
		turn_on_blue_led();
		break;
		case RGBLED_COLOR_CYAN:
		turn_off_red_led();
		turn_on_green_led();
		turn_on_blue_led();
		break;
		case RGBLED_COLOR_MAGENTA:
		turn_on_red_led();
		turn_off_green_led();
		turn_on_blue_led();
		break;
		case RGBLED_COLOR_YELLOW:
		turn_on_red_led();
		turn_on_green_led();
		turn_off_blue_led();
		break;
		case RGBLED_COLOR_WHITE:
		turn_on_red_led();
		turn_on_green_led();
		turn_on_blue_led();
		break;
		case RGBLED_COLOR_BLACK:
		default:
		turn_off_red_led();
		turn_off_green_led();
		turn_off_blue_led();
		break;
	}

}
void configure_rgb_led()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	
	PORTB->PCR[RED_LED_LOC] =
	   (PORTB->PCR[RED_LED_LOC] & ~(PORT_PCR_MUX_MASK | PORT_PCR_PE_MASK)) 
	   | PORT_PCR_IRQC_MASK | PORT_PCR_MUX(1);
	PTB->PDDR |= (1<<RED_LED_LOC);
	
	PORTB->PCR[GREEN_LED_LOC] =
	   (PORTB->PCR[GREEN_LED_LOC] & ~(PORT_PCR_MUX_MASK | PORT_PCR_PE_MASK)) 
	   | PORT_PCR_IRQC_MASK | PORT_PCR_MUX(1);
	PTB->PDDR |= (1<<GREEN_LED_LOC);
	
	PORTD->PCR[BLUE_LED_LOC] =
	   (PORTB->PCR[BLUE_LED_LOC] & ~(PORT_PCR_MUX_MASK | PORT_PCR_PE_MASK)) 
	   | PORT_PCR_IRQC_MASK | PORT_PCR_MUX(1);
	PTD->PDDR |= (1<<BLUE_LED_LOC);
	turn_off_red_led();
	turn_off_green_led();
	turn_off_blue_led();
}
void turn_on_red_led()
{
	PTB->PCOR |= (1<<RED_LED_LOC);
}
void turn_off_red_led()
{
	PTB->PSOR |= (1<<RED_LED_LOC);
}
void toggle_redled()
{
	PTB->PTOR |= (1<<RED_LED_LOC);
}
void turn_on_green_led()
{
	PTB->PCOR |= (1<<GREEN_LED_LOC);
}
void turn_off_green_led()
{
	PTB->PSOR |= (1<<GREEN_LED_LOC);
}
void toggle_greenled()
{
	PTB->PTOR |= (1<<GREEN_LED_LOC);
}
void turn_on_blue_led()
{
	PTD->PCOR |= (1<<BLUE_LED_LOC);
}
void turn_off_blue_led()
{
	PTD->PSOR |= (1<<BLUE_LED_LOC);
}
void toggle_blueled()
{
	PTD->PTOR |= (1<<BLUE_LED_LOC);
}
