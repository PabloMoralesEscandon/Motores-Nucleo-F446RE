#include "motor.h"

Motor init_motor(TIM_TypeDef* timer, TIM_HandleTypeDef timer_handle, uint32_t channel1, uint32_t channel2, GPIO_TypeDef* en_gpio, uint16_t en_pin, uint16_t prescaler, uint16_t arr){
	Motor motor;
	motor.timer = timer;
	motor.timer_handle = timer_handle;
	motor.channel1 = channel1;
	motor.channel2 = channel2;
	motor.en_gpio = en_gpio;
	motor.en_pin = en_pin;
	motor.prescaler = prescaler;
	motor.arr = arr;
	HAL_TIM_PWM_Start(&(motor.timer_handle), channel1);
	HAL_TIM_PWM_Start(&(motor.timer_handle), channel2);

	return motor;
}

void set_speed(Motor target, double speed){

	//Check if it will be going forwar or backward
	uint16_t ccr1 = 0;
	uint16_t ccr2 = 0;
	speed = MAX(MIN(speed, 0.0), 1.0); // Set speed between 0 and 1
	if(speed<0.5){
		HAL_GPIO_WritePin(target.en_gpio, target.en_pin, 1);
		ccr1=(target.arr +1)*(0.5 - speed)*2;
	} else if (speed>0.5){
		HAL_GPIO_WritePin(target.en_gpio, target.en_pin, 1);
		ccr2=(target.arr +1)*(speed-0.5)*2;
	} else{
		HAL_GPIO_WritePin(target.en_gpio, target.en_pin, 0);
	}
	switch(target.channel1){
		case TIM_CHANNEL_1:
			target.timer->CCR1 = ccr1;
			break;
		case TIM_CHANNEL_2:
			target.timer->CCR2 = ccr1;
			break;
		case TIM_CHANNEL_3:
			target.timer->CCR3 = ccr1;
			break;
		case TIM_CHANNEL_4:
			target.timer->CCR4 = ccr1;
			break;
		default:
			break;
	}
	switch(target.channel2){
			case TIM_CHANNEL_1:
				target.timer->CCR1 = ccr2;
				break;
			case TIM_CHANNEL_2:
				target.timer->CCR2 = ccr2;
				break;
			case TIM_CHANNEL_3:
				target.timer->CCR3 = ccr2;
				break;
			case TIM_CHANNEL_4:
				target.timer->CCR4 = ccr2;
				break;
			default:
				break;
	}

}
