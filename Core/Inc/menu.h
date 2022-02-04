/*
 * menu.h
 *
 *  Created on: 11 авг. 2021 г.
 *      Author: Alexander
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

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

uint8_t menu_pressed;

void main_screen();
void menu(uint16_t volume, uint8_t k_volume, uint8_t gas_time, uint8_t drainage_time);
void switch_page ();
void menu_change ();
void switch_menu ();
void load_var(uint16_t *var, uint16_t Addr);
void cast_8_to_16(uint16_t var_8_1, uint16_t var_8_2, uint16_t *var_16);
#endif /* INC_MENU_H_ */
