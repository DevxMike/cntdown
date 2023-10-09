/*
 * animation.cpp
 *
 *  Created on: 8 paź 2023
 *      Author: Michael
 */

#include "APP/animation.h"
#include "APP/display.h"
#include "main.h"
#include "APP/button.h"

enum{
	display_init = 0,
	init_blink,
	init_delay,
	display_time,
	display_settings,
	delay_settings
};

void animation_manager::main(){
	static uint8_t state = display_init;
	static uint32_t timer;
	static uint8_t blink_count = 0;

	auto minutes = time_manager::get_minutes();
	auto seconds = time_manager::get_seconds();

	auto sys_state = system_manager::get_system_state();
	auto long_press = button_manager::is_longer_pressed();

	auto blinking_digit = time_manager::get_currently_set();

	switch(state){
	case display_init:
		timer = HAL_GetTick();
		state = init_blink;
		break;

	case init_blink:
		display_manager::change_content({0, 0, 0, 0});
		if(HAL_GetTick() - timer > 500){
			timer = HAL_GetTick();
			++blink_count;
			state = init_delay;
		}
		break;

	case init_delay:
		display_manager::change_content({10, 10, 10, 10});
		if(HAL_GetTick() - timer > 500){
			timer = HAL_GetTick();
			state = init_blink;
		}

		if(blink_count == 3){
			state = display_time;
		}
		break;

	case display_time:
		display_manager::change_content({minutes / 10, minutes % 10, seconds / 10, seconds % 10});

		if(sys_state == system_state::setting_state && (HAL_GetTick() - timer > 400) && !(long_press)){
			timer = HAL_GetTick();
			state = delay_settings;
		}

		break;

	case delay_settings:
		if(blinking_digit == minutes_are_set){
			display_manager::change_content({10, 10, seconds / 10, seconds % 10});
		}
		else if(blinking_digit == seconds_are_set){
			display_manager::change_content({minutes / 10, minutes % 10, 10, 10});
		}

		if(HAL_GetTick() - timer > 400){
			timer = HAL_GetTick();
			state = display_time;
		}
		break;
	}
}
