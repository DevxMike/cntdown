/*
 * timer.cpp
 *
 *  Created on: Oct 6, 2023
 *      Author: Michael
 */
#include "rtc.h"
#include "APP/timer.h"
#include "APP/display.h"
#include "APP/system.h"

void time_manager::main(){
	static uint32_t timer;

	auto sys_state = system_manager::get_system_state();

	switch(sys_state){
	case system_state::counting_state:
		if(timer_not_set() && (HAL_GetTick() - timer >= 1000)){
//			sync = false;

//			display_manager::change_content({2, 1, 3, 7});
			system_manager::RST_Callback();
		}
		else if(!timer_not_set()){
			if(HAL_GetTick() - timer >= 1000){
//				sync = false;
				timer = HAL_GetTick();

				if(seconds != 0){
					--seconds;
				}
				else{
					if(minutes != 0){
						--minutes;
						seconds = 59;
					}

				}
			}
		}
		break;

	default: sync = false; break;
	}
}

void time_manager::increment_handler(){
	switch(currently_set){
	case minutes_are_set:
		increment_minutes();
	break;

	case seconds_are_set:
		increment_seconds();
	break;
	}
}

void time_manager::decrement_handler() {
	switch(currently_set){
	case minutes_are_set:
		decrement_minutes();
	break;

	case seconds_are_set:
		decrement_seconds();
	break;
	}
}

void time_manager::next_handler(){
	currently_set = (currently_set + 1) % 2;
}

void time_manager::prev_handler(){
	if(currently_set == 0){
		currently_set = 1;
	}
	else{
		--currently_set;
	}
}

void time_manager::alarm_handler(){
	++time_manager::seconds_elapsed;
//	time_manager::sync = true;
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
	time_manager::alarm_handler();
}
