#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"

#include "led_display.h"

int nvic_setup();

int main(){
	led_setup();
	led_display(GUESS_TOO_LOW);
	while(1){
	}
	
	return 0;
}

int nvic_setup() {
	return 0;
}

