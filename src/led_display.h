// led_dispaly.h - displays high, low, success or loss

/*!
	Contains possible results from a user guess
	Each index coresponds to a particular LED
 */
typedef enum {
	TOO_LOW,
	TOO_HIGH,
	WIN,
	LOSS
} GUESS_STATUS;

/*!
	Makes system calls for setting up on board LEDs
	
	@return 0 on success, else negative
 */
int led_setup();

/*!
	Shows LED related to status of user input
 */
void led_display(GUESS_STATUS guess);
