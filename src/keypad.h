// keypad.h - getting user input from keypad

#ifndef __INCLUDE_KEYPAD_H__
#define __INCLUDE_KEYPAD_H__

/*!
	Makes system calls for setting up GPIO for keypad
	
	@return 0 on success, else negative
 */
int keypad_setup(void);

/*!
	Get's a guess from user
	@param *guess what the user guessed
	@return 0 on success, else negative
 */
int get_input(int* guess);

#endif // __INCLUDE_KEYPAD_H__
