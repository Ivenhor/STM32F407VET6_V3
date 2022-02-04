/*
 * menu.c
 *
 *  Created on: 11 авг. 2021 г.
 *      Author: Alexander
 */
#include "menu.h"


/*****************************************************************************************************************************************/
/**
 * @brief save variable
 * @param var - what var to save
 * @param Addr - address to be saved. Example of mem address 1,2,3,4
*/
void save_var (uint16_t var, uint16_t Addr)  // example of mem address 1,2,3,4
{

	uint8_t data=var;
	// HAL expects address to be shifted one bit to the left
	uint16_t devAddr = (0x50 << 1);
	uint16_t memAddr = Addr;
	HAL_StatusTypeDef status;

	HAL_I2C_Mem_Write(&hi2c2, devAddr, memAddr, 2,
		 &data, 1, HAL_MAX_DELAY);

	    for(;;) { // wait...
	        status = HAL_I2C_IsDeviceReady(&hi2c2, devAddr, 1,
	                                        HAL_MAX_DELAY);
	        if(status == HAL_OK)
	            break;
	    }
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief load variable
 * @param var - what var to load
 * @param Addr - address to be load from. Example of mem address 1,2,3,4
*/
void load_var(uint16_t *var, uint16_t Addr) // example of mem address 1,2,3,4
{
	uint8_t data;
	// HAL expects address to be shifted one bit to the left
	uint16_t devAddr = (0x50 << 1);
	uint16_t memAddr = Addr;

	HAL_I2C_Mem_Read(&hi2c2, devAddr, memAddr, 2,
			&data, 1, HAL_MAX_DELAY);
	*var=data;
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief draw main screen
*/
void main_screen()
{
	ILI9341_Fill_Screen(BLUE );
	ILI9341_Draw_Text("Ready to start", 20, 100, WHITE, 3, BLUE);

}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief transform uint16_t to uint8_t
 * @param var_16 - 16 bit variable to be transformed
 * @param var_8_1 - first 8 bit variable to store data
 * @param var_8_2 - second 8 bit variable to store data
*/
void cast_16_to_8 (uint16_t var_16, uint16_t  *var_8_1, uint16_t *var_8_2)
{
	uint16_t i=0;
	*var_8_1=var_16/255;
	i=*var_8_1*255;
	*var_8_2=var_16-i;
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief transform uint8_t to uint16_t
 * @param var_8_1 - first 8 bit variable to restore data
 * @param var_8_2 - second 8 bit variable to restore data
 * @param Var_16 - 16 bit variable to be restored
*/
void cast_8_to_16(uint16_t var_8_1, uint16_t var_8_2, uint16_t *var_16)
{
	uint16_t i=0;
	i=var_8_1*255;
	*var_16=i+var_8_2;
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief draw menu template
 * @param volume - what volume to draw
 * @param k_volume - what k_volume to draw
 * @param gas_time - what gas_time to draw
 * @param drainage_time - what drainage_time to draw
*/
void menu(uint16_t volume, uint8_t k_volume, uint8_t gas_time, uint8_t drainage_time)
{
	ILI9341_Fill_Screen(BLUE );
	ILI9341_Draw_Text("MENU", 100, 20, WHITE, 3, BLUE);
	volume=volume;
	char volume_buf[10];
	sprintf(volume_buf, "%.d", volume);
	ILI9341_Draw_Text("Volume", 10, 80, WHITE, 2, BLUE);
	ILI9341_Draw_Text(volume_buf, 180, 80, WHITE, 2, BLUE);
	char k_volume_buf[10];
	sprintf(k_volume_buf, "%.d", k_volume);
	ILI9341_Draw_Text("Volume shift", 10, 100, WHITE, 2, BLUE);
	ILI9341_Draw_Text(k_volume_buf, 180, 100, WHITE, 2, BLUE);
	char gas_time_buf[10];
	sprintf(gas_time_buf, "%.d", gas_time);
	ILI9341_Draw_Text("Gas Time", 10, 120, WHITE, 2, BLUE);
	ILI9341_Draw_Text(gas_time_buf, 180, 120, WHITE, 2, BLUE);
	char drainage_time_buf[10];
	sprintf(drainage_time_buf, "%.d", drainage_time);
	ILI9341_Draw_Text("Drainage time", 10, 140, WHITE, 2, BLUE);
	ILI9341_Draw_Text(drainage_time_buf, 180, 140, WHITE, 2, BLUE);
	ILI9341_Draw_Text("-", 10, 175, WHITE, 4, BLUE);
	ILI9341_Draw_Text("+", 280, 175, WHITE, 4, BLUE);
	ILI9341_Draw_Text("Switch page", 60, 180, WHITE, 3, BLUE);


	//char page_buf[10];
	//sprintf(page_buf, "%.d", page);
	//ILI9341_Draw_Text(page_buf, 180, 180, WHITE, 2, BLUE);
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief draw service menu template
*/
void servis_menu()
{

}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief draw pouring menu template
*/
void pouring_menu()
{
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
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief change variable
 * @param i choose what var to change
*/
void change_var(uint16_t *i)
{
	//while(1)

	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)==0 && menu_pressed==0 && page!=0)
		{
			*i=*i+1;

			HAL_Delay(150);

		}
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)==0 && menu_pressed==0 && page!=0)
		{
			*i=*i-1;

			HAL_Delay(150);

		}

}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief choose what var to change, draw it on screen and save it
*/
void choose_var()
{
	if(page==1 && var == 1 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 77, 305, 97, GREEN);
		change_var(&volume_1);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", volume_1);
		ILI9341_Draw_Text(menu_buf, 180, 80, WHITE, 2, BLUE);
		cast_16_to_8(volume_1, &volume_1_1, &volume_1_2);
		save_var(volume_1_1, 1);
		save_var(volume_1_2, 2);
	}
	if(page==1 && var == 2 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 98, 305, 117, GREEN);
		change_var(&k_volume_1);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", k_volume_1);
		ILI9341_Draw_Text(menu_buf, 180, 100, WHITE, 2, BLUE);
		save_var(k_volume_1,3);

	}
	if(page==1 && var == 3 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 118, 305, 137, GREEN);
		change_var(&gas_time_1);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", gas_time_1);
		ILI9341_Draw_Text(menu_buf, 180, 120, WHITE, 2, BLUE);
		save_var(gas_time_1,4);
	}
	if(page==1 && var == 4 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 138, 305, 157, GREEN);
		change_var(&drainage_time_1);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", drainage_time_1);
		ILI9341_Draw_Text(menu_buf, 180, 140, WHITE, 2, BLUE);
		save_var(drainage_time_1,5);
	}
	if(page==2 && var == 1 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 77, 305, 97, GREEN);
		change_var(&volume_2);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", volume_2);
		ILI9341_Draw_Text(menu_buf, 180, 80, WHITE, 2, BLUE);
		cast_16_to_8(volume_2, &volume_2_1, &volume_2_2);
		save_var(volume_2_1, 6);
		save_var(volume_2_2, 7);
	}
	if(page==2 && var == 2 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 98, 305, 117, GREEN);
		change_var(&k_volume_2);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", k_volume_2);
		ILI9341_Draw_Text(menu_buf, 180, 100, WHITE, 2, BLUE);
		save_var(k_volume_2,8);

	}
	if(page==2 && var == 3 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 118, 305, 137, GREEN);
		change_var(&gas_time_2);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", gas_time_2);
		ILI9341_Draw_Text(menu_buf, 180, 120, WHITE, 2, BLUE);
		save_var(gas_time_2,109);
	}
	if(page==2 && var == 4 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 138, 305, 157, GREEN);
		change_var(&drainage_time_2);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", drainage_time_2);
		ILI9341_Draw_Text(menu_buf, 180, 140, WHITE, 2, BLUE);
		save_var(drainage_time_2,110);
	}
	if(page==3 && var == 1 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 77, 305, 97, GREEN);
		change_var(&volume_3);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", volume_3);
		ILI9341_Draw_Text(menu_buf, 180, 80, WHITE, 2, BLUE);
		cast_16_to_8(volume_3, &volume_3_1, &volume_3_2);
		save_var(volume_3_1, 11);
		save_var(volume_3_2, 12);
	}
	if(page==3 && var == 2 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 98, 305, 117, GREEN);
		change_var(&k_volume_3);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", k_volume_3);
		ILI9341_Draw_Text(menu_buf, 180, 100, WHITE, 2, BLUE);
		save_var(k_volume_3,13);

	}
	if(page==3 && var == 3 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 118, 305, 137, GREEN);
		change_var(&gas_time_3);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", gas_time_3);
		ILI9341_Draw_Text(menu_buf, 180, 120, WHITE, 2, BLUE);
		save_var(gas_time_3,14);
	}
	if(page==3 && var == 4 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 138, 305, 157, GREEN);
		change_var(&drainage_time_3);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", drainage_time_3);
		ILI9341_Draw_Text(menu_buf, 180, 140, WHITE, 2, BLUE);
		save_var(drainage_time_3,15);
	}
	if(page==4 && var == 1 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 77, 305, 97, GREEN);
		change_var(&volume_4);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", volume_4);
		ILI9341_Draw_Text(menu_buf, 180, 80, WHITE, 2, BLUE);
		cast_16_to_8(volume_4, &volume_4_1, &volume_4_2);
		save_var(volume_4_1, 16);
		save_var(volume_4_2, 17);
	}
	if(page==4 && var == 2 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 98, 305, 117, GREEN);
		change_var(&k_volume_4);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", k_volume_4);
		ILI9341_Draw_Text(menu_buf, 180, 100, WHITE, 2, BLUE);
		save_var(k_volume_4,18);

	}
	if(page==4 && var == 3 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 118, 305, 137, GREEN);
		change_var(&gas_time_4);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", gas_time_4);
		ILI9341_Draw_Text(menu_buf, 180, 120, WHITE, 2, BLUE);
		save_var(gas_time_4,19);
	}
	if(page==4 && var == 4 && menu_pressed==0)
	{
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 138, 305, 157, GREEN);
		change_var(&drainage_time_4);
		char menu_buf[10];
		sprintf(menu_buf, "%.d", drainage_time_4);
		ILI9341_Draw_Text(menu_buf, 180, 140, WHITE, 2, BLUE);
		save_var(drainage_time_4,20);
	}
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief switch between menu pages
*/
void switch_page ()
{
	switch(page)
	{
	case 1:
	menu(volume_1,k_volume_1,gas_time_1,drainage_time_1); break;
	case 2:
	menu(volume_2,k_volume_2,gas_time_2,drainage_time_2); break;
	case 3:
	menu(volume_3,k_volume_3,gas_time_3,drainage_time_3); break;
	case 4:
	menu(volume_4,k_volume_4,gas_time_4,drainage_time_4); break;
	case 5:
	page=0; break;
	default:
	break;
	}
	if(page>=5) page=5;
	if(page==0)
	{
		var=5;
		ILI9341_Fill_Screen(BLUE );
		ILI9341_Draw_Text("Ready to start", 20, 100, WHITE, 3, BLUE);
	}
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief draw rectangle to indicate what var is changing
*/
void switch_var()
{
	switch(var)
	{
	case 1:
		//ILI9341_Fill_Screen(BLUE );
		//menu(volume_1,k_volume_1,gas_time_1,drainage_time_1);
		ILI9341_Draw_Hollow_Rectangle_Coord(90, 17, 180, 47, WHITE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 77, 305, 97, WHITE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 98, 305, 117, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 118, 305, 137, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 138, 305, 157, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(5, 175, 305, 210, BLUE);
		//change_var(volume_1);
		break;
	case 2:
		//ILI9341_Fill_Screen(BLUE );
		//menu(volume_1,k_volume_1,gas_time_1,drainage_time_1);
		ILI9341_Draw_Hollow_Rectangle_Coord(90, 17, 180, 47, WHITE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 77, 305, 97, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 98, 305, 117, WHITE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 118, 305, 137, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 138, 305, 157, BLUE);
		break;
	case 3:
		//ILI9341_Fill_Screen(BLUE );
		//menu(volume_1,k_volume_1,gas_time_1,drainage_time_1);
		ILI9341_Draw_Hollow_Rectangle_Coord(90, 17, 180, 47, WHITE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 77, 305, 97, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 98, 305, 117, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 118, 305, 137, WHITE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 138, 305, 157, BLUE);
		break;
	case 4:
		//ILI9341_Fill_Screen(BLUE );
		//menu(volume_1,k_volume_1,gas_time_1,drainage_time_1);
		ILI9341_Draw_Hollow_Rectangle_Coord(90, 17, 180, 47, WHITE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 77, 305, 97, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 98, 305, 117, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 118, 305, 137, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 138, 305, 157, WHITE);
		ILI9341_Draw_Hollow_Rectangle_Coord(5, 175, 305, 210, BLUE);
		break;
	case 5:
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 77, 305, 97, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 138, 305, 157, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(5, 175, 305, 210, WHITE);
		break;
	case 6:
		var=0; break;
	default:
		break;
	}
	if(var>=6) var=6;
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief draw rectangle to indicate idle state of menu
*/
void switch_to_var ()
{
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0 && menu_pressed==0 && page!=0)
	{
		menu_pressed=1;
		ILI9341_Draw_Hollow_Rectangle_Coord(90, 17, 180, 47, WHITE);
		HAL_Delay(150);
	}
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0 && menu_pressed==1 && page!=0)
	{
		menu_pressed=0;
		HAL_Delay(150);
		ILI9341_Draw_Hollow_Rectangle_Coord(90, 17, 180, 47, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 77, 305, 97, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 98, 305, 117, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 118, 305, 137, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 138, 305, 157, BLUE);
		ILI9341_Draw_Hollow_Rectangle_Coord(5, 175, 305, 210, BLUE);
	}

}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief change menu page
*/
void menu_change ()
{

	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)==0 && menu_pressed==1 && page!=0)
	{
		var++;
		switch_var();
	}
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)==0 && menu_pressed==1 && page!=0)
		{
			var--;
			switch_var();
		}
	/*
	char var_buf[10];
	sprintf(var_buf, "%.d", var);
	ILI9341_Draw_Text(var_buf, 180, 160, WHITE, 2, BLUE);
	*/
	//if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0) break;
	HAL_Delay(100);

}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
/**
 * @brief swich between menu pages
*/
void switch_menu()
{
	if(page==0)
	{
	var=5;
	}
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)==0 && menu_pressed==0 && var==5)
	{
		page++;
		HAL_Delay(100);
		switch_page ();
	}
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)==0 && menu_pressed==0 && var==5)
	{
		page--;
		HAL_Delay(100);
		switch_page ();
 	}
	switch_to_var();
	menu_change();
	choose_var();
}
/*****************************************************************************************************************************************/
