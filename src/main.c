#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include "accelerometer.h"

int main(){
	
	accelerometer_setup(ACCELEROMETER_LIS3DSH);
	while(1){

	}
	
	return 0;
}

int nvic_setup() {
	
	return 0;
}

