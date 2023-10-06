/*
 * display.h
 *
 *  Created on: 6 paź 2023
 *      Author: Michael
 */

#ifndef INC_APP_DISPLAY_H_
#define INC_APP_DISPLAY_H_

#include "APP/system.h"
#include <array>
#include <cstdint>

constexpr uint8_t hex_codes_count = 10;
constexpr uint8_t display_size = 4;

enum display_states{
	init = 0,
	change_content_in_regs,
	wait_for_interrupt,
	wait_for_flipflop,
	blink_first,
	blink_second
};

class display_manager{
private:
	static const std::array<uint8_t, hex_codes_count> hex_codes;
	static std::array<uint8_t, display_size> displayed_codes;
	static bool interrupt_flag;

public:
	static void interrupt_handler();
	static void main();
	static void change_content(std::initializer_list<uint8_t> digits);
};



#endif /* INC_APP_DISPLAY_H_ */
