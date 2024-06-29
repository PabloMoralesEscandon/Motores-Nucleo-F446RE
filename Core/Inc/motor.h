/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTOR_H
#define __MOTOR_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private defines -----------------------------------------------------------*/
#define MAX(value, max) ((value) > (max) ? (max) : (value))
#define MIN(value, min) ((value) < (min) ? (min) : (value))

/* Exported types ------------------------------------------------------------*/

typedef enum {
	CH1,
	CH2,
	CH3,
	CH4
} Channel;

typedef struct{
	TIM_TypeDef* timer;
	TIM_HandleTypeDef timer_handle;
	Channel channel;
	GPIO_TypeDef* in1;
	GPIO_TypeDef* in2;
	uint16_t in1_pin;
	uint16_t in2_pin;
	uint16_t prescaler;
	uint16_t arr;
} Motor;

/* Exported functions prototypes ---------------------------------------------*/

Motor init_motor(TIM_TypeDef* timer, TIM_HandleTypeDef timer_handle, Channel channel, GPIO_TypeDef* in1, GPIO_TypeDef* in2, uint16_t in1_pin, uint16_t in2_pin, uint16_t prescaler, uint16_t arr);

void set_speed(Motor target, double speed);

#endif


