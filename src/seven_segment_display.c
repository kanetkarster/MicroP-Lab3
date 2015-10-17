#include "seven_segment_display.h"

/*!
	Digits which can be dispalyed
	TODO: set equal to bit vector contianing which segments to show
 */
typedef enum {
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE
} DIGIT;

/*!
	Makes system calls for setting up GPIO for 7 segment display
	
	@return 0 on success, else negative
 */
int seven_segment_setup() {
	return 0;
}

/*!
	displays a number on the seven segment display
	@param to_display number to display
	
	@return 0 on success, else negative
 */
int display(int to_display) {
	return 0;
}

