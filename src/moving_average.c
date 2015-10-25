#include "moving_average.h"

#define BUFF_SIZE 20

typedef struct {
	float buffer[BUFF_SIZE];
	int replace;
	float avg;
	float sum;
} FilterBuffer;

FilterBuffer filter;

/*!
	adds a value to the filter
	@param f value to be added to buffer
 */
int add_value(float f) {
	filter.sum -= filter.buffer[filter.replace % BUFF_SIZE];
	filter.sum += (filter.buffer[filter.replace % BUFF_SIZE] = f);
	filter.avg = filter.replace++ < BUFF_SIZE 
											? filter.sum/filter.replace 
											: filter.sum/BUFF_SIZE;
	return 0;
}

/*!
	@return average value
 */
float get_value(void) {
	return filter.avg;
}
