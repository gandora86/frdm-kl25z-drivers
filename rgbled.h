#ifndef RGBLED_H
#define RGBLED_H

typedef enum RGBLED_COLORS
{
	RGBLED_COLOR_BLACK = 0b000,
	RGBLED_COLOR_RED = 0b100,
	RGBLED_COLOR_GREEN = 0b010,
	RGBLED_COLOR_BLUE = 0b001,
	RGBLED_COLOR_CYAN = 0b011,
	RGBLED_COLOR_MAGENTA = 0b101,
	RGBLED_COLOR_YELLOW = 0b110,
	RGBLED_COLOR_WHITE = 0b111,
} RGBLED_COLOR;

void set_rgbled_color_to(RGBLED_COLOR color);
void configure_rgb_led();

void turn_on_red_led();
void turn_off_red_led();
void toggle_redled();

void turn_on_green_led();
void turn_off_green_led();
void toggle_greenled();

void turn_on_blue_led();
void turn_off_blue_led();
void toggle_blueled();

#endif
