/*
 * timer.h
 *
 *  Created on: Oct 6, 2023
 *      Author: Michael
 */

#ifndef INC_APP_TIMER_H_
#define INC_APP_TIMER_H_


#include "APP/display.h"


class time_manager{
private:
	static bool sync;
	static uint32_t seconds_elapsed;
	static uint8_t minutes;
	static uint8_t seconds;

public:
	static void main();
	static void alarm_handler();
};


#endif /* INC_APP_TIMER_H_ */
