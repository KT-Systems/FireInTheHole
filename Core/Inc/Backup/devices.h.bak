/*
 * devices.h
 *
 *  Created on: Mar 21, 2024
 *      Author: kara
 */

#ifndef INC_DEVICES_H_
#define INC_DEVICES_H_

//SoC
#define FULLY_CHARGED  0
#define MAX_Ah 15.833f


//TOTAL ICs in our system. Default will be 12 but for testing with the evaluation board 1 is used.
#define TOTAL_IC 12

//Cell Number from which measurements start.
#define START_MEASURE_CELL 0

//Cell Number in which measurements end.
#define STOP_MEASURE_CELL 12

//Amount of cell temperature measurement.
#define TOTAL_ID_TEMP 10

//#define DYNAMIC_CELL_BALANCING_ENABLED

#define DCC_BITS_CELL_BALANCING

#define MAX_CHARGING_VOLTAGE 598

#define MAX_CHARGING_CURRENT 6

#define FILE_BASE_NAME "A"


#define VICOR_CMD_PAGE                0x00 // Access BCM stored information
#define VICOR_CMD_OPERATION           0x01 // Turn BCM on or off
#define VICOR_CMD_CLEAR_FAULTS        0x03 // Clear all faults
#define VICOR_CMD_CAPABILITY          0x19 // PMBs key capabilites set by factory
#define VICOR_CMD_OT_FAULT_LIMIT      0x4F // Overtemperature protection
#define VICOR_CMD_OT_WARN_LIMIT       0x51 // Overtemperature warning
#define VICOR_CMD_VIN_OV_FAULT_LIMIT  0x55 // High-voltage-side overvoltage protection
#define VICOR_CMD_VIN_OV_WARN_LIMIT   0x57 // High-voltage-side overvoltage warning
#define VICOR_CMD_IIN_OC_FAULT_LIMIT  0x5B // High-voltage-side overcurrent protection
#define VICOR_CMD_IIN_OC_WARN_LIMIT   0x5D // High-voltage-side overcurrent warning
#define VICOR_CMD_TON_DELAY           0x60 // Start up delay in addition to fixed delay
#define VICOR_CMD_STATUS_BYTE         0x78 // Summary of faults
#define VICOR_CMD_STATUS_WORD         0x79 // Summary of fault conditions
#define VICOR_CMD_STATUS_IOUT         0x7B // Overcurrent fault status
#define VICOR_CMD_STATUS_INPUT        0x7C // Overvoltage and undervoltage fault status
#define VICOR_CMD_STATUS_TEMPERATURE  0x7D // Overtemperature and undertemperature fault status
#define VICOR_CMD_STATUS_CML          0x7E // PMBus communication fault
#define VICOR_CMD_STATUS_MFR_SPECIFIC 0x80 // Other BCM status indicator
#define VICOR_CMD_READ_VIN            0x88 // Reads HI-side voltage
#define VICOR_CMD_READ_IIN            0x89 // Reads HI-side current
#define VICOR_CMD_READ_VOUT           0x8B // Reads LO-side voltage
#define VICOR_CMD_READ_IOUT           0x8C // Reads LO-side current
#define VICOR_CMD_READ_TEMPERATURE_1  0x8D // Reads internal temperature
#define VICOR_CMD_READ_POUT           0x96 // Reads LO-side power
#define VICOR_CMD_PMBUS_REVISION      0x98 // PMBus compatible revision
#define VICOR_CMD_MFR_ID              0x99 // BCM controller ID
#define VICOR_CMD_MFR_MODEL           0x9A // Internal controller or BCM model
#define VICOR_CMD_MFR_REVISION        0x9B // Internal controller or BCM revision
#define VICOR_CMD_MFR_LOCATION        0x9C // Internal controller or BCM factory location
#define VICOR_CMD_MFR_DATE            0x9D // Internal controller or BCM manufacturing date
#define VICOR_CMD_MFR_SERIAL          0x9E // Internal controller or BCM serial number
#define VICOR_CMD_MFR_VIN_MIN         0xA0 // Minimum rated high side voltage
#define VICOR_CMD_MFR_VIN_MAX         0xA1 // Maximum rated high side voltage
#define VICOR_CMD_MFR_VOUT_MIN        0xA4 // Minimum rated low side voltage
#define VICOR_CMD_MFR_VOUT_MAX        0xA5 // Maximum rated low side voltage
#define VICOR_CMD_MFR_IOUT_MAX        0xA6 // Maximum rated low side current
#define VICOR_CMD_MFR_POUT_MAX        0xA7 // Maximum rated low side power
#define VICOR_CMD_READ_K_FACTOR       0xD1 // Reads K factor
#define VICOR_CMD_READ_BCM_ROUT       0xD4 // Reads low-voltage side output resistance
#define SET_ALL_THRESHOLDS            0xD5 // Set supervisory warning and protection thresholds
#define DISABLE_FAULT                 0xD7 // Disable overvoltage, overcurrent or undervoltage supervisory faults

#define DEVICE_ADDRESS 0x51
#define I2C_TIMEOUT    100


extern ADC_HandleTypeDef hadc1;

//Enums

typedef enum {OFF = 0x0, ON}powerState;

typedef enum {RELAY_NOT_STUCK = 0x0, RELAY_STUCK} relayState;

typedef enum {ERROR_RESET = 0x0, ERROR_TRIGGERED} errorState;

typedef enum {TIMER_RESET = 0x0, TIMER_TRIGGERED} timerState;

typedef enum {DISCONNECTED = 0x00, CONNECTED} connectionState;

typedef enum {ENTERED = 0X0, TO_ENTER} firstLoopEnterState;

typedef enum {NOT_PRESSED = 0X0, PRESSED} buttonState;

typedef enum {NOT_DISCHARGING = 0X0, DISCHARGING} discharginCellState;

typedef enum {SLAVE_DCDC_POWER = 0x0, SLAVE_VREF_POWER} slavePowerState;

typedef enum {IVT_STOP = 0x0, IVT_RUN = 0x1} ivtMode;

typedef enum {IVT_250KBPS = 0x08, IVT_500KBPS = 0x04, IVT_1000KBPS = 0x02} ivtBaudRate;

typedef enum {IVT_CURRENT = 0x20, IVT_VOLTAGE_1 = 0x21, IVT_VOLTAGE_2 = 0x22, IVT_VOLTAGE_3 = 0x23, IVT_TEMPERATURE = 0x24, IVT_WATTAGE = 0x25, IVT_CURRENT_COUNTER = 0x26, IVT_WATTAGE_COUNTER = 0x27} ivtVariable;

typedef enum {VICOR_CONTROLLER_PAGE = 0x0, VICOR_HIGH_VOLTAGE_PAGE = 0x1}vicorPages;

typedef enum {CHARGER_WANTED_ON = 0, CHARGER_WANTED_OFF = 0X1}chargerCommands;

typedef enum {VICOR_INPUT_VOLTAGE = 0x88, VICOR_INPUT_CURRENT = 0x89, VICOR_OUTPUT_VOLTAGE = 0x8b, VICOR_OUTPUT_CURRENT = 0x8c, VICOR_TEMPERATURE = 0x8d, VICOR_OUTPUT_WATTAGE = 0x96}vicorCommands;
//End of Enums

typedef struct Button{
	uint16_t pin;
	buttonState state;
}Button;

//Substructure of a pin.
typedef struct Pin{
	uint16_t pin;
	GPIO_TypeDef* group;
	GPIO_PinState state;
}Pin;

//Substructure of a timer.
typedef struct Timer{
	TIM_HandleTypeDef *timer;
	timerState triggered;
}Timer;
// Helping structure for can messaging.
typedef struct CANData{
	FDCAN_TxHeaderTypeDef   extTxHeader;
	FDCAN_TxHeaderTypeDef   stdTxHeader;
	uint8_t               TxData[8];
	FDCAN_RxHeaderTypeDef   RxHeader;
	uint8_t               RxData[8];
	uint8_t 			  checkSum;
}CANData;

typedef struct IsabellenData{

	// Variables for state detection of Isabellen.
	connectionState isConnected;// This flag is raised if Isabellen is connected. It is updated from keep-alive can message.
	errorState hasError;// This flag is raised if Isabellen is either disconnected or overcurrent has occured.

	//SoC
	uint64_t chargingAs;
	uint64_t dischargingAs;


	// Variables for SCS Checks.
	uint8_t counterCheck;// Variable to compare for SCS checking.
	uint8_t SCSErrors;// Flag that if more than the accepted, it raises an error to Isabellen.
	uint8_t SCSacceptedErrors;// Flag for maximun accepted errors.

	//	Variables send from Isabellen.
	float current;// Variable for storing current of Isabellen.
	float voltage1;// Variable for storing voltage 1 of Isabellen.
	float voltage2;// Variable for storing voltage 2 of Isabellen.
	float voltage3;// Variable for storing voltage 3 of Isabellen.
	int32_t wattage;

	int32_t currentCounter;
	int32_t wattageCounter;
	// Timer to detect if Isabellen is disconnected.
	TIM_HandleTypeDef *timeOutTimer;

}IsabellenData;

typedef struct ChargerData{

	connectionState isConnected;// Flag used to detect if charger is connected.

	// Variables that are sent to charger. They are multiplied with 10 because the charger wants it that way.
	uint16_t wantedCurrentTimes10;// Seting it from the user interface. Units 0.1 Ampere.
	uint16_t wantedVoltageTimes10;// Default: 590 Volt. Units 0.1 Volts.
	uint8_t wantedOff;// Variable to control if the charging should begin.1 is Charging disabled and 0 is Charging enabled.

	TIM_HandleTypeDef *timeOutTimer;// Timer to detect if charger is connected.

	// Variables from Charger. Also multiplied with 10.
	float currentAtCharger;
	float voltageAtCharger;

	//Variable for receiving charging errors.
	uint8_t statusFlag;

	// Errors coming from charger.
	errorState hardwareFailure;
	errorState overTempFailure;
	errorState voltageFailure;
	errorState detectsPackFailure;
	errorState commFailure;

}ChargerData;

typedef enum {CELL_1, CELL_2, CELL_3, CELL_4, CELL_5, CELL_6, CELL_7, CELL_8, CELL_9, CELL_10, CELL_11, CELL_12}CellID;
typedef enum{SEGMENT_1, SEGMENT_2, SEGMENT_3, SEGMENT_4, SEGMENT_5, SEGMENT_6, SEGMENT_7, SEGMENT_8, SEGMENT_9, SEGMENT_10, SEGMENT_11, SEGMENT_12}Segment;

typedef struct CellData{
	float val;
	uint8_t id;
//	CellID id; // 0 -12
//	Segment segment;

}CellData;
// Structure for storing data for our DCDC. Control may be outside of ACU.

typedef struct VicorData{

	uint8_t wantedOff;
	I2C_HandleTypeDef *vicorI2C;

	uint8_t vicorSlaveAddress;

	uint16_t temperature;
	float voltageIn;
	float voltageOut;
	float currentIn;
	float currentOut;
	float wattageOut;
}VicorData;


// Structure for storing data for our custom BMS.
typedef struct BMSData{

	// Pins
	Pin isOK; // This pin is used to send the signal to hardware reset latch.
	Pin latchedError;//This pin is used to find BMS latched state in order to send it to ECU. Is SCS so must implement checksum.

	// Flags
	errorState hasError;// Flag that is raised when bms has error
	errorState voltageMeasurementError;
	connectionState interfaceIsConnected;// Flag that is raised when user interface is connected.
	connectionState vcuIsConnected;// Flag that is raised when VCU is connected.
	timerState startCommunicate;// Flag that starts the communication of the IC.
	firstLoopEnterState userInterfaceShowErrorFlag;// Flag that is raised when error should be sent to the user interface.
	errorState voltagesHaveError;// Flag that shows if voltages have errors such as open wire or over and under thresholds.
	errorState tempsHaveError;// Flag that shows if temperatures have errors such as open wire or over and under thresholds.
	errorState internalVoltagesHaveError;// Flag that is raised if
	errorState isoSPIHasError;// FLag that is raised if PEC is wrong.
	uint8_t cellBalancingIsEnabled;// Flag that shows when cell balancing is enabled.
	uint8_t cellBalancingIsWanted;// Flag that shows when user wants cell balancing is enabled.

	//  Timers
	TIM_HandleTypeDef *stopDisplayingTimer;// Timer to detect if User Interface is connected.
	TIM_HandleTypeDef *communicationStartTimer;// Timer to synchronize BMS ICs communications.
	Timer restartDCTOTimer;// Timer to reset DCTO for PWM Discherging. Not used right now.

	uint8_t acceptedErrors;// Max errors to detect if faults are occured.

	uint16_t voltageErrorFlags[TOTAL_IC][STOP_MEASURE_CELL];// Stores the error count of each voltage measurement.

	uint16_t tempErrorFlags[TOTAL_IC][TOTAL_ID_TEMP];// Stores the error count of each temperature measurement.

	uint16_t internalVoltagesErrorFlags[TOTAL_IC];// Flags that is raised when miscellaneous errors are detected in the IC.
	slavePowerState icPower[TOTAL_IC];
	uint8_t DischargingCells[TOTAL_IC][STOP_MEASURE_CELL];	// Used if want to detect which cells are balanced. Used in interface

	uint8_t firstSegmentLostCommunication; // IF isoSPI error occurs from the pec, we find which segment was disconnected.

	// Variable used for cell balancing.
	// Is the diferrence between the least charged cell and all the others, that if crossed cell balancing is enabled
	float maxDiffbetweenCells;

	// Variables for storing the max and min cell voltage of the pack.
	CellData minVoltageCell;
	CellData maxVoltageCell;

	// Variable for storing the max temperature among the cells.
	CellData maxCellTemp;

	// Variable that stores all sum of all cells' voltages.
	float packVoltage;

	// Variable of the least voltage measurement that can enable cell balancing.
	float minVoltageBalancingisEnabled;
	float maxVoltageBalancingisEnabled;

	// Limits of voltage and temperature measurements.
	float OVThreshold;// OverVoltage Threshold
	float UVThreshold;// UnderVoltage Threshold
	float OTThreshold;// OverTemperature Threshold
	float UTThreshold;// UnderTemperature Threshold
	float ITMPThreshold;// OverTemperature Threshold of the ADBMS ICs

	// Array of ICs structures. They store info and data from the ICs.
	cell_asic bmsIC[TOTAL_IC];

	// For display reasons
	float internalDieTemperature[TOTAL_IC];

	float temperatures[TOTAL_IC][TOTAL_ID_TEMP];
	float voltages[TOTAL_IC][STOP_MEASURE_CELL];

	uint8_t wifiIsConnected;
}BMSData;

typedef struct ACUData{


	float overCurrentThreshold;// Overcurrent threshold for the BMS to compare in order to open the shutdown system.

	// IMD Variables.
	errorState IMDHasError;// This flag is set if IMD has Error
	uint16_t IMDResistance;// The resistance measured between the low and high voltage.
	TIM_HandleTypeDef *IMDPWMCaptureTimer;
	float IMDPWMFrequency;
	float IMDPWMDutyCycle;
	uint32_t IMDPWMCaptureValue;

	// Add IMD Timer for pwm capture!
	uint32_t startPrechargeTime;

	uint16_t analogInputRawValues[3];
	float vicorThermistorTemperature;
	float vicorTemperature;
	float humidity;
	float PCBTemperature;

	//Flags
	uint16_t airMinusIsStuckFlag;
	uint16_t airPlusIsStuckFlag;
	uint8_t airsStuckAcceptedErrors;

	uint8_t airMinusIsStuck;// FLag that is raised when air minus is stuck.
	uint8_t airPlusIsStuck;// FLag that is raised when air minus is stuck.
	uint8_t DCBusOver60Volt;// FLag that is raised when DC-Bus voltage is over 60 Volt.
	uint8_t prechargeIsDone;// Flag that is raised when precharge of the inverter is done and there is high voltage outside the tsac
	uint8_t startPrecharge;	// Flag that starts the precharge sequence.

	// Pins
	Pin TSOver60Volt;
	Pin airPlusDriver;// Pin that drives airplus during precharge procedure.

	Pin startPrechargeAction;// Digital output to start hardware charge action precharge!

	Pin preAux;	// Digital input for Precharge relay auxilliary state.
	Pin airPlusAux;// Digital input for air plus relay auxilliary state.
	Pin airMinusAux;// Digital input for air minus relay auxilliary state.
	Pin airPlusSupply;// Digital input for AIR Plus Supply. It is used to detect if relay is stuck.
	Pin airMinusSupply;// Digital input for AIR Minus Supply. It is used to detect if relay is stuck.

	Pin IMDLatchedError;// Digital input of the latched state of the IMD in order to light the IMD Error on Dashboard.

	Pin fansControl;
	Pin SDCardIsDetected;

	Pin IMDIsOK;

	//SoC
	float soc;
	uint32_t sdSyncTime;
	uint8_t sdEnabled;
	uint8_t sdDisabled;
	bool usbConnected;
	uint8_t updateCellBalancingValue;
}ACUData;

extern volatile float socPercent;
extern volatile float remainingAh;

float callibrateBMSVoltage(float readValue, uint8_t currentSegment);
float map(float x, float in_min, float in_max, float out_min, float out_max);
void checkErrors(uint8_t tIC, BMSData *_bms, IsabellenData *_ivt, ACUData *_acu, FDCAN_HandleTypeDef *_hcan);
uint8_t calcCheckSum(uint8_t temp[8],uint8_t length);
uint8_t checkCheckSum(uint8_t temp[8],uint8_t length, uint8_t checkSumByte, ACUData *_acu);
void parseDischargeCells(cell_asic *_BMS_IC, BMSData *_bms);
//HAL_StatusTypeDef VicorInit(VicorData *_vicor, I2C_HandleTypeDef *_i2c);
HAL_StatusTypeDef ACUInit(ACUData *_acu,TIM_HandleTypeDef *_IMDPWMCaptureTimer, uint16_t _overCurrentThreshold);
HAL_StatusTypeDef powerVicor(VicorData _vicor,powerState _powerState);
HAL_StatusTypeDef BMSInit(BMSData *_bms, TIM_HandleTypeDef *_stopDisplayingTimer,
	TIM_HandleTypeDef * _communicationStartTimer, uint8_t _acceptedErrors,
	float _maxDiffbetweenCells, float _minVoltageBalancingIsEnabled, float _maxVoltageBalancingIsEnabled,
	float _overVoltageThreshold, float _underVoltageThreshold,
	float _OverTempThreshold, float _UnderTempThreshold);
HAL_StatusTypeDef ChargerInit(ChargerData *_charger,TIM_HandleTypeDef *_timeOutTimer);
HAL_StatusTypeDef IVTInit(IsabellenData *_ivt,TIM_HandleTypeDef *_timeOutTimer, uint8_t _SCSacceptedErrors);
void IVTChangeMode(FDCAN_HandleTypeDef *_hcan, ivtMode mode);
void IVTMeasurementConfig(FDCAN_HandleTypeDef *_hcan, ivtVariable measurement, uint16_t time);
void IVTRestartToDefaults(FDCAN_HandleTypeDef *_hcan);
void IVTRestartToBitrate(FDCAN_HandleTypeDef *_hcan, ivtBaudRate bitrate);
HAL_StatusTypeDef updateVicorData(VicorData *_vicor);
HAL_StatusTypeDef VicorInit(VicorData *_vicor);
HAL_StatusTypeDef readVicorData(VicorData *_vicor, vicorCommands cmd);
void writeVicorPage(VicorData *_vicor, uint8_t page);
void clearVicorFaults(VicorData *_vicor);
float thermistorCalculate(uint16_t adcValue);
float calculateSoC(uint64_t chAs, uint64_t dchAs);

#endif /* INC_DEVICES_H_ */
