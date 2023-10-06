#ifndef button_h
#define button_h

#include <array>
#include <memory>
#include "gpio.h"

constexpr uint8_t interface_size = 7;

using cback_type = void(*)();

enum class button_state{
	waiting_for_push,
	debouncing,
	waiting_for_release,
	waiting_longer_press
};

class button {
private:
	button_state state;
	uint32_t tick_holder;
	GPIO_TypeDef* port;
	uint32_t pin;

public:
	button(GPIO_TypeDef* _port, uint32_t _pin);
	bool read_button();
	button_state get_state() { return state; };
	void set_state(button_state s) { state = s; };
	uint32_t get_ticks() { return tick_holder; }
	void set_ticks(uint32_t t) { tick_holder = t; }
	virtual void update_button() = 0;
};

class push_button : public button {
private:
	cback_type on_btn_pressed;
protected:
	void callback() { on_btn_pressed(); }
public:
	push_button(GPIO_TypeDef* _port, uint32_t _pin, cback_type cback) : button(_port, _pin), on_btn_pressed{ cback } {}
	virtual void update_button();
};

class hold_push_button : public push_button {
public:
	hold_push_button(GPIO_TypeDef* _port, uint32_t _pin, cback_type cback) : push_button(_port, _pin, cback) {}
	virtual void update_button();
};

class button_manager {
private:
	static std::array<std::shared_ptr<push_button>, interface_size> keyboard;

public:
	static void main();
};

#endif
