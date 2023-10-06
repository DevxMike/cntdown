#include "APP/system.h"
#include "APP/digital_output.h"
#include "gpio.h"
#include "APP/display.h"

digital_output setting_led(ACTIVITY_INDICATOR_GPIO_Port, ACTIVITY_INDICATOR_Pin);

void system_manager::main(){
	static system_state old_state = state;
	static bool init_done = false;

	if(!init_done){
		setting_led.write(true);
		init_done = true;
	}

	if(old_state != state){
		switch(state){
		case system_state::reset_state:
			// reset the clock
			break;

		case system_state::counting_state:
			// start the clock
			break;

		case system_state::halt_state:
			setting_led.write(true);
			break;

		case system_state::setting_state:
			setting_led.write(false);
			break;
		}
	}

	old_state = state;
}

void system_manager::INC_Callback() {
	if (state == system_state::setting_state) {
		// increase
	}
}
void system_manager::DEC_Callback() {
	if (state == system_state::setting_state) {
		// decrease
	}
}
void system_manager::TRIG_Callback() {
	if (state == system_state::halt_state) {
		// start
		state = system_state::counting_state;
	}
	else if (state == system_state::counting_state) {
		// stop
		state = system_state::halt_state;
	}
}
void system_manager::SET_Callback() {
	if (state == system_state::halt_state || state == system_state::reset_state) {
		state = system_state::setting_state;
	}
	else if(state == system_state::setting_state){
		state = system_state::halt_state;
	}
}
void system_manager::RST_Callback() {
	switch (state) {
	case system_state::reset_state:
	case system_state::halt_state:
	case system_state::counting_state:
		display_manager::change_content({0x00, 0x00, 0x00, 0x00});

		state = system_state::reset_state;
		break;
	}
}
void system_manager::NEXT_Callback() {
	if (state == system_state::setting_state) {
		// next
	}
}
void system_manager::PREV_Callback() {
	if (state == system_state::setting_state) {
		// prev
	}
}
