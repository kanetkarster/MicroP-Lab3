#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"

#include "led_display.h"
#include "seven_segment_display.h"
#include "accelerometer.h"

#define NUM_TRIES 3
#define GUESS_ERROR 5
void game_loop(void);
int get_input(void);

int main(){
	accelerometer_setup(ACCELEROMETER_LIS3DSH);
	led_setup();
	seven_segment_setup();
	
	led_display(GUESS_TOO_HIGH);
	//display(32.8);
	while(1){
		game_loop();
	}
	
	return 0;
}

void game_loop() {
	int guess;
	float anglef;
	int anglei;
	GUESS_STATUS stat;
	for (int i = 0; i < NUM_TRIES; i++) {
		//while(!keypadready); // busy wait for keypad value
		printf("enter a value!\n");
		scanf("%d", &guess);
		get_angle(&anglef);
		display(anglef);
		anglei = (int) anglef;
		int err = guess - GUESS_ERROR;
		if ((-5 < err) && (err < 5)) {
			stat = GUESS_WIN;
			break;
		}
		else if (guess < anglei) {
			stat = GUESS_TOO_LOW;
		}
		else {
			stat = GUESS_TOO_HIGH;
		}
		led_display(stat);
	}
	if (stat != GUESS_WIN) {
		led_display(GUESS_LOSS);
	}
}
