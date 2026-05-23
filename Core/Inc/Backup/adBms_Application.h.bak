/*******************************************************************************
Copyright (c) 2020 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensor.
******************************************************************************
* @file:    adBms_Application.h
* @brief:   Bms application header file
* @version: $Revision$
* @date:    $Date$
* Developed by: ADIBMS Software team, Bangalore, India
*****************************************************************************/
/*! @addtogroup APPLICATION
*  @{
*
*/

/*! @addtogroup APPLICATION
*  @{
*
*/

#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <stdint.h>
#include "main.h"

float map(float x, float in_min, float in_max, float out_min, float out_max);
float lookUpTable(int16_t voltage);
int16_t getIntFromVoltage(float voltage);
float getVoltage(int data);
void adBms6830_update_configb(uint8_t tIC, cell_asic *ic);
void adbms6830_safe_write(uint8_t tIC, cell_asic *ic, TYPE type, GRP group);
void adBms6830_snap(uint8_t tIC);
void adBms6830_unsnap(uint8_t tIC);
void adBms6830_mute(uint8_t tIC);
void adBms6830_unmute(uint8_t tIC);
void adBms6830_write_pwm(uint8_t tIC, cell_asic *ic, PWM_DUTY value);
void adBms6830_init_config(uint8_t tIC, cell_asic *ic, float _OV_THRESHOLD,float _UV_THRESHOLD);
void adBms6830_write_read_config(uint8_t tIC, cell_asic *ic);
void adBms6830_read_config(uint8_t tIC, cell_asic *ic);
void adBms6830_read_cell_voltages(uint8_t tIC, cell_asic *ic);
void adBms6830_read_s_voltages(uint8_t tIC, cell_asic *ic);
void adBms6830_read_avgcell_voltages(uint8_t tIC, cell_asic *ic);
void adBms6830_read_fcell_voltages(uint8_t tIC, cell_asic *ic);
void adBms6830_read_aux_voltages(uint8_t tIC, cell_asic *ic);
void adBms6830_clear_flags(uint8_t tIC, cell_asic *ic);
#endif
/** @}*/
/** @}*/
