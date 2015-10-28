// led_dispaly.h - displays high, low, success or loss
#ifndef __INCLUDE_LED_DISPLAY_
#define __INCLUDE_LED_DISPLAY_
/*!
	Contains possible results from a user guess
	Each index coresponds to a particular LED
 */
typedef enum {
	GUESS_TOO_LOW = GPIO_Pin_13,	// orange
	GUESS_TOO_HIGH = GPIO_Pin_15,	// blue
	GUESS_WIN = GPIO_Pin_12,			// green
	GUESS_LOSS = GPIO_Pin_14,			// red
	GUESS_ALL = GUESS_TOO_LOW | GUESS_TOO_HIGH | GUESS_WIN | GUESS_LOSS
} GUESS_STATUS;

/*!
	Makes system calls for setting up on board LEDs
	
	@return 0 on success, else negative
 */
int led_setup(void);

/*!
	Shows LED related to status of user input
 */
void led_display(GUESS_STATUS guess);

#endif // __INCLUDE_LED_DISPLAY_
