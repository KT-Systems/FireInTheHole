/*
 * initFunctions.c
 *
 *  Created on: Mar 19, 2024
 *      Author: kara
 */
#include "main.h"
#include "math.h"




volatile float socPercent = 0.0f;
volatile float remainingAh = 0.0f;
static uint64_t lastChargeAs = 0;
static uint64_t lastDischargeAs = 0;

uint8_t CANFlag = 0;


/**
*******************************************************************************
* @brief function that implements all error checks on our system and sends it
* to user interface if connected
*******************************************************************************
*/

void checkErrors(uint8_t tIC, BMSData *_bms, IsabellenData *_ivt, ACUData *_acu, FDCAN_HandleTypeDef *_hcan){

	float temporaryCurrentCellVoltage;
	float temporaryCurrentCellTemperature;
	float temporaryPackVoltage = 0;
	firstLoopEnterState firstSegmentLostFlag = TO_ENTER;
	uint8_t temporarymaxVoltageCellID;
	uint8_t temporaryminVoltageCellID;
	uint8_t temporarymaxTemperatureCellID;

	_bms->maxVoltageCell.val = 0;
	_bms->minVoltageCell.val = 5;
	_bms->maxCellTemp.val = -10;

	for(uint8_t cic = 0; cic < tIC; cic++){
		for(uint8_t cid = START_MEASURE_CELL; cid < STOP_MEASURE_CELL; cid++){
			temporaryCurrentCellVoltage = callibrateBMSVoltage(getVoltage(_bms->bmsIC[cic].acell.ac_codes[cid]), cic);

//			temporaryCurrentCellVoltage = getVoltage(_bms->bmsIC[cic].acell.ac_codes[cid]);

			_bms->voltages[cic][cid] = temporaryCurrentCellVoltage;//For Displaying reasons

			// Finds minimum voltage measurement
			if(temporaryCurrentCellVoltage < _bms->minVoltageCell.val){
				_bms->minVoltageCell.val = temporaryCurrentCellVoltage;
				temporaryminVoltageCellID = cic * 12 + cid;
			}

			// Finds maximum voltage measurement
			if(temporaryCurrentCellVoltage > _bms->maxVoltageCell.val){
				_bms->maxVoltageCell.val = temporaryCurrentCellVoltage;
				temporarymaxVoltageCellID = cic * 12 + cid;
			}
			// Error checking. If overvoltage or undervoltage, raises an error to that specific cell.
			// If the current error of any cell is more thatn the accepted errors, general error on BMS is raised.
			if((temporaryCurrentCellVoltage > _bms->OVThreshold) || (temporaryCurrentCellVoltage < _bms->UVThreshold)) _bms->voltageErrorFlags[cic][cid]++;
			else _bms->voltageErrorFlags[cic][cid] = ERROR_RESET;// If error is reseted, the value of error in that cell is set back to zero.

			// Calculates voltage of the pack.
			temporaryPackVoltage += temporaryCurrentCellVoltage; //Read VPV instead. Tried it but didnt work well for some reason
		}
		for(uint8_t cidTemp = 0; cidTemp < TOTAL_ID_TEMP; cidTemp++){

			temporaryCurrentCellTemperature = lookUpTable(_bms->bmsIC[cic].aux.a_codes[cidTemp]);
			_bms->temperatures[cic][cidTemp] = temporaryCurrentCellTemperature;//For Displaying reasons
			// Finds maximum temperature.
			if(temporaryCurrentCellTemperature > _bms->maxCellTemp.val){
				_bms->maxCellTemp.val = temporaryCurrentCellTemperature;
				temporarymaxTemperatureCellID = cic * 10 + cidTemp;
			}

			// Error checking. If overtemperature or undertemperature, raises an error to that specific cell.
			// If the current error of any cell is more that the accepted errors, general error on BMS is raised.
			if(temporaryCurrentCellTemperature > _bms->OTThreshold || temporaryCurrentCellTemperature < _bms->UTThreshold) {
				_bms->tempErrorFlags[cic][cidTemp]++;
			}
			else _bms->tempErrorFlags[cic][cidTemp] = ERROR_RESET;// If error is fixed, the value of error in that cell is set back to zero.
		}


		//		_bms->packVoltage = 25*getVoltage(_bms->bmsIC[cic].aux.a_codes[11]);// not tested. Maybe compare this to the sum of the all the cells to check if measurements are correct.

		// Multiple Internals Variables such as Vref2, Vdigital , Vanalog ,ITMP Temp.
		_bms->internalDieTemperature[cic] = (getVoltage(_bms->bmsIC[cic].stata.itmp) / 0.00752) - 273;
		if(_bms->internalDieTemperature[cic] > _bms->ITMPThreshold ||
			_bms->bmsIC[cic].statb.vr4k < 9667 || // 2.95 Volts
			_bms->bmsIC[cic].statb.vr4k > 10100 ||// 3.015 Volts
			_bms->bmsIC[cic].statb.vd < 8000 ||	  // 2.7 Volts
			_bms->bmsIC[cic].statb.vd > 14000 ||  // 3.6 Volts
			_bms->bmsIC[cic].statb.va < 20000 ||  // 4.5 Volts
			_bms->bmsIC[cic].statb.va > 26667) _bms->internalVoltagesErrorFlags[cic]++; // 5.5 Volts
		else _bms->internalVoltagesErrorFlags[cic] = 0;
	}
	_bms->packVoltage = temporaryPackVoltage;
	_bms->minVoltageCell.id = temporaryminVoltageCellID;
	_bms->maxVoltageCell.id = temporarymaxVoltageCellID;
	_bms->maxCellTemp.id = temporarymaxTemperatureCellID;
	_bms->voltagesHaveError = ERROR_RESET;
	_bms->tempsHaveError = ERROR_RESET;
	firstSegmentLostFlag = TO_ENTER;
	_bms->isoSPIHasError = ERROR_RESET;
	_bms->firstSegmentLostCommunication = 0;
	_bms->internalVoltagesHaveError = ERROR_RESET;
	for(uint8_t cic = 0; cic < tIC; cic++){
		for(uint8_t cid = START_MEASURE_CELL; cid < STOP_MEASURE_CELL; cid++) if(_bms->voltageErrorFlags[cic][cid] > 2 * _bms->acceptedErrors) {
			// If more than the accepted errors occured, It raises error to the BMS.
			_bms->voltagesHaveError = ERROR_TRIGGERED;
		}
		for(uint8_t cidTemp = 0; cidTemp < TOTAL_ID_TEMP; cidTemp++) if(_bms->tempErrorFlags[cic][cidTemp] >  2 * 2 * _bms->acceptedErrors) {
			// If more than the accepted errors occured, It raises error to the BMS.
			_bms->tempsHaveError = ERROR_TRIGGERED; // Change it to error triggered !
		}

		if(_bms->internalVoltagesErrorFlags[cic] > _bms->acceptedErrors) _bms->internalVoltagesHaveError = ERROR_RESET;

		if(_bms->bmsIC[cic].cccrc.acell_pec){// Detects ISO-SPI Failure.
			_bms->isoSPIHasError = ERROR_TRIGGERED;
			if(firstSegmentLostFlag){
				firstSegmentLostFlag = ENTERED;
				_bms->firstSegmentLostCommunication = cic;
			}
		}
	}
	// Error checking for isabellen. If Isabellen is disconnected or overcurrents or SCS fails, general error on BMS is raised.
	if(!_ivt->isConnected || _ivt->current > _acu->overCurrentThreshold || _ivt->SCSErrors > _ivt->SCSacceptedErrors) _ivt->hasError = ERROR_TRIGGERED;//change it to ERROR_TRIGERED when ivt is connected.
	else _ivt->hasError = ERROR_RESET;// If error is resetted, the value of error in that cell is set back to zero.

	if(_ivt->hasError || _bms->voltagesHaveError || _bms->tempsHaveError || _bms->internalVoltagesHaveError || _bms->voltageMeasurementError) _bms->hasError = ERROR_TRIGGERED;
	else _bms->hasError = ERROR_RESET;

	  // AIRPLUS IS STUCK DETECTION
	if(_acu->airPlusAux.state != _acu->airPlusSupply.state) _acu->airPlusIsStuckFlag++; //Air Minus is stucked (Thn gamhsame)
	else _acu->airPlusIsStuckFlag = 0;

	if(_acu->airPlusIsStuckFlag > _acu->airsStuckAcceptedErrors) _acu->airPlusIsStuck = RELAY_STUCK;
	else _acu->airPlusIsStuck = RELAY_NOT_STUCK;

	  // AIRMINUS IS STUCK DETECTION
	if(_acu->airMinusAux.state != _acu->airMinusSupply.state) _acu->airMinusIsStuckFlag++; //Air Plus is stucked (Thn gamhsame)
	else _acu->airMinusIsStuckFlag = 0;

	if(_acu->airMinusIsStuckFlag > _acu->airsStuckAcceptedErrors) _acu->airMinusIsStuck = RELAY_STUCK;
	else _acu->airMinusIsStuck = RELAY_NOT_STUCK;

//	if((_acu->airMinusIsStuck || _acu->airPlusIsStuck)) {
//		CANData airsCANData;
//		airsCANData.stdTxHeader.IDE = CAN_ID_STD;
//		airsCANData.stdTxHeader.StdId = ACU_RELAY_STUCK_TX_CAN_ID;
//		airsCANData.stdTxHeader.RTR = CAN_RTR_DATA;
//		airsCANData.stdTxHeader.DLC = 1;
//		airsCANData.TxData[0] = _acu->airMinusIsStuck || _acu->airPlusIsStuck;
//		if(HAL_CAN_AddTxMessage(_hcan, &airsCANData.stdTxHeader, airsCANData.TxData, &airsCANData.TxMailbox) != HAL_OK) Error_Handler();
//	}

    if(_bms->hasError) {
    	// Sends hardware signal to reset latching system.
    	HAL_GPIO_WritePin(_bms->isOK.group, _bms->isOK.pin, GPIO_PIN_RESET);//Default : RESET
//    	HAL_GPIO_WritePin(_bms->isOK.group, _bms->isOK.pin, GPIO_PIN_SET);//Default : RESET


    	// If user interface is connected, send message to display the error that occured (only once)
    	if(_bms->interfaceIsConnected && _bms->userInterfaceShowErrorFlag){
    		CANData _canData;
    		_bms->userInterfaceShowErrorFlag = ENTERED;
			_canData.stdTxHeader.Identifier = INTERFACE_BMS_FAULT_CAN_ID;
    		_canData.stdTxHeader.IdType = FDCAN_STANDARD_ID;
    		_canData.stdTxHeader.TxFrameType = FDCAN_DATA_FRAME;
    		_canData.stdTxHeader.DataLength = FDCAN_DLC_BYTES_1;
    		_canData.stdTxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    		_canData.stdTxHeader.BitRateSwitch = FDCAN_BRS_OFF;
    		_canData.stdTxHeader.FDFormat = FDCAN_CLASSIC_CAN;
    		_canData.stdTxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    		_canData.stdTxHeader.MessageMarker = 0;
    		if(_bms->voltagesHaveError) _canData.TxData[0] = 1;// Voltages Fault
    		else if(_bms->tempsHaveError) _canData.TxData[0] = 2;// Temperatures Fault
    		else if(_ivt->hasError) _canData.TxData[0] = 3;// Current Sensor Fault
    		else _canData.TxData[0] = 4; // Generic Fault
    		if(_bms->isoSPIHasError) _canData.TxData[0] = 0; //ISOSPI Fault
    		for(int i = 0; i < 1; i++){// Sends multiple messages in case any is lost
    		osDelay(5);
    		if (HAL_FDCAN_AddMessageToTxFifoQ(_hcan, &_canData.stdTxHeader, _canData.TxData) != HAL_OK) Error_Handler();
    		}
    	}
    }
    else{
    	// Resets the hardware signal to reset latching system. The user now has to hardware reset our BMS. Rules compliant.
    	// Also resets the flag to user interface show error.
    	_bms->userInterfaceShowErrorFlag = TO_ENTER;
    	HAL_GPIO_WritePin(_bms->isOK.group, _bms->isOK.pin, GPIO_PIN_SET);
    }
}

/**
*******************************************************************************
* @brief function that converts voltage to integer values of IC
*******************************************************************************
*/

uint8_t calcCheckSum(uint8_t temp[8], uint8_t length){
	uint8_t sum = 0;
	for(int i = 0; i < length; i++) sum += temp[i];
	return sum;
}
/**
*******************************************************************************
* @brief function that checks if checksum is correct
*******************************************************************************
*/

uint8_t checkCheckSum(uint8_t temp[8], uint8_t length, uint8_t checkSumByte, ACUData *_acu){


	if(calcCheckSum(temp, length) != checkSumByte) return 1;
	else return 0;
}
/**
*******************************************************************************
* @brief Initializes the Vicor structure that contains data about our DCDC
* Management implementation
*******************************************************************************
*/

extern I2C_HandleTypeDef hi2c1;
HAL_StatusTypeDef VicorInit(VicorData *_vicor){

	_vicor->vicorI2C = &hi2c1;

	_vicor->voltageIn = 0;// High side voltage of DCDC
	_vicor->voltageOut = 0;// Low side voltage of DCDC

	_vicor->wantedOff = 0;

	_vicor->currentIn = 0;// High side current of DCDC
	_vicor->currentOut = 0;// Low side current of DCDC

	_vicor->temperature = 0;// Temperature of DCDC

	_vicor->vicorSlaveAddress = 0x51 ;

	HAL_I2C_IsDeviceReady(&hi2c1,
	                      _vicor->vicorSlaveAddress << 1,
	                      5,
	                      100);
return HAL_OK;
}
/**
*******************************************************************************
* @brief Read Data for Vicor DCDC
*******************************************************************************
*/
HAL_StatusTypeDef readVicorData(VicorData *_vicor, vicorCommands cmd){
	uint8_t tmp[2];
	HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(_vicor->vicorI2C, _vicor->vicorSlaveAddress << 1, cmd, 1, tmp, 2, 5);
	switch((uint8_t)cmd){
	case VICOR_INPUT_VOLTAGE:
		_vicor->voltageIn = ((tmp[1] << 8) + tmp[0]) / 10.0;
	break;
	case VICOR_INPUT_CURRENT:
		_vicor->currentIn = ((tmp[1] << 8) + tmp[0]) / 1000.0;
	break;
	case VICOR_OUTPUT_VOLTAGE:
		_vicor->voltageOut = ((tmp[1] << 8) + tmp[0]) / 10.0;
	break;
	case VICOR_OUTPUT_CURRENT:
		_vicor->currentOut = ((tmp[1] << 8) + tmp[0]) / 100.0;
	break;
	case VICOR_TEMPERATURE:
		_vicor->temperature = (tmp[1] << 8) + tmp[0];
	break;
	case VICOR_OUTPUT_WATTAGE:
		_vicor->wattageOut = (tmp[1] << 8) + tmp[0];
	default:
	break;
	}
	return ret;
}

/**
*******************************************************************************
* @brief Read all wanted data for Vicor DCDC
*******************************************************************************
*/
//extern I2C_HandleTypeDef hi2c1;
HAL_StatusTypeDef updateVicorData(VicorData *_vicor){
//	readVicorData(_vicor, VICOR_INPUT_VOLTAGE);
//	osDelay(1);
	readVicorData(_vicor, VICOR_INPUT_CURRENT);
//	osDelay(1);
//	readVicorData(_vicor, VICOR_OUTPUT_VOLTAGE);
	osDelay(1);
	readVicorData(_vicor, VICOR_OUTPUT_CURRENT);
	osDelay(1);
	readVicorData(_vicor, VICOR_TEMPERATURE);
	osDelay(1);
	readVicorData(_vicor, VICOR_OUTPUT_WATTAGE);

	return HAL_OK;
}
void writeVicorPage(VicorData *_vicor, uint8_t page) {
	uint8_t buffer[2] = {VICOR_CMD_PAGE, page};
	HAL_I2C_Master_Transmit(_vicor->vicorI2C, _vicor->vicorSlaveAddress << 1, buffer, 2, I2C_TIMEOUT);
}
void clearVicorFaults(VicorData *_vicor) {
    uint8_t buffer[1] = {VICOR_CMD_CLEAR_FAULTS};
    HAL_I2C_Master_Transmit(_vicor->vicorI2C, _vicor->vicorSlaveAddress << 1, buffer, 1, I2C_TIMEOUT);
}

//static HAL_StatusTypeDef pmbus_read(uint8_t cmd, uint8_t *buffer, uint8_t nbytes) {
//    const uint8_t address = 0x51 << 1;
//    const uint8_t cmd_size = 1;
//    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c1, address, cmd, cmd_size, buffer, nbytes, I2C_TIMEOUT*100);
//    return status;
//}
//
//static HAL_StatusTypeDef pmbus_write(uint8_t cmd, uint8_t *buffer) {
//    const uint8_t address = 0x51 << 1;
//    const uint8_t cmd_size = 1;
//    const uint16_t buff_size = sizeof(buffer);
//    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c1, address, cmd, cmd_size, buffer, buff_size, I2C_TIMEOUT*10);
//    return status;
//}
//void write_page(uint8_t value) {
//	const uint8_t address = 0x51 << 1;
//	uint8_t buffer[2] = {VICOR_CMD_PAGE, value};
//	HAL_I2C_Master_Transmit(&hi2c1, address, buffer, 2, I2C_TIMEOUT);
//}
//void clear_faults() {
//    uint8_t buffer[1] = {VICOR_CMD_CLEAR_FAULTS};
//    const uint8_t address = DEVICE_ADDRESS << 1;
//    HAL_I2C_Master_Transmit(&hi2c1, address, buffer, 1, I2C_TIMEOUT);
//}
//uint8_t operation = 2;
//HAL_StatusTypeDef read_operation() {
//	uint8_t buffer[1];
//	HAL_StatusTypeDef status = pmbus_read(VICOR_CMD_OPERATION, buffer, 1);
//	if (status == HAL_OK)
//	{
//		operation = buffer[0];
//		return HAL_OK;
//	}
//	return status;
//}
/**
*******************************************************************************
* @brief Initializes the Isabellenhuete structure that contains data about
* our current and voltage sensor.
*******************************************************************************
*/
HAL_StatusTypeDef IVTInit(IsabellenData *_ivt, TIM_HandleTypeDef *_timeOutTimer, uint8_t _SCSacceptedErrors){

	// Variables for SCS checks.
	_ivt->SCSacceptedErrors = _SCSacceptedErrors;
	_ivt->SCSErrors = ERROR_RESET;
	_ivt->counterCheck = 0;

	// Variables for state detection of Isabellen.
	_ivt->isConnected = ERROR_RESET;
	_ivt->hasError = ERROR_RESET;

	// Variable for storing current of Isabellen.
	_ivt->current = -1;

	// Variables for storing voltages of Isabellen.
	_ivt->voltage1 = -1;
	_ivt->voltage2 = -1;
	_ivt->voltage3 = -1;
	_ivt->wattage = 0;

	//SoC
	_ivt->chargingAs = 0;
	_ivt->dischargingAs = 0;

	_ivt->currentCounter = 0;
	_ivt->wattageCounter = 0;
	// Timer to detect if Isabellen is disconnected.
	_ivt->timeOutTimer =_timeOutTimer;

	// Initializes the timeout Timer.
	return HAL_TIM_Base_Start_IT(_timeOutTimer);
}

/**
*******************************************************************************
* @brief Changes mode of IVT
* STOP = 0x0
* RUN = 0x1
*******************************************************************************
*/
void IVTChangeMode(FDCAN_HandleTypeDef *_hcan, ivtMode mode){
	  canData.stdTxHeader.IdType = FDCAN_STANDARD_ID;
	  canData.stdTxHeader.Identifier = IVT_MESSAGE_COMMAND_CAN_ID;//0x201
	  canData.stdTxHeader.TxFrameType = FDCAN_DATA_FRAME;
	  canData.stdTxHeader.DataLength = FDCAN_DLC_BYTES_8;
	  canData.stdTxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	  canData.stdTxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	  canData.stdTxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	  canData.stdTxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	  canData.stdTxHeader.MessageMarker = 0;
	  canData.TxData[0] = 0x34;
	  canData.TxData[1] = mode;
	  canData.TxData[2] = 0x01;
	  canData.TxData[3] = 0x00;
	  canData.TxData[4] = 0x00;
	  canData.TxData[5] = 0x00;
	  canData.TxData[6] = 0x00;
	  canData.TxData[7] = 0x00;
		if(HAL_FDCAN_AddMessageToTxFifoQ(_hcan, &canData.stdTxHeader, canData.TxData) != HAL_OK)	Error_Handler();
}

/**
 *******************************************************************************
 * @briefs store the settings we have send to IVT.
 *******************************************************************************
 */
void IVTStoreSettings(FDCAN_HandleTypeDef *_hcan){

	  canData.stdTxHeader.IdType = FDCAN_STANDARD_ID;
	  canData.stdTxHeader.Identifier = IVT_MESSAGE_COMMAND_CAN_ID;//0x201
	  canData.stdTxHeader.TxFrameType = FDCAN_DATA_FRAME;
	  canData.stdTxHeader.DataLength = FDCAN_DLC_BYTES_8;
	  canData.stdTxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	  canData.stdTxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	  canData.stdTxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	  canData.stdTxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	  canData.stdTxHeader.MessageMarker = 0;
	  canData.TxData[0] = 0x32;
	  canData.TxData[1] = 0x00;
	  canData.TxData[2] = 0x00;
	  canData.TxData[3] = 0x00;
	  canData.TxData[4] = 0x00;
	  canData.TxData[5] = 0x00;
	  canData.TxData[6] = 0x00;
	  canData.TxData[7] = 0x00;
	  if(HAL_FDCAN_AddMessageToTxFifoQ(_hcan, &canData.stdTxHeader, canData.TxData) != HAL_OK)	Error_Handler();
}
/**
 *******************************************************************************
 * @briefs configs IVT Measurements
 *******************************************************************************
 */

void IVTMeasurementConfig(FDCAN_HandleTypeDef *_hcan, ivtVariable measurement, uint16_t time){

	  IVTChangeMode(_hcan, 0);
	  osDelay(100);
	  canData.stdTxHeader.IdType = FDCAN_STANDARD_ID;
	  canData.stdTxHeader.Identifier = IVT_MESSAGE_COMMAND_CAN_ID;//0x201
	  canData.stdTxHeader.TxFrameType = FDCAN_DATA_FRAME;
	  canData.stdTxHeader.DataLength = FDCAN_DLC_BYTES_8;
	  canData.stdTxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	  canData.stdTxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	  canData.stdTxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	  canData.stdTxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	  canData.stdTxHeader.MessageMarker = 0;
	  canData.TxData[0] = measurement;
	  if(time == 1) canData.TxData[1] = 1;
	  else canData.TxData[1] = 2;
	  canData.TxData[2] = time >> 8;
	  canData.TxData[3] = time;
	  canData.TxData[4] = 0x00;
	  canData.TxData[5] = 0x00;
	  canData.TxData[6] = 0x00;
	  canData.TxData[7] = 0x00;
	  if(HAL_FDCAN_AddMessageToTxFifoQ(_hcan, &canData.stdTxHeader, canData.TxData) != HAL_OK)	Error_Handler();
	  osDelay(10);
	  IVTStoreSettings(_hcan);
//	  osDelay(100);
//	  IVTChangeMode(_hcan, 1);
}


void IVTRestartToDefaults(FDCAN_HandleTypeDef *_hcan){

	  IVTChangeMode(_hcan, 0);
	  osDelay(100);
	  canData.stdTxHeader.IdType = FDCAN_STANDARD_ID;
	  canData.stdTxHeader.Identifier = IVT_MESSAGE_COMMAND_CAN_ID;//0x201
	  canData.stdTxHeader.TxFrameType = FDCAN_DATA_FRAME;
	  canData.stdTxHeader.DataLength = FDCAN_DLC_BYTES_8;
	  canData.stdTxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	  canData.stdTxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	  canData.stdTxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	  canData.stdTxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	  canData.stdTxHeader.MessageMarker = 0;
	  canData.TxData[0] = 0x3d;
	  canData.TxData[1] = 0x00;
	  canData.TxData[2] = 0x00;
	  canData.TxData[3] = 0x00;
	  canData.TxData[4] = 0x00;
	  canData.TxData[5] = 0x00;
	  canData.TxData[6] = 0x00;
	  canData.TxData[7] = 0x00;

	  if(HAL_FDCAN_AddMessageToTxFifoQ(_hcan, &canData.stdTxHeader, canData.TxData) != HAL_OK)	Error_Handler();

	return;
}
/**
*******************************************************************************
* @brief Sets bitrate to ivt and restarts it.
* bitrate = 0x08 -> 250kbit/s 1
* bitrate = 0x04 -> 500kbit/s 1
* bitrate = 0x02 -> 1000kbit/s 1
*******************************************************************************
*/

void IVTRestartToBitrate(FDCAN_HandleTypeDef *_hcan, ivtBaudRate bitrate){
//	  CANData canData;

	  IVTChangeMode(_hcan, 0);

	  osDelay(100);
	  canData.stdTxHeader.IdType = FDCAN_STANDARD_ID;
	  canData.stdTxHeader.Identifier = IVT_MESSAGE_COMMAND_CAN_ID;//0x201
	  canData.stdTxHeader.TxFrameType = FDCAN_DATA_FRAME;
	  canData.stdTxHeader.DataLength = FDCAN_DLC_BYTES_8;
	  canData.stdTxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	  canData.stdTxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	  canData.stdTxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	  canData.stdTxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	  canData.stdTxHeader.MessageMarker = 0;
	  canData.TxData[0] = 0x3a;
	  canData.TxData[1] = bitrate;
	  canData.TxData[2] = 0x00;
	  canData.TxData[3] = 0x00;
	  canData.TxData[4] = 0x00;
	  canData.TxData[5] = 0x00;
	  canData.TxData[6] = 0x00;
	  canData.TxData[7] = 0x00;

	  if(HAL_FDCAN_AddMessageToTxFifoQ(_hcan, &canData.stdTxHeader, canData.TxData) != HAL_OK)	Error_Handler();
}


/**
*******************************************************************************
* @brief Initializes the Charger structure that contains data about our Elcon
* Charger and the process of charging
*******************************************************************************
*/
HAL_StatusTypeDef ChargerInit(ChargerData *_charger, TIM_HandleTypeDef *_timeOutTimer){

	// Variables that are sent to charger. They are multiplied with 10 because the charger wants it that way.
	_charger->wantedCurrentTimes10 = 0;// Seting it from the user interface. Units 0.1 Ampere.
	_charger->wantedVoltageTimes10 = MAX_CHARGING_VOLTAGE * 10;// Default: 590 Volt. Units 0.1 Volts.

	// Variable to control if the charging should begin.
	_charger->wantedOff = 1; // 1 is Charging disabled and 0 is Charging enabled.

	// Variables from Charger. Also multiplied with 10.
	_charger->currentAtCharger = 0;
	_charger->voltageAtCharger = 0;

	// Timer to detect if charger is connected.
	_charger->timeOutTimer = _timeOutTimer;

	// Flag used to detect if charger is connected.
	_charger->isConnected = DISCONNECTED;


	// Errors coming from charger.
	_charger->statusFlag = 1;
	_charger->hardwareFailure = ERROR_TRIGGERED;
	_charger->overTempFailure = ERROR_TRIGGERED;
	_charger->voltageFailure = ERROR_TRIGGERED;
	_charger->detectsPackFailure = ERROR_TRIGGERED;
	_charger->commFailure = ERROR_TRIGGERED;

	// Initializes the time out timer.
	return HAL_TIM_Base_Start_IT(_timeOutTimer);;
}

/**
*******************************************************************************
* @brief Initializes the BMS structure that contains data about our Battery
* Management System implementation
*******************************************************************************
*/


HAL_StatusTypeDef BMSInit(BMSData *_bms, TIM_HandleTypeDef *_stopDisplayingTimer,
	TIM_HandleTypeDef * _communicationStartTimer, uint8_t _acceptedErrors,
	float _maxDiffbetweenCells, float _minVoltageBalancingIsEnabled, float _maxVoltageBalancingIsEnabled,
	float _overVoltageThreshold, float _underVoltageThreshold,
	float _OverTempThreshold, float _UnderTempThreshold){

	for(int cic = 0; cic < TOTAL_IC; cic++) for(int cid = 0; cid < TOTAL_ID_TEMP; cid++) _bms->DischargingCells[cic][cid] = 0;

	// Pin definitions

	// This pin is used to send the signal to hardware reset latch.
	_bms->isOK.pin = AMS_OK_Output_Pin;
	_bms->isOK.group = AMS_OK_Output_GPIO_Port;

	// This pin is from hardware BMS reset latch.
	_bms->latchedError.pin = AMS_Latched_Input_Pin;
	_bms->latchedError.group = AMS_Latched_Input_GPIO_Port;

	// Flags for multiple state detections
	_bms->voltageMeasurementError = ERROR_RESET;

	_bms->hasError = ERROR_RESET;// Flag that is raised when bms has error.

	_bms->voltagesHaveError = ERROR_RESET;// Flag that raises when voltages have error

	_bms->tempsHaveError = ERROR_RESET;// Flag that raises when temperatures have error

	_bms->internalVoltagesHaveError = ERROR_RESET; // Flag that is raised when miscellaneous errors are detected in the BMS IC.

	_bms->interfaceIsConnected = DISCONNECTED;// Flag that is raised when user interface is connected.

	_bms->vcuIsConnected = DISCONNECTED;// Flag that is raised when VCU is connected.

	_bms->userInterfaceShowErrorFlag = 1;// Flag that is raised when error should be sent to the user interface.

	_bms->cellBalancingIsEnabled = 0;// FLag that is raised when cell balancing is enabled.

	// Timer Initialization
	_bms->communicationStartTimer = _communicationStartTimer;
	_bms->stopDisplayingTimer = _stopDisplayingTimer;

	_bms->restartDCTOTimer.triggered = TIMER_RESET;
	// Flag that starts the communication of the ICs.
	_bms->startCommunicate = 1;

	// Limits for the measurements of ADBMS ICs.
	_bms->OTThreshold = _OverTempThreshold;
	_bms->UTThreshold = _UnderTempThreshold;
	_bms->OVThreshold = _overVoltageThreshold;
	_bms->UVThreshold = _underVoltageThreshold;
	_bms->ITMPThreshold = 100;
	// Starting valiables for min, max measurements.
	_bms->minVoltageCell.val = 5;
	_bms->minVoltageCell.id = 0;

	_bms->maxVoltageCell.val = 0;
	_bms->maxVoltageCell.id = 0;

	_bms->maxCellTemp.val = 0;
	_bms->maxCellTemp.id = 0;


	_bms->icPower[0] = SLAVE_DCDC_POWER;
	_bms->icPower[1] = SLAVE_DCDC_POWER;
	_bms->icPower[2] = SLAVE_DCDC_POWER;
	_bms->icPower[3] = SLAVE_DCDC_POWER;
	_bms->icPower[4] = SLAVE_DCDC_POWER;
	_bms->icPower[5] = SLAVE_DCDC_POWER;
	_bms->icPower[6] = SLAVE_DCDC_POWER;
	_bms->icPower[7] = SLAVE_DCDC_POWER;
	_bms->icPower[8] = SLAVE_DCDC_POWER;
	_bms->icPower[9] = SLAVE_DCDC_POWER;
	_bms->icPower[10] = SLAVE_DCDC_POWER;
	_bms->icPower[11] = SLAVE_DCDC_POWER;

	// Initializes the maximum errors needed for establishing whether the BMS has a fault or not
	_bms->acceptedErrors = _acceptedErrors;

	// Variables needed for the Cell balancing algorithm from the dcc bits.
	_bms->maxDiffbetweenCells = _maxDiffbetweenCells;
	_bms->minVoltageBalancingisEnabled = _minVoltageBalancingIsEnabled;
	_bms->maxVoltageBalancingisEnabled = _maxVoltageBalancingIsEnabled;

	_bms->wifiIsConnected = DISCONNECTED;

	HAL_GPIO_WritePin(AMS_CS_2_GPIO_Port, AMS_CS_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AMS_CS_1_GPIO_Port, AMS_CS_1_Pin, GPIO_PIN_SET);

	// Initialize the ICs and the ADCV command

	adBms6830_init_config(TOTAL_IC, _bms->bmsIC, _overVoltageThreshold, _underVoltageThreshold);
	adBmsWakeupIc(TOTAL_IC);
	adBms6830_clear_flags(TOTAL_IC, _bms->bmsIC);
	adBms6830_Adcv(RD_OFF, CONTINUOUS, DCP_OFF, RSTF_OFF, OW_OFF_ALL_CH);// Start C-ADC Conversions. Initialize only once.

	// Here the timers are started with their interrupts enabled.
	return (HAL_TIM_Base_Start_IT(_stopDisplayingTimer) |
			HAL_TIM_Base_Start_IT(_communicationStartTimer));
}

/**
*******************************************************************************
* @brief Initializes the ACU structure that contains data coming from the main
* PCB ocated inside TSAC.
*******************************************************************************
*/
HAL_StatusTypeDef ACUInit(ACUData *_acu, TIM_HandleTypeDef *_IMDPWMCaptureTimer, uint16_t _overCurrentThreshold){

	// Overcurrent threshold for the BMS to compare in order to open the shutdown system.
	_acu->overCurrentThreshold = _overCurrentThreshold;
	_acu->IMDHasError = ERROR_RESET;
	_acu->IMDResistance = 0;
	_acu->IMDPWMFrequency = 0;
	_acu->IMDPWMDutyCycle = 0;
	_acu->startPrecharge = 0;
	_acu->vicorTemperature = 0;
	_acu->humidity = 0;
	_acu->PCBTemperature = 0;
	_acu->vicorThermistorTemperature = 0;

	_acu->airMinusIsStuck = RELAY_STUCK;
	_acu->airPlusIsStuck = RELAY_STUCK;
	_acu->airMinusIsStuckFlag = 0;
	_acu->airPlusIsStuckFlag = 0;
	_acu->airsStuckAcceptedErrors = 100;

	_acu->DCBusOver60Volt = 0;
	_acu ->startPrecharge = 0;
	_acu->prechargeIsDone = 0;
	_acu->IMDPWMCaptureTimer = _IMDPWMCaptureTimer;

	// Pins
	_acu->IMDIsOK.pin = IMD_OK_Input_Pin;
	_acu->IMDIsOK.group = IMD_OK_Input_GPIO_Port;

	_acu->airPlusDriver.pin = AIR_Plus_Driver_Output_Pin;
	_acu->airPlusDriver.group = AIR_Plus_Driver_Output_GPIO_Port;

	_acu->fansControl.pin = Fans_Output_Pin;
	_acu->fansControl.group = Fans_Output_GPIO_Port;

	_acu->TSOver60Volt.pin = AIRs_Voltage_Over_60_Input_Pin;
	_acu->TSOver60Volt.group = AIRs_Voltage_Over_60_Input_GPIO_Port;

	_acu->startPrechargeAction.pin = AA_Button_Output_Pin;
	_acu->startPrechargeAction.group = AA_Button_Output_GPIO_Port;

	// Digital input for air minus relay auxilliary state.
	_acu->airMinusAux.pin = AIR_Minus_State_Input_Pin;
	_acu->airMinusAux.group = AIR_Minus_State_Input_GPIO_Port;

	// Digital input for air minus relay auxilliary supply.
	_acu->airMinusSupply.pin = TSMS_Input_Pin;
	_acu->airMinusSupply.group = TSMS_Input_GPIO_Port;

	// Digital input for air plus relay auxilliary state.
	_acu->airPlusAux.pin = Air_Plus_State_Input_Pin;
	_acu->airPlusAux.group = Air_Plus_State_Input_GPIO_Port;

	// Digital input for air minus relay auxilliary supply.
	_acu->airPlusSupply.pin = AIR_Plus_Supply_Input_Pin;
	_acu->airPlusSupply.group = AIR_Plus_Supply_Input_GPIO_Port;

	// Digital input for Precharge relay auxilliary state.
	_acu->preAux.pin = Pre_State_Input_Pin;
	_acu->preAux.group = Pre_State_Input_GPIO_Port;

	// Digital input for SD Card State.
	_acu->SDCardIsDetected.pin = LED_SD_Pin;
	_acu->SDCardIsDetected.group = LED_SD_GPIO_Port;

	// This pin is from hardware BMS reset latch.
	_acu->IMDLatchedError.pin = IMD_Latched_Input_Pin;
	_acu->IMDLatchedError.group = IMD_Latched_Input_GPIO_Port;

	//SoC
    _acu->soc = 0;

    _acu->sdDisabled = 0;
    _acu->sdEnabled = 0;
    _acu->usbConnected = false;

    _acu->updateCellBalancingValue = 0;

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)_acu->analogInputRawValues, 3);

	// Flag that starts the precharge sequence. It is updated from External Interrupt or from dashboard button through CANBUS emssage from VCU

	return 	HAL_TIM_IC_Start_IT(_IMDPWMCaptureTimer, TIM_CHANNEL_1) | HAL_TIM_IC_Start_IT(_IMDPWMCaptureTimer, TIM_CHANNEL_2);
}




float callibrateBMSVoltage(float readValue, uint8_t currentSegment){
//	if(currentSegment == 7) return readValue;
//	else
	return (map(readValue * 12, 32.325, 49.673, 32.4 , 49.8)) / 12;}
float temperatureVicor = 0;
float thermistorCalculate(uint16_t adcValue){
  float Vout = (3.3 * adcValue) / 4095;     // Convert Vout to volts
  float R = 10000 * (1 / ((3.3 / Vout) - 1)); // Formula to calculate tested resistor's value
  float steinhart = R / 10000;     // (R/Ro)
  steinhart = log(steinhart);            // ln(R/Ro)
  steinhart /= 3435;             // 1/B * ln(R/Ro)
  steinhart += 1.0 / (25 + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;           // Invert
  steinhart -= 273.15;
  temperatureVicor = steinhart;
  if(steinhart < 0) return 0;
  return steinhart;
}


/**
 * @brief  Calculates the accumulator's state of charge
 * @param  Charging AmpereHours, Discharging AmpereHours
 * @retval State of Charge value
 */

float calculateSoC(uint64_t chAs, uint64_t dchAs)
{
    int64_t dAs = (int64_t)(chAs - lastChargeAs) - (int64_t)(dchAs - lastDischargeAs);
    float dAh = ((float)dAs) / 3600.0f;

    remainingAh += dAh;

    if (remainingAh < 0.0f)
        remainingAh = 0.0f;
    else if (remainingAh > MAX_Ah)
        remainingAh = MAX_Ah;

    lastChargeAs = chAs;
    lastDischargeAs = dchAs;

    return 100.0f * (remainingAh / MAX_Ah);
}













