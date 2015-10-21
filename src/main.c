#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"

#include "seven_segment_display.h"

int main(){
	// SystemInit();
	seven_segment_setup();
	while(1){
			int timerValue = TIM_GetCounter(TIM3);
			if (timerValue == 400)
					GPIO_SetBits(GPIOD, GPIO_Pin_12);
			else if (timerValue == 500)
					GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	}
	
	return 0;
}
