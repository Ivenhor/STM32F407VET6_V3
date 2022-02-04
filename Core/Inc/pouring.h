/*
 * pouring.h
 *
 *  Created on: Jul 6, 2021
 *      Author: Alexander
 */

#ifndef INC_POURING_H_
#define INC_POURING_H_

#include "stm32f4xx_hal.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "config.h"
#include "menu.h"

//void sensor_test();
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void time();
void load_init();
//void pwm_test ();
//void gas(uint8_t gas_time);
//void pouring (uint8_t volume, uint8_t k_volume);
//void drainage(uint8_t drainage_time);
void filling_cycle(uint16_t volume, uint16_t k_volume, uint16_t gas_time, uint16_t drainage_time);



#endif /* INC_POURING_H_ */
