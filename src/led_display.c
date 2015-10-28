#include "stm32f4xx_conf.h"
#include "led_display.h"

#define GPIO_LED GPIOD

/*!
	Makes system calls for setting up on board LEDs
	
	@return 0 on success, else negative
 */
int led_setup() {
	GPIO_InitTypeDef gpio_init_s; // Structure to initilize definitions of GPIO
	GPIO_StructInit(&gpio_init_s); // Fills each GPIO_InitStruct member with its default value

	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOD, ENABLE); // Provides power for LEDs

	gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; 			// Set as Output
	gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate, allow values to change as fast as they are set
	gpio_init_s.GPIO_OType = GPIO_OType_PP;			// Operating output type (push-pull) for selected pins
	gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// If there is no input, don't pull.

	gpio_init_s.GPIO_Pin = GUESS_TOO_LOW | GUESS_TOO_HIGH | 
												 GUESS_WIN | GUESS_LOSS; // select the 4 GPIO Pins for LEDs
	GPIO_Init(GPIO_LED, &gpio_init_s); 						// Initializes the  LEDs
	
	return 0;
}

/*!
	Shows LED related to status of user input
 */
void led_display(GUESS_STATUS guess) {
	GPIO_ResetBits(GPIO_LED, GUESS_ALL);
	GPIO_SetBits(GPIO_LED, guess);
};

