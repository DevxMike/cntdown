/*
 * digital_output.h
 *
 *  Created on: Oct 6, 2023
 *      Author: Michael
 */

#ifndef INC_APP_DIGITAL_OUTPUT_H_
#define INC_APP_DIGITAL_OUTPUT_H_

#include "gpio.h"

class digital_output{
private:
	GPIO_TypeDef* port;
	uint32_t pin;
	bool state;

public:
	digital_output(GPIO_TypeDef* _port, uint32_t _pin):
		port{ _port }, pin{ _pin }{}

	void write(bool o){
		state = o;

		if(state){
			HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
		}
	}

	void toggle(){
		write(!state);
	}
};


#endif /* INC_APP_DIGITAL_OUTPUT_H_ */
