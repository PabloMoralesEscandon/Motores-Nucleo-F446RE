#include "motor.h"

Motor init_motor(TIM_TypeDef* timer, TIM_HandleTypeDef timer_handle, Channel channel,  GPIO_TypeDef* in1, GPIO_TypeDef* in2, uint16_t in1_pin, uint16_t in2_pin, uint16_t prescaler, uint16_t arr){
	Motor motor;
	motor.timer = timer;
	motor.timer_handle = timer_handle;
	motor.channel = channel;
	motor.in1 = in1;
	motor.in2 = in2;
	motor.in1_pin = in1_pin;
	motor.in2_pin = in2_pin;
	motor.prescaler = prescaler;
	motor.arr = arr;

	return motor;
}

void set_speed(Motor target, double speed){

	//Check if it will be going forwar or backward
	if(speed<0){
		HAL_GPIO_WritePin(target.in1, target.in1_pin, 1);
		HAL_GPIO_WritePin(target.in2, target.in2_pin, 0);
		speed = -speed;
	} else if (speed>0){
		HAL_GPIO_WritePin(target.in1, target.in1_pin, 0);
		HAL_GPIO_WritePin(target.in2, target.in2_pin, 1);
	} else{
		HAL_GPIO_WritePin(target.in1, target.in1_pin, 0);
		HAL_GPIO_WritePin(target.in2, target.in2_pin, 0);
	}
	speed = MAX(MIN(speed, 0.0), 1.0); // Set speed between 0 and 1
	uint16_t ccr = (target.arr +1)*speed;
	uint32_t channel;
	switch(target.channel){
		case CH1:
			target.timer->CCR1 = ccr;
			channel = TIM_CHANNEL_1;
			break;
		case CH2:
			target.timer->CCR2 = ccr;
			channel = TIM_CHANNEL_2;
			break;
		case CH3:
			target.timer->CCR3 = ccr;
			channel = TIM_CHANNEL_3;
			break;
		case CH4:
			target.timer->CCR4 = ccr;
			channel = TIM_CHANNEL_4;
			break;
		default:
			break;
	}
	HAL_TIM_PWM_Start(&(target.timer_handle), channel);
}
