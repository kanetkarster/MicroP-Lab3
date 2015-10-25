#include "seven_segment_display.h"

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
		
#define IO_SEVEN_SEGMENT GPIOB

/*!
	Which pin (on IO_SEVEN_SEGMENT) is used for each digit.
 */
typedef enum {
	DIGIT_FIRST = GPIO_Pin_0,  // 1
	DIGIT_SECOND = GPIO_Pin_1, // 2
	DIGIT_THIRD = GPIO_Pin_2,  // 6
	ALL_DIGITS = DIGIT_FIRST | DIGIT_SECOND | DIGIT_THIRD,
} DIGIT;

/*!
	Which pin (on IO_SEVEN_SEGMENT) is used for each segment.
*/
typedef enum {
	SEGMENT_A = GPIO_Pin_4,	 // 14
	SEGMENT_B = GPIO_Pin_5,  // 16
	SEGMENT_C = GPIO_Pin_7,  // 13
	SEGMENT_D = GPIO_Pin_8,  // 3
	SEGMENT_E = GPIO_Pin_11, // 5
	SEGMENT_F = GPIO_Pin_12, // 11
	SEGMENT_G = GPIO_Pin_13, // 15
	SEGMENT_H = GPIO_Pin_14,	// Period
	ALL_SEGS = SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G
} SEGMENT;

/*!
	Digits which can be dispalyed
	TODO: set equal to bit vector contianing which segments to show
 */
typedef enum {
	NUM_ZERO = ALL_SEGS ^ SEGMENT_G,
	NUM_ONE = SEGMENT_B | SEGMENT_C,
	NUM_TWO = ALL_SEGS ^ SEGMENT_C ^ SEGMENT_F,
	NUM_THREE = ALL_SEGS ^ SEGMENT_E ^ SEGMENT_F,
	NUM_FOUR = SEGMENT_B | SEGMENT_C | SEGMENT_G |SEGMENT_F,
	NUM_FIVE= ALL_SEGS ^ SEGMENT_B ^ SEGMENT_E,
	NUM_SIX = ALL_SEGS ^ SEGMENT_B,
	NUM_SEVEN = SEGMENT_A | SEGMENT_B | SEGMENT_C,
	NUM_EIGHT = ALL_SEGS,
	NUM_NINE = ALL_SEGS ^ SEGMENT_E
} NUMBER;

NUMBER toSegments[10] = 
	{
		NUM_ZERO,
    NUM_ONE,
    NUM_TWO,
		NUM_THREE,
    NUM_FOUR,
		NUM_FIVE,
		NUM_SIX,
		NUM_SEVEN,
		NUM_EIGHT,
		NUM_NINE
	};
	
DIGIT INDEX[3] = {
	DIGIT_FIRST,
	DIGIT_SECOND,
	DIGIT_THIRD,
};

NUMBER num[3];

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
	tim_init_s.TIM_Prescaler = 400;
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
	//GPIO_StructInit(&gpio_init_s);
	// Power to GPIOB
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE);
	
	/* set on board LEDs */
	gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; 			// Set as Output
	gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate, allow values to change as fast as they are set
	gpio_init_s.GPIO_OType = GPIO_OType_PP;			// Operating output type (push-pull) for selected pins
	gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// If there is no input, don't pull.
	
	gpio_init_s.GPIO_Pin = DIGIT_FIRST | DIGIT_SECOND | DIGIT_THIRD |
												SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D |
												SEGMENT_E | SEGMENT_F | SEGMENT_G | SEGMENT_H;
	GPIO_Init(GPIOB, &gpio_init_s);
	GPIO_SetBits(GPIOB, DIGIT_FIRST | DIGIT_SECOND | DIGIT_THIRD);
	//GPIO_WriteBit(GPIOB, GPIO_Pin_0 | GPIO_Pin_13, Bit_SET);
	/* add TIM3_IRQn to the interupts */
	// TODO: maybe we should use a central nvic declaration?
	NVIC_InitTypeDef  nvic_init_s;
	nvic_init_s.NVIC_IRQChannel = TIM3_IRQn;
	nvic_init_s.NVIC_IRQChannelCmd = ENABLE;
	nvic_init_s.NVIC_IRQChannelPreemptionPriority = 1;
	nvic_init_s.NVIC_IRQChannelSubPriority = 1;
	
	num[0] = toSegments[4];
	num[1] = toSegments[2];
	num[2] = toSegments[0];
	
	NVIC_Init(&nvic_init_s);
	
	return 0;
}
int count = 0;
void TIM3_IRQHandler() {
	TIM_ClearFlag(TIM3, TIM_IT_Update);
	
	// Select a Digit
	GPIO_SetBits(GPIOB, ALL_DIGITS);
	GPIO_ResetBits(GPIOB, INDEX[count % 3]);
	
	// Display a Number
	GPIO_ResetBits(GPIOB, ALL_SEGS);
	GPIO_SetBits(GPIOB, num[count % 3]);
	
	count++;
}

/*!
	displays a number on the seven segment display
	@param to_display number to display
	
	@return 0 on success, else negative
 */
int display(int to_display) {
	return 0;
}

