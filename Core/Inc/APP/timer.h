/*
 * timer.h
 *
 *  Created on: Oct 6, 2023
 *      Author: Michael
 */

#ifndef INC_APP_TIMER_H_
#define INC_APP_TIMER_H_


#include "APP/display.h"

enum{
	minutes_are_set = 0,
	seconds_are_set = 1
};

class time_manager{
private:
	static bool sync;

	static uint32_t seconds_elapsed;
	static uint8_t minutes;
	static uint8_t seconds;
	static uint8_t currently_set;

	static void increment_minutes() { minutes = (minutes + 1) % 100; }
	static void decrement_minutes() { minutes = (minutes == 0? 99 : (minutes - 1)); }
	static void increment_seconds() { seconds = (seconds + 1) % 60; }
	static void decrement_seconds() { seconds = (seconds == 0? 59 : (seconds - 1)); }

public:
	static void main();
	static void alarm_handler();

	static void increment_handler();
	static void decrement_handler();

	static void next_handler();
	static void prev_handler();

	static void reset_handler(){ minutes =3; seconds = 0; }

	static bool timer_not_set() { return (minutes == 0) && (seconds == 0); }

	static uint8_t get_minutes() { return minutes; }
	static uint8_t get_seconds() { return seconds; }

	static void init_settings() { currently_set = minutes_are_set; }

	static uint8_t get_currently_set() { return currently_set; }
};


#endif /* INC_APP_TIMER_H_ */
