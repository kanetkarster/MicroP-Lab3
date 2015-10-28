#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"

#include "led_display.h"
#include "seven_segment_display.h"
#include "accelerometer.h"


int main(){
	SystemInit();
	led_setup();
	seven_segment_setup();
	accelerometer_setup(ACCELEROMETER_LIS3DSH);
	
	led_display(GUESS_TOO_HIGH);
	display(32.8);
	float f;
	while(1){
		while (wait % 10 != 0);
		get_angle(&f);
		display(f);
	}
	
	return 0;
}
