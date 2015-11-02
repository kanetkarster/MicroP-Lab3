#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include "keypad.h"
#include "led_display.h"
#include "seven_segment_display.h"
#include "accelerometer.h"

#define NUM_TRIES 3
#define GUESS_ERROR 4
void game_loop(void);

int main(){
	//set up components
	accelerometer_setup(ACCELEROMETER_LIS3DSH);
	keypad_setup();
	led_setup();
	seven_segment_setup();
	
	// give the accelerometer time to setup
	while (wait < 100);
	display(119);
	//wait for enter key
	while(!keypadready);
	keypadready = 0;
	//start game
	game_loop();
	while(1);
	return 0;
}

void game_loop() {
	int guess;
	float anglef;
	int anglei;
	GUESS_STATUS stat;

	get_angle(&anglef);
	anglei = (int) anglef;
	printf("angle = %f\n", anglef);
	for (int i = 0; i < NUM_TRIES; i++) {

		while(!keypadready); 	// busy wait for keypad value
		get_input(&guess);	//get guess
		printf("guess: %d\n", guess);
		int err = anglef - guess;
		printf("err: %d\n", err);
		//check guess and update LED to display
		if ((-GUESS_ERROR < err) && (err < GUESS_ERROR)) {
			led_display(GUESS_WIN);
			display(anglef);
			return;
		}
		else if (guess < anglei) {
			stat = GUESS_TOO_LOW;
		}
		else {
			stat = GUESS_TOO_HIGH;
		}
		led_display(stat);
	}
	//display final game info if game is over
	led_display(GUESS_LOSS);
	display(anglef);
}
