#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"

#include "seven_segment_display.h"

int main(){
	SystemInit();
	seven_segment_setup();
	while(1){
	
	}
	
	return 0;
}
