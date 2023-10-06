#include "APP/button.h"

button::button(GPIO_TypeDef* _port, uint32_t _pin) : state{ button_state::waiting_for_push }, tick_holder{ 0 },
	port{ _port }, pin{ _pin }
{
	//TBD
}

bool button::read_button() {
	bool state = HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET? false : true;

	return state;
}

void push_button::update_button() {
	auto state = get_state();

	switch (state) {
	case button_state::waiting_for_push:
		if (read_button()) {
			set_ticks(HAL_GetTick());
			state = button_state::debouncing;
		}
		break;

	case button_state::debouncing:
		if (HAL_GetTick() - get_ticks() > 30) {
			callback();
			state = button_state::waiting_for_release;
		}
		break;

	case button_state::waiting_for_release:
		if (!read_button()) {
			state = button_state::waiting_for_push;
		}
		break;
	}
	set_state(state);
	// std::cout << "Push button update\n";
}

void hold_push_button::update_button() {
	auto state = get_state();

	switch (state) {
	case button_state::waiting_for_push:
		if (read_button()) {
			set_ticks(HAL_GetTick());
			state = button_state::debouncing;
		}
		break;

	case button_state::debouncing:
		if (HAL_GetTick() - get_ticks() > 30) {
			callback();
			set_ticks(HAL_GetTick());
			state = button_state::waiting_longer_press;
		}
		break;

	case button_state::waiting_longer_press:
		if (read_button() && (HAL_GetTick() - get_ticks() > 1500)) { // and ticks greater than
			set_ticks(HAL_GetTick());
			state = button_state::waiting_for_release;
		}
		else if (!read_button()) {
			state = button_state::waiting_for_push;
		}
		break;

	case button_state::waiting_for_release:
		if(!read_button()){
			state = button_state::waiting_for_push;
		}
		else if(read_button() && (HAL_GetTick() - get_ticks() > 100)){
			callback();
			set_ticks(HAL_GetTick());
		}

		break;
	}

	set_state(state);
}

void button_manager::main() {
	for (auto& x : keyboard) {
		x->update_button();
	}
}
