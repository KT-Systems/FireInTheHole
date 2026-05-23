/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.c
  * @brief   This file provides code for the configuration
  *          of the FDCAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "fdcan.h"

/* USER CODE BEGIN 0 */
extern int flag;
/* USER CODE END 0 */

FDCAN_HandleTypeDef hfdcan1;
FDCAN_HandleTypeDef hfdcan2;

/* FDCAN1 init function */
void MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = ENABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = ENABLE;
  hfdcan1.Init.NominalPrescaler = 10;
  hfdcan1.Init.NominalSyncJumpWidth = 2;
  hfdcan1.Init.NominalTimeSeg1 = 13;
  hfdcan1.Init.NominalTimeSeg2 = 2;
  hfdcan1.Init.DataPrescaler = 1;
  hfdcan1.Init.DataSyncJumpWidth = 1;
  hfdcan1.Init.DataTimeSeg1 = 1;
  hfdcan1.Init.DataTimeSeg2 = 1;
  hfdcan1.Init.MessageRAMOffset = 0;
  hfdcan1.Init.StdFiltersNbr = 4;
  hfdcan1.Init.ExtFiltersNbr = 0;
  hfdcan1.Init.RxFifo0ElmtsNbr = 7;
  hfdcan1.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxFifo1ElmtsNbr = 0;
  hfdcan1.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxBuffersNbr = 0;
  hfdcan1.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.TxEventsNbr = 0;
  hfdcan1.Init.TxBuffersNbr = 0;
  hfdcan1.Init.TxFifoQueueElmtsNbr = 8;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan1.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */
  FDCAN_FilterTypeDef sFilterConfig;
  sFilterConfig.IdType       = FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex  = 0;
  sFilterConfig.FilterType   = FDCAN_FILTER_DUAL;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1    = INTERFACE_IS_CONNECTED_CAN_ID;
  sFilterConfig.FilterID2    = 0x611;
  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)  Error_Handler();

  sFilterConfig.IdType       = FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex  = 1;
  sFilterConfig.FilterType   = FDCAN_FILTER_DUAL;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1    = IVT_CURRENT_CAN_ID;
  sFilterConfig.FilterID2    = IVT_VOLTAGE_1_CAN_ID;
  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK) Error_Handler();

  sFilterConfig.IdType       = FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex  = 2;
  sFilterConfig.FilterType   = FDCAN_FILTER_DUAL;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1    = VCU_IS_CONNECTED_RX_CAN_ID;
  sFilterConfig.FilterID2    =  0x511;
  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK) Error_Handler();

  sFilterConfig.IdType       = FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex  = 3;
  sFilterConfig.FilterType   = FDCAN_FILTER_DUAL;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1    = IVT_WATTAGE_CAN_ID;
  sFilterConfig.FilterID2    = IVT_WATTAGE_CAN_ID;
  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK) Error_Handler();

  HAL_FDCAN_ConfigGlobalFilter(&hfdcan1,FDCAN_REJECT,FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);

  if(HAL_FDCAN_Start(&hfdcan1) != HAL_OK) Error_Handler ();

//  if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)  Error_Handler();

  /* USER CODE END FDCAN1_Init 2 */

}
/* FDCAN2 init function */
void MX_FDCAN2_Init(void)
{

  /* USER CODE BEGIN FDCAN2_Init 0 */

  /* USER CODE END FDCAN2_Init 0 */

  /* USER CODE BEGIN FDCAN2_Init 1 */

  /* USER CODE END FDCAN2_Init 1 */
  hfdcan2.Instance = FDCAN2;
  hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan2.Init.AutoRetransmission = ENABLE;
  hfdcan2.Init.TransmitPause = DISABLE;
  hfdcan2.Init.ProtocolException = ENABLE;
  hfdcan2.Init.NominalPrescaler = 20;
  hfdcan2.Init.NominalSyncJumpWidth = 2;
  hfdcan2.Init.NominalTimeSeg1 = 13;
  hfdcan2.Init.NominalTimeSeg2 = 2;
  hfdcan2.Init.DataPrescaler = 1;
  hfdcan2.Init.DataSyncJumpWidth = 1;
  hfdcan2.Init.DataTimeSeg1 = 1;
  hfdcan2.Init.DataTimeSeg2 = 1;
  hfdcan2.Init.MessageRAMOffset = 150;
  hfdcan2.Init.StdFiltersNbr = 0;
  hfdcan2.Init.ExtFiltersNbr = 1;
  hfdcan2.Init.RxFifo0ElmtsNbr = 1;
  hfdcan2.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.RxFifo1ElmtsNbr = 1;
  hfdcan2.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.RxBuffersNbr = 0;
  hfdcan2.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.TxEventsNbr = 0;
  hfdcan2.Init.TxBuffersNbr = 0;
  hfdcan2.Init.TxFifoQueueElmtsNbr = 0;
  hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan2.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN2_Init 2 */
  FDCAN_FilterTypeDef sFilterConfig;
  sFilterConfig.IdType       = FDCAN_EXTENDED_ID;
  sFilterConfig.FilterIndex  = 0;
  sFilterConfig.FilterType   = FDCAN_FILTER_MASK;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO1;
  sFilterConfig.FilterID1    = CHARGER_RX_CAN_ID;
  sFilterConfig.FilterID2    = 0x1FFFFFFF;
  if (HAL_FDCAN_ConfigFilter(&hfdcan2, &sFilterConfig) != HAL_OK)  Error_Handler();

  HAL_FDCAN_ConfigGlobalFilter(&hfdcan2,FDCAN_REJECT,FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);

  if(HAL_FDCAN_Start(&hfdcan2) != HAL_OK) Error_Handler ();

//  if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)  Error_Handler();
  /* USER CODE END FDCAN2_Init 2 */

}

static uint32_t HAL_RCC_FDCAN_CLK_ENABLED=0;

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspInit 0 */

  /* USER CODE END FDCAN1_MspInit 0 */
    /* FDCAN1 clock enable */
    HAL_RCC_FDCAN_CLK_ENABLED++;
    if(HAL_RCC_FDCAN_CLK_ENABLED==1){
      __HAL_RCC_FDCAN_CLK_ENABLE();
    }

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**FDCAN1 GPIO Configuration
    PD0     ------> FDCAN1_RX
    PD1     ------> FDCAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* FDCAN1 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
  /* USER CODE BEGIN FDCAN1_MspInit 1 */

  /* USER CODE END FDCAN1_MspInit 1 */
  }
  else if(fdcanHandle->Instance==FDCAN2)
  {
  /* USER CODE BEGIN FDCAN2_MspInit 0 */

  /* USER CODE END FDCAN2_MspInit 0 */
    /* FDCAN2 clock enable */
    HAL_RCC_FDCAN_CLK_ENABLED++;
    if(HAL_RCC_FDCAN_CLK_ENABLED==1){
      __HAL_RCC_FDCAN_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**FDCAN2 GPIO Configuration
    PB12     ------> FDCAN2_RX
    PB13     ------> FDCAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* FDCAN2 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN2_IT0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);
  /* USER CODE BEGIN FDCAN2_MspInit 1 */

  /* USER CODE END FDCAN2_MspInit 1 */
  }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

  /* USER CODE END FDCAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_FDCAN_CLK_ENABLED--;
    if(HAL_RCC_FDCAN_CLK_ENABLED==0){
      __HAL_RCC_FDCAN_CLK_DISABLE();
    }

    /**FDCAN1 GPIO Configuration
    PD0     ------> FDCAN1_RX
    PD1     ------> FDCAN1_TX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1);

    /* FDCAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
  /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

  /* USER CODE END FDCAN1_MspDeInit 1 */
  }
  else if(fdcanHandle->Instance==FDCAN2)
  {
  /* USER CODE BEGIN FDCAN2_MspDeInit 0 */

  /* USER CODE END FDCAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_FDCAN_CLK_ENABLED--;
    if(HAL_RCC_FDCAN_CLK_ENABLED==0){
      __HAL_RCC_FDCAN_CLK_DISABLE();
    }

    /**FDCAN2 GPIO Configuration
    PB12     ------> FDCAN2_RX
    PB13     ------> FDCAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* FDCAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(FDCAN2_IT0_IRQn);
  /* USER CODE BEGIN FDCAN2_MspDeInit 1 */

  /* USER CODE END FDCAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
uint8_t canFlag = 0;
uint8_t ivtByteZero = 0;
uint8_t canArray[8];
uint8_t mphkeCan;
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hcan, uint32_t RxFifo0ITs)
{
 if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) == RESET) return;
  if (HAL_FDCAN_GetRxMessage(hcan, FDCAN_RX_FIFO0, &canData.RxHeader, canData.RxData) != HAL_OK) Error_Handler();

  // Isabellen Current Data is stored and checked for overcurrent.
  // It also resets the timer for Isabellen disconnecting.
  // Also I do SCS digital check that i receive the correct messages from IVT.

//  if(canData.RxHeader.ExtId == CHARGER_RX_CAN_ID && canData.RxHeader.IDE == CAN_ID_EXT) {
//	  canFlag++;
//
//	  charger.isConnected = CONNECTED;
//	  charger.timeOutTimer->Instance->CNT = TIMER_RESET;
//	  charger.voltageAtChargerTimes10 = (canData.RxData[0] << 8) + canData.RxData[1];
//	  charger.currentAtChargerTimes10 = (canData.RxData[2] << 8) + canData.RxData[3];
//	  charger.statusFlag = canData.RxData[4];
//	  return;
//  }

 if(canData.RxHeader.Identifier == IVT_CURRENT_CAN_ID && canData.RxHeader.IdType == FDCAN_STANDARD_ID && hcan == &hfdcan1){
  	  ivt.current = ((canData.RxData[2] << 24) | (canData.RxData[3] << 16) | (canData.RxData[4] << 8) | canData.RxData[5]) / 1000.0;
  	  ivt.timeOutTimer->Instance->CNT = TIMER_RESET;
  	  ivt.isConnected = CONNECTED;
  	  if(canData.RxData[1] != ivt.counterCheck){
  		  ivt.counterCheck = canData.RxData[1];
  		  ivt.SCSErrors++;
  	  }
  	  else ivt.SCSErrors = ERROR_RESET;
  	  ivt.counterCheck++;
  	  return;
  }

  // It takes the charging current and the charging command from the user interface.
  // It also serves as a keep-alive message to detect whether interface is connected.
  else if(canData.RxHeader.Identifier == INTERFACE_IS_CONNECTED_CAN_ID) {
	  mphkeCan++;
	  bms.interfaceIsConnected = CONNECTED;
	  bms.stopDisplayingTimer->Instance->CNT = TIMER_RESET;
	  charger.wantedCurrentTimes10 = canData.RxData[0] - 100;
	  charger.wantedOff = canData.RxData[1] & 0x1;
	  bms.cellBalancingIsWanted = canData.RxData[1] >> 4;

  }
  // It stores Voltage 1 of Isabellen.
  else if(canData.RxHeader.Identifier == IVT_VOLTAGE_1_CAN_ID) {
	  ivtByteZero = canData.RxData[1];
  	  ivt.timeOutTimer->Instance->CNT = TIMER_RESET;
	  ivt.voltage1 = ((canData.RxData[2] << 24) | (canData.RxData[3] << 16) | (canData.RxData[4] << 8) | canData.RxData[5]) / 1000.0;
  }
  else if(canData.RxHeader.Identifier == 0x511) {
	//  canFlag++;
	  for(int i = 0; i < 8; i++) canArray[i] = canData.RxData[i];

  }


  // It stores Voltage 2 of Isabellen.
//  else if(canData.RxHeader.StdId == IVT_VOLTAGE_2_CAN_ID) ivt.voltage2 = ((canData.RxData[2] << 24) | (canData.RxData[3] << 16) | (canData.RxData[4] << 8) | canData.RxData[5]) / 1000.0;
//  // It stores Voltage 3 of Isabellen.
//
//  else if(canData.RxHeader.StdId == IVT_VOLTAGE_3_CAN_ID) ivt.voltage3 = ((canData.RxData[2] << 24) | (canData.RxData[3] << 16) | (canData.RxData[4] << 8) | canData.RxData[5]) / 1000.0;

  // It stores wattage of Isabellen.
  else if(canData.RxHeader.Identifier == IVT_WATTAGE_CAN_ID){
  	  ivt.timeOutTimer->Instance->CNT = TIMER_RESET;
	  ivt.wattage = (canData.RxData[2] << 24) | (canData.RxData[3] << 16) | (canData.RxData[4] << 8) | canData.RxData[5];
  }

  // It starts the precharge action from the button in Dashboard. VCU reads the buttons state and sends it through canBus.
//  else if(canData.RxHeader.StdId == START_PRECHARGE_CAN_ID) acu.startPrecharge = 1;

  // It detects the charger and takes data from him.
//  // It also serves as a keep-alive message to detect whether charger is connected. Will need to take it to Fifo1MsgPendingCallback when seperate CAN is used.
//  else if(canData.RxHeader.ExtId == CHARGER_RX_CAN_ID && canData.RxHeader.IDE == CAN_ID_EXT) {
//	  flag++;
//	  charger.isConnected = CONNECTED;
//	  charger.timeOutTimer->Instance->CNT = TIMER_RESET;
//	  charger.voltageAtChargerTimes10 = (canData.RxData[0] << 8) + canData.RxData[1];
//	  charger.currentAtChargerTimes10 = (canData.RxData[2] << 8) + canData.RxData[3];
//	  charger.statusFlag = canData.RxData[4];
//	  return;
//  }

  // Message from VCU to know if accumulator is connected. It deletes some tasks whether is connected or not.
  else if(canData.RxHeader.Identifier == VCU_IS_CONNECTED_RX_CAN_ID){// APO VCU
	  bms.vcuIsConnected = CONNECTED;

	  canData.stdTxHeader.Identifier = VCU_IS_CONNECTED_TX_CAN_ID;
	  canData.stdTxHeader.IdType               = FDCAN_STANDARD_ID;           // IDE = CAN_ID_STD
	  canData.stdTxHeader.TxFrameType          = FDCAN_DATA_FRAME;            // RTR = CAN_RTR_DATA
	  canData.stdTxHeader.DataLength           = FDCAN_DLC_BYTES_1;
	  canData.stdTxHeader.ErrorStateIndicator =  FDCAN_ESI_ACTIVE;
	  canData.stdTxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	  canData.stdTxHeader.MessageMarker = 0;
	  canData.stdTxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	  canData.stdTxHeader.BitRateSwitch = FDCAN_BRS_OFF;

	  canData.TxData[0] = 1;
	  if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &canData.stdTxHeader, canData.TxData) != HAL_OK) Error_Handler();
  }

  else if (canData.RxHeader.Identifier == IVT_CURRENT_COUNTER_CAN_ID) {
	  ivt.timeOutTimer->Instance->CNT = TIMER_RESET;
	  ivt.currentCounter = (canData.RxData[2] << 24) | (canData.RxData[3] << 16) | (canData.RxData[4] << 8) | canData.RxData[5];
	    }
  else if (canData.RxHeader.Identifier == IVT_WATTAGE_COUNTER_CAN_ID) {
	  ivt.timeOutTimer->Instance->CNT = TIMER_RESET;
	  ivt.wattageCounter = (canData.RxData[2] << 24) | (canData.RxData[3] << 16) | (canData.RxData[4] << 8) | canData.RxData[5];

  }
}
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hcan, uint32_t RxFifo1ITs)
{
	if((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) == RESET) return;
	canFlag++;
	if (HAL_FDCAN_GetRxMessage(hcan, FDCAN_RX_FIFO1, &canData.RxHeader, canData.RxData) != HAL_OK) Error_Handler();


	if(canData.RxHeader.Identifier == CHARGER_RX_CAN_ID && canData.RxHeader.IdType     == FDCAN_EXTENDED_ID) {
	//	canFlag++;
		charger.isConnected = CONNECTED;
		charger.timeOutTimer->Instance->CNT = TIMER_RESET;
		charger.voltageAtCharger = ((canData.RxData[0] << 8) + canData.RxData[1]) / 10.0;
		charger.currentAtCharger = ((canData.RxData[2] << 8) + canData.RxData[3]) /10.0;
		charger.statusFlag = canData.RxData[4];
		return;
	}

}
/* USER CODE END 1 */
