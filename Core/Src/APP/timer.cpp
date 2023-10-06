/*
 * timer.cpp
 *
 *  Created on: Oct 6, 2023
 *      Author: Michael
 */
#include "rtc.h"
#include "APP/timer.h"
#include "APP/display.h"

void time_manager::main(){
	if(sync){
		sync = false;
		seconds = (seconds + 1) % 60;

		if(seconds == 0){
			minutes = (minutes + 1) % 60;
		}

		display_manager::change_content({minutes / 10, minutes % 10, seconds / 10, seconds % 10});
	}
}
void time_manager::alarm_handler(){
	++time_manager::seconds_elapsed;
	time_manager::sync = true;
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
	time_manager::alarm_handler();
}
