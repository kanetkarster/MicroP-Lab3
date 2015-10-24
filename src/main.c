#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include "keypad.h"
int nvic_setup(void);

int main(){
	SystemInit();
	keypad_setup();
	while(1){
	}
	
	return 0;
}

int nvic_setup() {
	
	return 0;
}

