/*
 * display.cpp
 *
 *  Created on: 6 paź 2023
 *      Author: Michael
 */

#include "APP/display.h"
#include <algorithm>
#include "spi.h"
#include "APP/digital_output.h"

enum{
	master_reset = 0,
	output_enable,
	latch
};

static std::array<digital_output, 3> spi_signals{
	digital_output{ MASTER_RESET_GPIO_Port, MASTER_RESET_Pin },
	digital_output{ OUTPUT_ENABLE_GPIO_Port, OUTPUT_ENABLE_Pin },
	digital_output{ LATCH_GPIO_Port, LATCH_Pin }
};

void copy(std::array<uint8_t, display_size> input, uint8_t* output){
	for(uint8_t i = 0; i < display_size; ++i){
		output[i] = input.at(i);
	}
}

void display_manager::main(){
	static uint8_t state = 0;
	static uint8_t hex_buffer[display_size];
	static uint32_t timer;

	switch(state){
	case init:
		change_content({ 0x00, 0x00, 0x00, 0x00});
		copy(displayed_codes, hex_buffer);

		spi_signals.at(master_reset).write(true);
		spi_signals.at(output_enable).write(true);
		spi_signals.at(latch).write(false);

		HAL_SPI_Transmit_IT(&hspi1, hex_buffer, display_size);

		state = wait_for_interrupt;

		break;

	case wait_for_interrupt:
		if(interrupt_flag){
			spi_signals.at(latch).write(true);

			interrupt_flag = false;
			timer = HAL_GetTick();
			state = wait_for_flipflop;
		}
		break;

	case wait_for_flipflop:
		if(HAL_GetTick() - timer >= 1){
			spi_signals.at(latch).write(false);
			spi_signals.at(output_enable).write(false);

			timer = HAL_GetTick();
			state = change_content_in_regs;
		}
		break;

	case change_content_in_regs:
		if(HAL_GetTick() - timer >= 10){
			copy(displayed_codes, hex_buffer);

			HAL_SPI_Transmit_IT(&hspi1, hex_buffer, display_size);

			state = wait_for_interrupt;
		}
		break;
	}
}

void display_manager::change_content(std::initializer_list<uint8_t> digits){
	auto code_iter = displayed_codes.begin();

	for(auto x : digits){
		*code_iter = hex_codes.at(x);
		code_iter++;
	}
}

void display_manager::interrupt_handler(){
	interrupt_flag = true;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
	display_manager::interrupt_handler();
}
