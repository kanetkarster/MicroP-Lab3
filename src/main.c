#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"

#include "led_display.h"
#include "seven_segment_display.h"

int main(){
	SystemInit();
	led_setup();
	seven_segment_setup();
	led_display(GUESS_TOO_LOW);
	display(6.23);
	
	while(1){
	
	}
	
	return 0;
}
