#include "keypad.h"
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
/*!
	Makes system calls for setting up GPIO for keypad
	
	@return 0 on success, else negative
 */
 //4,5,7,8, 11,12,13,14
int keypad_setup() {
	//set variables
	GPIO_InitTypeDef gpio_init_s;
	EXTI_InitTypeDef exti_init_s;
	NVIC_InitTypeDef nvic_init_s;
	
	//enable clock for GPIOB
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//enable clock for SYSCFG
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	//set pin as input
	gpio_init_s.GPIO_Mode = GPIO_Mode_IN;
	gpio_init_s.GPIO_OType = GPIO_OType_PP;
	gpio_init_s.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | 
												 GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	gpio_init_s.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &gpio_init_s);
	
	//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource
	
	return -1;
}

/*!
	Get's a guess from user
	@param *guess what the user guessed
	@return 0 on success, else negative
 */
int get_input(int* guess) {
	return 0;
}
