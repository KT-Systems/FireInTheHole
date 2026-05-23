/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "iwdg.h"
#include "adBms6830Data.h"
#include "adbms_main.h"
#include "adBms_Application.h"
#include "devices.h"
#include "fdcan.h"
#include "cmsis_os.h"
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
#define MEDIA_NRST_Pin GPIO_PIN_4
#define MEDIA_NRST_GPIO_Port GPIOE
#define Media_Select_Pin GPIO_PIN_13
#define Media_Select_GPIO_Port GPIOC
#define OSC32_IN_Pin GPIO_PIN_14
#define OSC32_IN_GPIO_Port GPIOC
#define OSC32_OUT_Pin GPIO_PIN_15
#define OSC32_OUT_GPIO_Port GPIOC
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOH
#define OSC_OUT_Pin GPIO_PIN_1
#define OSC_OUT_GPIO_Port GPIOH
#define LED_CAN_2_Pin GPIO_PIN_0
#define LED_CAN_2_GPIO_Port GPIOC
#define LED_Heart_Pin GPIO_PIN_1
#define LED_Heart_GPIO_Port GPIOC
#define LED_CAN_3_Pin GPIO_PIN_2
#define LED_CAN_3_GPIO_Port GPIOC
#define IMD_PWM_Input_Pin GPIO_PIN_0
#define IMD_PWM_Input_GPIO_Port GPIOA
#define DCDC_Temperature_Input_Pin GPIO_PIN_2
#define DCDC_Temperature_Input_GPIO_Port GPIOA
#define Humidity_Input_Pin GPIO_PIN_3
#define Humidity_Input_GPIO_Port GPIOA
#define Air_Temperature_Input_Pin GPIO_PIN_4
#define Air_Temperature_Input_GPIO_Port GPIOA
#define AMS_SCK_Pin GPIO_PIN_5
#define AMS_SCK_GPIO_Port GPIOA
#define AMS_MISO_Pin GPIO_PIN_6
#define AMS_MISO_GPIO_Port GPIOA
#define AMS_MOSI_Pin GPIO_PIN_7
#define AMS_MOSI_GPIO_Port GPIOA
#define Fans_Output_Pin GPIO_PIN_4
#define Fans_Output_GPIO_Port GPIOC
#define AMS_CS_1_Pin GPIO_PIN_5
#define AMS_CS_1_GPIO_Port GPIOC
#define AMS_CS_2_Pin GPIO_PIN_0
#define AMS_CS_2_GPIO_Port GPIOB
#define AIR_Plus_Driver_Output_Pin GPIO_PIN_2
#define AIR_Plus_Driver_Output_GPIO_Port GPIOB
#define AIR_Plus_Supply_Input_Pin GPIO_PIN_8
#define AIR_Plus_Supply_Input_GPIO_Port GPIOE
#define LED_CAN_1_Pin GPIO_PIN_9
#define LED_CAN_1_GPIO_Port GPIOE
#define CHIP_EN_Pin GPIO_PIN_14
#define CHIP_EN_GPIO_Port GPIOE
#define SPI_RDY_Pin GPIO_PIN_15
#define SPI_RDY_GPIO_Port GPIOE
#define SPI_RDY_EXTI_IRQn EXTI15_10_IRQn
#define WIFI_CLK_Pin GPIO_PIN_10
#define WIFI_CLK_GPIO_Port GPIOB
#define SPI_CS_Pin GPIO_PIN_11
#define SPI_CS_GPIO_Port GPIOB
#define WIFI_MISO_Pin GPIO_PIN_14
#define WIFI_MISO_GPIO_Port GPIOB
#define WIFI_MOSI_Pin GPIO_PIN_15
#define WIFI_MOSI_GPIO_Port GPIOB
#define TSMS_Input_Pin GPIO_PIN_8
#define TSMS_Input_GPIO_Port GPIOD
#define DAT0_MCU_Pin GPIO_PIN_8
#define DAT0_MCU_GPIO_Port GPIOC
#define DAT1_MCU_Pin GPIO_PIN_9
#define DAT1_MCU_GPIO_Port GPIOC
#define AIR_Minus_State_Input_Pin GPIO_PIN_8
#define AIR_Minus_State_Input_GPIO_Port GPIOA
#define PG_MCU_Pin GPIO_PIN_9
#define PG_MCU_GPIO_Port GPIOA
#define VBUS_Sense_Pin GPIO_PIN_10
#define VBUS_Sense_GPIO_Port GPIOA
#define SWDIO_MCU_Pin GPIO_PIN_13
#define SWDIO_MCU_GPIO_Port GPIOA
#define SWCLK_MCU_Pin GPIO_PIN_14
#define SWCLK_MCU_GPIO_Port GPIOA
#define LED_SD_H7_Pin GPIO_PIN_15
#define LED_SD_H7_GPIO_Port GPIOA
#define DAT2_MCU_Pin GPIO_PIN_10
#define DAT2_MCU_GPIO_Port GPIOC
#define DAT3_MCU_Pin GPIO_PIN_11
#define DAT3_MCU_GPIO_Port GPIOC
#define CLK_MCU_Pin GPIO_PIN_12
#define CLK_MCU_GPIO_Port GPIOC
#define CMD_MCU_Pin GPIO_PIN_2
#define CMD_MCU_GPIO_Port GPIOD
#define IMD_Latched_Input_Pin GPIO_PIN_3
#define IMD_Latched_Input_GPIO_Port GPIOD
#define Air_Plus_State_Input_Pin GPIO_PIN_4
#define Air_Plus_State_Input_GPIO_Port GPIOD
#define Pre_State_Input_Pin GPIO_PIN_5
#define Pre_State_Input_GPIO_Port GPIOD
#define AMS_OK_Output_Pin GPIO_PIN_6
#define AMS_OK_Output_GPIO_Port GPIOD
#define AIRs_Voltage_Over_60_Input_Pin GPIO_PIN_7
#define AIRs_Voltage_Over_60_Input_GPIO_Port GPIOD
#define SWO_MCU_Pin GPIO_PIN_3
#define SWO_MCU_GPIO_Port GPIOB
#define SD_Detection_Pin GPIO_PIN_4
#define SD_Detection_GPIO_Port GPIOB
#define LED_SD_Pin GPIO_PIN_5
#define LED_SD_GPIO_Port GPIOB
#define Vicor_SCL_Pin GPIO_PIN_6
#define Vicor_SCL_GPIO_Port GPIOB
#define Vicor_SDA_Pin GPIO_PIN_7
#define Vicor_SDA_GPIO_Port GPIOB
#define IMD_OK_Input_Pin GPIO_PIN_8
#define IMD_OK_Input_GPIO_Port GPIOB
#define AMS_Latched_Input_Pin GPIO_PIN_9
#define AMS_Latched_Input_GPIO_Port GPIOB
#define LED_CAN2_Pin GPIO_PIN_0
#define LED_CAN2_GPIO_Port GPIOE
#define AA_Button_Output_Pin GPIO_PIN_1
#define AA_Button_Output_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */
#define criticalCan hfdcan1
#define chargerCan hfdcan2

#define SD_SPI_HANDLE hspi2

#define BMSCommSPI hspi1

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
