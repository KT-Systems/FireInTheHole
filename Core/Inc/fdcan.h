/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.h
  * @brief   This file contains all the function prototypes for
  *          the fdcan.c file
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
#ifndef __FDCAN_H__
#define __FDCAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
extern CANData canData;
extern IsabellenData ivt;
extern ACUData acu;
extern ChargerData charger;
extern BMSData bms;
extern VicorData vicor;
/* USER CODE END Includes */

extern FDCAN_HandleTypeDef hfdcan1;

extern FDCAN_HandleTypeDef hfdcan2;

/* USER CODE BEGIN Private defines */

//CAN IDs

#define START_PRECHARGE_CAN_ID 0x100

//IVT IDs
#define IVT_MESSAGE_COMMAND_CAN_ID 0x411

#define IVT_CURRENT_CAN_ID 0x521

#define IVT_VOLTAGE_1_CAN_ID 0x522

#define IVT_VOLTAGE_2_CAN_ID 0x523

#define IVT_VOLTAGE_3_CAN_ID 0x524

#define IVT_TEMPERATURE_CAN_ID 0x525

#define IVT_WATTAGE_CAN_ID 0x526

#define IVT_CURRENT_COUNTER_CAN_ID 0x527

#define IVT_WATTAGE_COUNTER_CAN_ID 0x528

//ACU IDs

#define ACU_INFO_TX_1_CAN_ID 0x105

#define ACU_INFO_TX_2_CAN_ID 0x106


#define VCU_IS_CONNECTED_RX_CAN_ID 0x175

#define VCU_IS_CONNECTED_TX_CAN_ID 0x176

#define ACU_RELAY_STUCK_TX_CAN_ID 0x102

//Interface IDs

#define INTERFACE_IS_CONNECTED_CAN_ID 0x150

#define INTERFACE_VOLTAGES_CAN_ID 0x700

#define INTERFACE_TEMPERATURES_CAN_ID 0x701

#define INTERFACE_BMS_FAULT_CAN_ID 0x101

#define CHARGER_CURRENT_TO_INTERFACE_CAN_ID 0x102

//Charger IDs

#define CHARGER_TX_CAN_ID 0x1806E5F4

#define CHARGER_RX_CAN_ID 0x18ff50e5
/* USER CODE END Private defines */

void MX_FDCAN1_Init(void);
void MX_FDCAN2_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __FDCAN_H__ */

