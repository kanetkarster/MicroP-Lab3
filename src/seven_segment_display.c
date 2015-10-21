#include "seven_segment_display.h"

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"

/*!
	Digits which can be dispalyed
	TODO: set equal to bit vector contianing which segments to show
 */
typedef enum {
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE
} DIGIT;

/*!
	Makes system calls for setting up GPIO for 7 segment display
	
	@return 0 on success, else negative
 */
int seven_segment_setup() {
	
	/* Enable Timer */
	// Give power to Timer 3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef tim_init_s;
	// set Prescaler so the transitions are smooth
	tim_init_s.TIM_Prescaler = 40*1000;
	tim_init_s.TIM_CounterMode =  TIM_CounterMode_Up;
	tim_init_s.TIM_ClockDivision = TIM_CKD_DIV1;
	tim_init_s.TIM_Period = 500;
	tim_init_s.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &tim_init_s);
	// enable the clock
	TIM_Cmd(TIM3, ENABLE);
	// needed for IRQ to be called
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	/* Enable IO Pins */
	GPIO_InitTypeDef gpio_init_s;
	GPIO_StructInit(&gpio_init_s);
	// Power to GPIOD
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOD, ENABLE); 
	
	/* set on board LEDs */
	gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; 			// Set as Output
	gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate, allow values to change as fast as they are set
	gpio_init_s.GPIO_OType = GPIO_OType_PP;			// Operating output type (push-pull) for selected pins
	gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// If there is no input, don't pull.
	
	gpio_init_s.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_Init(GPIOD, &gpio_init_s);
	GPIO_WriteBit(GPIOD, GPIO_Pin_12 | GPIO_Pin_13, Bit_RESET);
	
	/* add TIM3_IRQn to the interupts */
	// TODO: maybe we should use a central nvic declaration?
	NVIC_InitTypeDef  nvic_init_s;
	nvic_init_s.NVIC_IRQChannel = TIM3_IRQn;
	nvic_init_s.NVIC_IRQChannelCmd = ENABLE;
	nvic_init_s.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_s.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&nvic_init_s);
	
	return 0;
}
int count = 0;
void TIM3_IRQHandler() {
	TIM_ClearFlag(TIM3, TIM_IT_Update);
	
	// flash led 13
	count = (count + 1) % 10;
	if (count == 9)
	{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	}
}

/*!
	displays a number on the seven segment display
	@param to_display number to display
	
	@return 0 on success, else negative
 */
int display(int to_display) {
	return 0;
}

