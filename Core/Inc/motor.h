/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTOR_H
#define __MOTOR_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private defines -----------------------------------------------------------*/
#define MAX(value, max) ((value) > (max) ? (max) : (value))
#define MIN(value, min) ((value) < (min) ? (min) : (value))

/* Exported types ------------------------------------------------------------*/

typedef struct{
	TIM_TypeDef* timer;
	TIM_HandleTypeDef timer_handle;
	uint32_t channel1;
	uint32_t channel2;
	GPIO_TypeDef* en_gpio;
	uint16_t en_pin;
	uint16_t prescaler;
	uint16_t arr;
} Motor;

/* Exported functions prototypes ---------------------------------------------*/

Motor init_motor(TIM_TypeDef* timer, TIM_HandleTypeDef timer_handle, uint32_t channel1, uint32_t channel2, GPIO_TypeDef* en_gpio, uint16_t en_pin, uint16_t prescaler, uint16_t arr);

void set_speed(Motor target, double speed);

#endif


