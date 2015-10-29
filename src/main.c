#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include "keypad.h"
#include "led_display.h"
#include "seven_segment_display.h"
#include "accelerometer.h"


int main(){
	accelerometer_setup(ACCELEROMETER_LIS3DSH);
	keypad_setup();
	led_setup();
	seven_segment_setup();
	
	led_display(GUESS_TOO_HIGH);
	display(32.8);
	float f;
	while(1){
	}
	
	return 0;
}
