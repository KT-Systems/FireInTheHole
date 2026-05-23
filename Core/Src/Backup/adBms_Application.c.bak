/*******************************************************************************
Copyright (c) 2020 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensor.
******************************************************************************
* @file:    adbms_Application.c
* @brief:   adbms application test cases
* @version: $Revision$
* @date:    $Date$
* Developed by: ADIBMS Software team, Bangalore, India
*****************************************************************************/
/*! \addtogroup APPLICATION
*  @{
*/

/*! @addtogroup Application
*  @{
*/
#include "common.h"
#include "adBms_Application.h"
#include "adBms6830CmdList.h"
#include "adBms6830GenericType.h"
#include "mcuWrapper.h"
#include "cmsis_os.h"
#include "fdcan.h"
#include "fatfs.h"
#ifdef MBED
extern Serial pc;
#endif
/**
*******************************************************************************
* @brief Setup Variables
* The following variables can be modified to configure the software.
*******************************************************************************
*/


/* ADC Command Configurations */

uint32_t pladc_count;


/**
*******************************************************************************
* @brief function that changes the scale of a variable
*******************************************************************************
*/
float map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
*******************************************************************************
* @brief function that converts data from AUX register.
* to temperature. From datasheet of Sony/Murata VTC6, the battaries we use.
*******************************************************************************
*/

float lookUpTable(int16_t voltage){

	float look_up_table[33] = {2.44, 2.42, 2.40, 2.38, 2.35, 2.32, 2.27, 2.23, 2.17, 2.11, 2.05, 1.99, 1.92, 1.86, 1.8,
			1.74, 1.68, 1.63, 1.59, 1.55, 1.51, 1.48, 1.45, 1.43, 1.40, 1.38, 1.37, 1.35, 1.34, 1.33, 1.32, 1.31, 1.30};
    int i = 1;
    float fvolt = getVoltage(voltage);
    float min, max;
    while(fvolt < look_up_table[i]){
    	i++;
    	max = look_up_table[i - 1];
    	min = look_up_table[i];
}
return map(fvolt,max,min,(5 * i - 45),(5 * i - 40));
}

/**
*******************************************************************************
* @brief function that turns float values of IC to integers
*******************************************************************************
*/

int16_t getIntFromVoltage(float voltage){
	int16_t intVoltage = voltage / 0.000150 - 10000;
	return intVoltage;
}
/**
*******************************************************************************
* @brief function that integer values of IC to voltages
*******************************************************************************
*/

float getVoltage(int data)
{
    float voltage_float = ((data + 10000) * 0.000150);
    return voltage_float;
}
/**
*******************************************************************************
* @brief function that initializes cell_asic structure array
*******************************************************************************
*/
void adBms6830_init_config(uint8_t tIC, cell_asic *ic, float _OV_THRESHOLD,float _UV_THRESHOLD)
{
  for(uint8_t cic = 0; cic < tIC; cic++)
  {
		/* Init config A */
	  ic[cic].tx_cfga.refon = PWR_UP;
//	  ic[cic].tx_cfga.
	  ic[cic].tx_cfga.gpo = 0X3FF; /* All GPIO pull down off */
	  ic[cic].tx_cfga.fc = IIR_FPA8; // Filter frequency is 52Hz and data receiving rate of our setup is 50 Hz
		/* Init config B */
	  ic[cic].tx_cfgb.vov = SetOverVoltageThreshold(_OV_THRESHOLD);
	  ic[cic].tx_cfgb.vuv = SetUnderVoltageThreshold(_UV_THRESHOLD);
	  ic[cic].tx_cfgb.dcto = 0; // For PWM Cell Balancing!
	  ic[cic].tx_cfgb.dtrng = 0;// DCTO Bit is equal to 1 minute.
	  ic[cic].tx_cfgb.dtmen = 0;// If dcto > 0 when watchdog times out, it will enter a state that will check if the cell has gone undervoltaged and disable the PWM discharge
	  ic[cic].tx_cfgb.dcc = 0;

  }

  for(int i = 0; i < 3; i++){ // Sends them multpile times to make sure the chips are configured.
	  adBmsWakeupIc(tIC);
	  adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
	  adBmsWriteData(tIC, &ic[0], WRCFGB, Config, B);
  }
//  adbms6830_safe_write(tIC,&ic[0], Config, A); // Experimental!
//  adbms6830_safe_write(tIC,&ic[0], Config, B);
  adBmsWakeupIc(tIC);
  adBmsReadData(tIC, &ic[0], RDCFGA, Config, A);
  adBmsReadData(tIC, &ic[0], RDCFGB, Config, B);
}

void adbms6830_safe_write(uint8_t tIC, cell_asic *ic, TYPE type, GRP group){
uint8_t writeCompleted;
	switch(type){

	case Pwm:

		switch(group){
		case A:
			while(1){
				  adBmsWakeupIcIdle(tIC);
				  adBmsWriteData(tIC, &ic[0], WRPWM1, Pwm, A);
				  adBmsReadData(tIC, &ic[0], WRPWM1, Pwm, A);
				  writeCompleted = 1;
				  for(int cic = 0; cic < TOTAL_IC; cic++) for(int i = 0; i < 6; i++) if(ic[cic].pwma.rx_data[i] != ic[cic].pwma.tx_data[i]) writeCompleted = 0;
				  if(writeCompleted) break;
			}
		break;

		case B:
			while(1){
				  adBmsWakeupIcIdle(tIC);
				  adBmsWriteData(tIC, &ic[0], WRPWM2, Pwm, B);
				  adBmsReadData(tIC, &ic[0], RDPWM2, Pwm, B);
				  writeCompleted = 1;
				  for(int cic = 0; cic < TOTAL_IC; cic++) for(int i = 0; i < 6; i++) if(ic[cic].pwmb.rx_data[i] != ic[cic].pwmb.tx_data[i]) writeCompleted = 0;
				  if(writeCompleted) break;
			}
		break;
		default:
		break;


		}
	break;

	case Config:

		switch(group){
		case A:
			while(1){
				adBmsWakeupIcIdle(tIC);
				adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
				adBmsReadData(tIC, &ic[0], RDCFGA, Config, A);
				writeCompleted = 1;
				for(int cic = 0; cic < TOTAL_IC; cic++) for(int i = 0; i < 6; i++) if(ic[cic].configa.rx_data[i] != ic[cic].configa.tx_data[i]) writeCompleted = 0;
				if(writeCompleted) break;
			}
		break;

		case B:
			while(1){
				  adBmsWakeupIcIdle(tIC);
				  adBmsWriteData(tIC, &ic[0], WRCFGB, Config, B);
				  adBmsReadData(tIC, &ic[0], RDCFGB, Config, B);
				  writeCompleted = 1;
				  for(int cic = 0; cic < TOTAL_IC; cic++) for(int i = 0; i < 6; i++) if(ic[cic].configb.rx_data[i] != ic[cic].configb.tx_data[i]) writeCompleted = 0;
				  if(writeCompleted) break;
			}
		break;
		default:

		break;


		}
	break;

	default:
	break;
	}


}
/**
*******************************************************************************
* @brief Sends PWM command with the parameter value in it. It enables passive
* cell balancing with PWM form the IC
*******************************************************************************
*/
void adBms6830_write_pwm(uint8_t tIC, cell_asic *ic, PWM_DUTY value){
	uint8_t writeCompleted = 0;
	uint8_t timeout = 0;
	for(uint8_t cic = 0; cic < tIC; cic++){
		for(uint8_t cid = START_MEASURE_CELL; cid < 12; cid++) ic[cic].PwmA.pwma[cid] = value;

#if STOP_MEASURE_CELL>12
		for(uint8_t cid = 0; cid < STOP_MEASURE_CELL - 12; cid++) ic[cic].PwmB.pwmb[cid] = value;
#endif
	}
	while(!writeCompleted && timeout < 100){
		timeout++;
		writeCompleted = 1;
		adBmsWakeupIcIdle(tIC);
		adBmsWriteData(tIC, &ic[0], WRPWM1, Pwm, A);
		adBmsReadData(tIC, &ic[0], RDPWM1, Pwm, A);
		for(int cic = 0; cic < tIC; cic++)	for(int i = 0; i < 6; i++)	if(ic[cic].pwma.rx_data[i] != ((value << 4) | value)) writeCompleted = 0;
	}
#if	STOP_MEASURE_CELL>12
		adBmsWriteData(tIC, &ic[0], WRPWM2, Pwm, B);
		adBmsReadData(tIC, &ic[0], RDPWM2, Pwm, B);
#endif

}


/**
*******************************************************************************
* @brief Write and Read Configuration Register A/B
*******************************************************************************
*/
void adBms6830_write_read_config(uint8_t tIC, cell_asic *ic){
	adBmsWakeupIc(tIC);
	adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
	adBmsWriteData(tIC, &ic[0], WRCFGB, Config, B);
	adBmsReadData(tIC, &ic[0], RDCFGA, Config, A);
	adBmsReadData(tIC, &ic[0], RDCFGB, Config, B);
}

/**
*******************************************************************************
* @brief Read Configuration Register A/B
*******************************************************************************
*/
void adBms6830_read_config(uint8_t tIC, cell_asic *ic){
  adBmsWakeupIcIdle(tIC);
  adBmsReadData(tIC, &ic[0], RDCFGA, Config, A);
  adBmsReadData(tIC, &ic[0], RDCFGB, Config, B);
}

/**
*******************************************************************************
* @brief Update Configuration Register B
*******************************************************************************
*/
void adBms6830_update_configb(uint8_t tIC, cell_asic *ic){
	uint8_t writeCompleted = 0;
	uint8_t timeout = 0;
	while(!writeCompleted && timeout < 30){
		timeout++;
		writeCompleted = 1;
		adBmsWriteData(tIC, &ic[0], WRCFGB, Config, B);
		adBmsReadData(tIC, &ic[0], RDCFGB, Config, B);
		for(int cic = 0; cic < tIC; cic++)	for(int i = 0; i < 6; i++)	if(ic[cic].configb.rx_data[i] != ic[cic].configb.tx_data[i]) writeCompleted = 0;

	}
}

/**
*******************************************************************************
* @brief Read Cell Voltages
*******************************************************************************
*/
void adBms6830_read_cell_voltages(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsReadData(tIC, &ic[0], RDCVA, Cell, A);
  adBmsReadData(tIC, &ic[0], RDCVB, Cell, B);
  adBmsReadData(tIC, &ic[0], RDCVC, Cell, C);
  adBmsReadData(tIC, &ic[0], RDCVD, Cell, D);
  adBmsReadData(tIC, &ic[0], RDCVE, Cell, E);
  adBmsReadData(tIC, &ic[0], RDCVF, Cell, F);
  //printVoltages(tIC, &ic[0], Cell);

}

/**
*******************************************************************************
* @brief Read S-Voltages
*******************************************************************************
*/
void adBms6830_read_s_voltages(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsReadData(tIC, &ic[0], RDSVA, S_volt, A);
  adBmsReadData(tIC, &ic[0], RDSVB, S_volt, B);
  adBmsReadData(tIC, &ic[0], RDSVC, S_volt, C);
  adBmsReadData(tIC, &ic[0], RDSVD, S_volt, D);
  adBmsReadData(tIC, &ic[0], RDSVD, S_volt, E);
  adBmsReadData(tIC, &ic[0], RDSVD, S_volt, F);

}

/**
*******************************************************************************
* @brief Start Avarage Cell Voltage Measurement
*******************************************************************************
*/
void adBms6830_start_avgcell_voltage_measurment(uint8_t tIC)
{
  adBmsWakeupIc(tIC);
  adBms6830_Adcv(RD_ON, SINGLE, DCP_OFF, RSTF_OFF, OW_OFF_ALL_CH);
  pladc_count = adBmsPollAdc(PLADC);
}
//void adbms6830ReadAvg(uint8_t tIC, uint8_t *read_buffer, int16_t voltages[12][16]){
////	adBmsRead(tIC,RDACA,read_buffer);
//
//
//}

/**
*******************************************************************************
* @brief Read Avarage Cell Voltages
*******************************************************************************
*/
void adBms6830_read_avgcell_voltages(uint8_t tIC, cell_asic *ic)
{

  adBmsWakeupIcIdle(tIC);
  adBmsReadData(tIC, &ic[0], RDACA, AvgCell, A);
  adBmsReadData(tIC, &ic[0], RDACB, AvgCell, B);
  adBmsReadData(tIC, &ic[0], RDACC, AvgCell, C);
  adBmsReadData(tIC, &ic[0], RDACD, AvgCell, D);
  adBmsReadData(tIC, &ic[0], RDSTATA, Status, A); // Statuses!
  adBmsReadData(tIC, &ic[0], RDSTATB, Status, B);
  adBmsReadData(tIC, &ic[0], RDSTATC, Status, C);
}

/**
*******************************************************************************
* @brief Read Filtered Cell Voltages
*******************************************************************************
*/
void adBms6830_read_fcell_voltages(uint8_t tIC, cell_asic *ic)
{
#if START_MEASURE_CELL < 3
  adBmsReadData(tIC, &ic[0], RDFCA, F_volt, A);
#endif
  adBmsReadData(tIC, &ic[0], RDFCB, F_volt, B);
  adBmsReadData(tIC, &ic[0], RDFCC, F_volt, C);
  adBmsReadData(tIC, &ic[0], RDFCD, F_volt, D);

  adBmsReadData(tIC, &ic[0], RDSTATA, Status, A); // Statuses!
  adBmsReadData(tIC, &ic[0], RDSTATB, Status, B);
#if STOP_MEASURE_CELL > 12
  adBmsReadData(tIC, &ic[0], RDFCE, F_volt, E);
  adBmsReadData(tIC, &ic[0], RDFCF, F_volt, F);
#endif
}

/**
*******************************************************************************
* @brief Read AUX, VMV, V+ Voltages
*******************************************************************************
*/
void adBms6830_read_aux_voltages(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIcIdle(tIC);
  adBmsReadData(tIC, &ic[0], RDAUXA, Aux, A);
  adBmsReadData(tIC, &ic[0], RDAUXB, Aux, B);
  adBmsReadData(tIC, &ic[0], RDAUXC, Aux, C);
  adBmsReadData(tIC, &ic[0], RDAUXD, Aux, D);
}

/**
*******************************************************************************
* @brief Read Redundant GPIO Voltages
*******************************************************************************
*/
void adBms6830_read_raux_voltages(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsReadData(tIC, &ic[0], RDRAXA, RAux, A);
  adBmsReadData(tIC, &ic[0], RDRAXB, RAux, B);
  adBmsReadData(tIC, &ic[0], RDRAXC, RAux, C);
  adBmsReadData(tIC, &ic[0], RDRAXD, RAux, D);
  //printVoltages(tIC, &ic[0], RAux);
}

/**
*******************************************************************************
* @brief Read Status Reg. A, B, C, D and E.
*******************************************************************************
*/
void adBms6830_read_status_registers(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIcIdle(tIC);
  adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
  adBmsWriteData(tIC, &ic[0], WRCFGB, Config, B);
  adBms6830_Adax(AUX_OW_OFF, PUP_DOWN, AUX_ALL);
  pladc_count = adBmsPollAdc(PLADC);
  adBms6830_Adcv(RD_OFF, SINGLE, DCP_OFF, RSTF_OFF,  OW_OFF_ALL_CH);
  pladc_count = pladc_count + adBmsPollAdc(PLADC);

  adBmsReadData(tIC, &ic[0], RDSTATA, Status, A);
  adBmsReadData(tIC, &ic[0], RDSTATB, Status, B);
  adBmsReadData(tIC, &ic[0], RDSTATC, Status, C);
  adBmsReadData(tIC, &ic[0], RDSTATD, Status, D);
  adBmsReadData(tIC, &ic[0], RDSTATE, Status, E);
  //printPollAdcConvTime(pladc_count);
  //printStatus(tIC, &ic[0], Status, ALL_GRP);
}

/**
*******************************************************************************
* @brief Mute Command for pwm balancing
*******************************************************************************
*/
void adBms6830_mute(uint8_t tIC){
	  adBmsWakeupIcIdle(tIC);
	  spiSendCmd(MUTE);
}

/**
*******************************************************************************
* @brief Unmute Command for pwm balancing
*******************************************************************************
*/
void adBms6830_unmute(uint8_t tIC){
//	  adBmsWakeupIcIdle(tIC);
	  spiSendCmd(UNMUTE);
}
/**
*******************************************************************************
* @brief Snap Command
*******************************************************************************
*/
void adBms6830_snap(uint8_t tIC){
	  adBmsWakeupIcIdle(tIC);
	  spiSendCmd(SNAP);
}


/**
*******************************************************************************
* @brief UnSnap Command
*******************************************************************************
*/
void adBms6830_unsnap(uint8_t tIC){
	  adBmsWakeupIcIdle(tIC);
	  spiSendCmd(UNSNAP);
}

/**
*******************************************************************************
* @brief Clear Cell measurement reg.
*******************************************************************************
*/
void adBms6830_clear_flags(uint8_t tIC, cell_asic *ic)
{
	for(int cic = 0; cic < tIC; cic++){
		ic[cic].clflag.cl_csflt = 0xffff;
		ic[cic].clflag.cl_ced = 1;
		ic[cic].clflag.cl_cmed = 1;
		ic[cic].clflag.cl_oscchk = 1;
		ic[cic].clflag.cl_sed = 1;
		ic[cic].clflag.cl_sleep = 1;
		ic[cic].clflag.cl_smed = 1;
		ic[cic].clflag.cl_spiflt = 1;
		ic[cic].clflag.cl_thsd = 1;
		ic[cic].clflag.cl_tmode = 1;
		ic[cic].clflag.cl_vaov = 1;
		ic[cic].clflag.cl_vauv = 1;
		ic[cic].clflag.cl_vauv = 1;
		ic[cic].clflag.cl_vde = 1;
		ic[cic].clflag.cl_vdel = 1;
		ic[cic].clflag.cl_vdov = 1;
		ic[cic].clflag.cl_vduv = 1;
	}
	adBmsWakeupIc(tIC);
	adBmsWriteData(tIC, &ic[0], CLRFLAG, Clrflag, A);
}
void adBms6830_clear_cell_measurement(uint8_t tIC)
{
  adBmsWakeupIcIdle(tIC);
  spiSendCmd(CLRCELL);
#ifdef MBED
  pc.printf("Cell Registers Cleared\n\n");
#else
  printf("Cell Registers Cleared\n\n");
#endif
}
/**
*******************************************************************************
* @brief Clear Aux measurement reg.
*******************************************************************************
*/
void adBms6830_clear_aux_measurement(uint8_t tIC)
{
  adBmsWakeupIcIdle(tIC);
  spiSendCmd(CLRAUX);
#ifdef MBED
  pc.printf("Aux Registers Cleared\n\n");
#else
  printf("Aux Registers Cleared\n\n");
#endif
}

/**
*******************************************************************************
* @brief Clear spin measurement reg.
*******************************************************************************
*/
void adBms6830_clear_spin_measurement(uint8_t tIC)
{
  adBmsWakeupIc(tIC);
  spiSendCmd(CLRSPIN);
#ifdef MBED
  pc.printf("Spin Registers Cleared\n\n");
#else
  printf("Spin Registers Cleared\n\n");
#endif
}

/**
*******************************************************************************
* @brief Clear fcell measurement reg.
*******************************************************************************
*/
void adBms6830_clear_fcell_measurement(uint8_t tIC)
{
  adBmsWakeupIc(tIC);
  spiSendCmd(CLRFC);
#ifdef MBED
  pc.printf("Fcell Registers Cleared\n\n");
#else
  printf("Fcell Registers Cleared\n\n");
#endif
}

void setPin(Pin *_pin){
	_pin->state = GPIO_PIN_SET;
	HAL_GPIO_WritePin(_pin->group, _pin->pin, GPIO_PIN_SET);
}
void resetPin(Pin *_pin){
	_pin->state = GPIO_PIN_RESET;
	HAL_GPIO_WritePin(_pin->group, _pin->pin, GPIO_PIN_RESET);
}
GPIO_PinState readPin(Pin *_pin){
	_pin->state = HAL_GPIO_ReadPin(_pin->group, _pin->pin);
	return _pin->state;
}


/** @}*/
/** @}*/
