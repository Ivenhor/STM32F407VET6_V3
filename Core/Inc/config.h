/*
 * config.h
 *
 *  Created on: Jul 5, 2021
 *      Author: Alexander
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_




uint32_t pulses;

uint16_t PWM;


uint16_t volume_1;
uint16_t volume_2;
uint16_t volume_3;
uint16_t volume_4;

uint16_t volume_1_1;
uint16_t volume_1_2;
uint16_t volume_2_1;
uint16_t volume_2_2;
uint16_t volume_3_1;
uint16_t volume_3_2;
uint16_t volume_4_1;
uint16_t volume_4_2;

uint16_t gas_time_1;
uint16_t gas_time_2;
uint16_t gas_time_3;
uint16_t gas_time_4;


uint16_t drainage_time_1;
uint16_t drainage_time_2;
uint16_t drainage_time_3;
uint16_t drainage_time_4;


uint8_t pouring_speed;


uint16_t k_volume_1;
uint16_t k_volume_2;
uint16_t k_volume_3;
uint16_t k_volume_4;



uint16_t pulses_per_sec;
uint16_t last_pulses;


float liters;
float liters_per_min;
float ref_volume;

uint8_t var;
uint8_t page;


uint16_t ms;
uint16_t sec;
uint16_t step;

uint16_t pwm_start_correction;

uint8_t start_control_time;
//------------------------------FLAGS---------------------------------------------------------


uint8_t optimum_speed;
uint8_t flag_3;

uint8_t start_pulse_error;
uint8_t error_recovery;
uint8_t error_3;

//------------------------------FLAGS---------------------------------------------------------





#endif /* INC_CONFIG_H_ */
