/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Sensor_Pin GPIO_PIN_2
#define Sensor_GPIO_Port GPIOA
#define Sensor_EXTI_IRQn EXTI2_IRQn
#define TFT_DC_Pin GPIO_PIN_4
#define TFT_DC_GPIO_Port GPIOC
#define TFT_RST_Pin GPIO_PIN_5
#define TFT_RST_GPIO_Port GPIOC
#define TFT_CS_Pin GPIO_PIN_0
#define TFT_CS_GPIO_Port GPIOB
#define Load_out_3_Pin GPIO_PIN_7
#define Load_out_3_GPIO_Port GPIOE
#define Load_out_2_Pin GPIO_PIN_8
#define Load_out_2_GPIO_Port GPIOE
#define Load_out_1_Pin GPIO_PIN_9
#define Load_out_1_GPIO_Port GPIOE
#define Stop_sensor_1_Pin GPIO_PIN_13
#define Stop_sensor_1_GPIO_Port GPIOE
#define Stop_sensor_2_Pin GPIO_PIN_14
#define Stop_sensor_2_GPIO_Port GPIOE
#define Stop_sensor_3_Pin GPIO_PIN_15
#define Stop_sensor_3_GPIO_Port GPIOE
#define Signal_LED_Pin GPIO_PIN_12
#define Signal_LED_GPIO_Port GPIOB
#define Pressure_Pin GPIO_PIN_13
#define Pressure_GPIO_Port GPIOB
#define D_OUT_Pin GPIO_PIN_9
#define D_OUT_GPIO_Port GPIOD
#define D_SCK_Pin GPIO_PIN_10
#define D_SCK_GPIO_Port GPIOD
#define Led_4_Pin GPIO_PIN_11
#define Led_4_GPIO_Port GPIOD
#define Btn_4_Pin GPIO_PIN_12
#define Btn_4_GPIO_Port GPIOD
#define Led_3_Pin GPIO_PIN_13
#define Led_3_GPIO_Port GPIOD
#define Btn_3_Pin GPIO_PIN_14
#define Btn_3_GPIO_Port GPIOD
#define Led_2_Pin GPIO_PIN_15
#define Led_2_GPIO_Port GPIOD
#define Btn_2_Pin GPIO_PIN_6
#define Btn_2_GPIO_Port GPIOC
#define Led_1_Pin GPIO_PIN_7
#define Led_1_GPIO_Port GPIOC
#define Btn_1_Pin GPIO_PIN_8
#define Btn_1_GPIO_Port GPIOC
#define T_CLK_Pin GPIO_PIN_15
#define T_CLK_GPIO_Port GPIOA
#define T_CS_Pin GPIO_PIN_10
#define T_CS_GPIO_Port GPIOC
#define T_MOSI_Pin GPIO_PIN_11
#define T_MOSI_GPIO_Port GPIOC
#define T_MISO_Pin GPIO_PIN_12
#define T_MISO_GPIO_Port GPIOC
#define T_IRQ_Pin GPIO_PIN_0
#define T_IRQ_GPIO_Port GPIOD
#define Save_Pin GPIO_PIN_4
#define Save_GPIO_Port GPIOB
#define Menu_Pin GPIO_PIN_5
#define Menu_GPIO_Port GPIOB
#define Minus_Pin GPIO_PIN_8
#define Minus_GPIO_Port GPIOB
#define Plus_Pin GPIO_PIN_9
#define Plus_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
