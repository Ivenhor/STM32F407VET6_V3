/*
 * pouring.c
 *
 *  Created on: Jul 6, 2021
 *      Author: Alexander
 */



#include "pouring.h"

void save ()
{
	 //const char wmsg[] = "10";
	 //char rmsg[sizeof(wmsg)];


	uint8_t data=pwm_start_correction/100;
	// HAL expects address to be shifted one bit to the left
	uint16_t devAddr = (0x50 << 1);
	uint16_t memAddr = 21;
	HAL_StatusTypeDef status;

	HAL_I2C_Mem_Write(&hi2c2, devAddr, memAddr, I2C_MEMADD_SIZE_16BIT,
		 &data, 1, HAL_MAX_DELAY);

	    for(;;) { // wait...
	        status = HAL_I2C_IsDeviceReady(&hi2c2, devAddr, 1,
	                                        HAL_MAX_DELAY);
	        if(status == HAL_OK)
	            break;
	    }

	    char data_buf[10];
	    sprintf(data_buf, "%d", data);
	    ILI9341_Draw_Text(data_buf, 10, 10, WHITE, 2, BLUE);

}

void load()
{
	uint8_t data;
	// HAL expects address to be shifted one bit to the left
	uint16_t devAddr = (0x50 << 1);
	uint16_t memAddr = 21;

	HAL_I2C_Mem_Read(&hi2c2, devAddr, memAddr, I2C_MEMADD_SIZE_16BIT,
			&data, 1, HAL_MAX_DELAY);
	pwm_start_correction=data*100;

	char data_buf[10];
	sprintf(data_buf, "%d", data);
	ILI9341_Draw_Text(data_buf, 10, 10, WHITE, 2, BLUE);

}

void flow ()
{

	pulses_per_sec=pulses-last_pulses;
	last_pulses=pulses;
	liters_per_min=((float)pulses_per_sec/(float)ref_volume)/3*600/1000;
	liters=pulses/ref_volume/1000;
/*
	char flow_buf[10];
	sprintf(flow_buf, "%d", pulses_per_sec);
	ILI9341_Draw_Text(flow_buf, 10, 80, WHITE, 2, BLUE);

*/
	char liters_buf[10];
	sprintf(liters_buf, "%.2f", liters);
	ILI9341_Draw_Text("Volume:", 10, 140, WHITE, 2, BLUE);
	ILI9341_Draw_Text(liters_buf, 150, 140, WHITE, 2, BLUE);
	ILI9341_Draw_Text("L", 200, 140, WHITE, 2, BLUE);


	char liters_per_min_buf[10];
	sprintf(liters_per_min_buf, "%.2f", liters_per_min);
	ILI9341_Draw_Text("Speed:", 10, 120, WHITE, 2, BLUE);
	ILI9341_Draw_Text(liters_per_min_buf, 150, 120, WHITE, 2, BLUE);
	ILI9341_Draw_Text("L/m", 200, 120, WHITE, 2, BLUE);

	char pulses_buf[10];
	sprintf(pulses_buf, "%lu", pulses);
	ILI9341_Draw_Text(pulses_buf, 150, 160, WHITE, 2, BLUE);

	uint16_t end_vol=volume_1*k_volume_1;
	char test_buf[10];
	sprintf(test_buf, "%d", end_vol);
	ILI9341_Draw_Text(test_buf, 150, 180, WHITE, 2, BLUE);



}



void pwm_valve()
{
	if (liters_per_min<=pouring_speed)
	{
		PWM-=step;
		if(PWM<=50)
		{
			PWM=50;
		}
	}
	if (liters_per_min>=pouring_speed)
	{
		PWM+=step;
		if(PWM>=9999)
		{
			PWM=9999;
		}
	}
	TIM3->CCR4=PWM;
	uint8_t duty_cycle;
	duty_cycle=PWM/100;
	char pwm_buf[10];
	sprintf(pwm_buf, "%d", duty_cycle);
	ILI9341_Draw_Text("Duty cycle:", 10, 100, WHITE, 2, BLUE);
	ILI9341_Draw_Text(pwm_buf, 150, 100, WHITE, 2, BLUE);
	ILI9341_Draw_Text("%", 180, 100, WHITE, 2, BLUE);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
        if(htim->Instance == TIM1) //check if the interrupt comes from TIM1
        {
        	ms++;
        	time();
        }
        if(htim->Instance == TIM2) //check if the interrupt comes from TIM1
                {
        			flow();
        			if(sec>=start_control_time || optimum_speed)
        			{
        			pwm_valve();
        			}
                }
}

void time()
{
	//uint16_t sec=0;
	if(ms>=999)
	{
		sec++;
		//HAL_GPIO_TogglePin(GPIOB, Signal_LED_Pin);
		ms=0;

	char sec_buf[10];
	sprintf(sec_buf, "%d", sec);
	ILI9341_Draw_Text(sec_buf, 210, 10, WHITE, 2, BLUE);


	}
}



void error_check(uint16_t gas_time)
{
	if(pulses<=10 && sec-gas_time>2)										// check flow
	{
		start_pulse_error=1;
		error_recovery=1;
	} else
	{
		start_pulse_error=0;
	}
	if (liters_per_min>=pouring_speed) 										//check if speed optimal
	{
		optimum_speed=1;
	}

}

void error_hendler()
{
	if (start_pulse_error==1)
	{
		pwm_valve();
	}
	if(error_recovery==1 && start_pulse_error==0)
	{
		PWM=pwm_start_correction;
		error_recovery=0;
	}

}


void start_sequence(uint16_t k_volume, uint16_t gas_time)											// do start stuff
{
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

	ILI9341_Fill_Screen(BLUE);

	load();
	//load_var(k_volume_1, 2);
	//gas_time=5;
	//drainage_time=5;
	PWM=5000;
	//volume=100;
	pouring_speed=1;
	step=50;
	//k_volume=68;

	start_control_time=gas_time+2;

	ref_volume=100*(float)k_volume/1000;									// check if pwm is nominal

	if(pwm_start_correction>=8500)
	{
		pwm_start_correction=8500;
	}
	if(pwm_start_correction<=3000)
		{
			pwm_start_correction=3000;
		}


	PWM=pwm_start_correction;											// set start pwm



}
void stop_sequence()													// do stop stuff
{
	liters_per_min=0;
	pulses_per_sec=0;
	ref_volume=0;
	start_control_time=0;
	optimum_speed=0;

	error_recovery=0;

	pwm_start_correction=PWM;

	save();

	HAL_TIM_Base_Stop_IT(&htim1);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
}

void gas(uint16_t gas_time)													// start gas sequence
{
	HAL_GPIO_WritePin(GPIOE, Load_out_2_Pin, GPIO_PIN_SET);					// Open EPK1
	TIM3->CCR4=9999;														// Close drainage
	HAL_Delay(gas_time*1000);
	HAL_GPIO_WritePin(GPIOE, Load_out_2_Pin, GPIO_PIN_RESET);				//Close EPK1
	TIM3->CCR4=PWM;															//start drainage control
	HAL_GPIO_WritePin(GPIOE, Load_out_3_Pin, GPIO_PIN_SET);                 //Open EGK1
}

void pouring (uint16_t volume, uint16_t k_volume, uint16_t gas_time)								// start pouring sequence
{

	pulses=0;
	HAL_TIM_Base_Start_IT(&htim2);

	do
	{
		error_check(gas_time);
		error_hendler();


	} while (pulses<=volume*k_volume/10);                                   // i dont know why /10 is needed somehow volume is 10 times bigger than needed
	pulses=0;
	HAL_TIM_Base_Stop_IT(&htim2);

}

void drainage(uint16_t drainage_time)										// start drainage sequence
{
	HAL_GPIO_WritePin(GPIOE, Load_out_3_Pin, GPIO_PIN_RESET);				//Close EGK1
	TIM3->CCR4=PWM;															//start drainage control
	HAL_Delay(drainage_time*1000);
	TIM3->CCR4=0;
}

void filling_cycle(uint16_t volume, uint16_t k_volume, uint16_t gas_time, uint16_t drainage_time)		//full cycle of pouring
{

	//load();
	  start_sequence(k_volume, gas_time);
	  gas(gas_time);
	  pouring(volume, k_volume,drainage_time);
	  drainage(drainage_time);
	  stop_sequence();
	  //save();

	  sec=0;
	  main_screen();
}
