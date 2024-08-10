/**
 * @file 	app.h
 * @brief APP Header file.
 *
 * This file contains the declarations and definitions for the Application
 *
 * @author [RISC-Takers]
 * @date [2 MAR 2024]
 *
 * @SWversion 1.0.0
 *
 * @remarks
 *    -Platform         : AVR
 *    -Peripherial      : Atmega32
 */
/*==================================================================================================================================*/
#ifndef APP_H_
#define APP_H_

/* ===================================================================================================
										   Includes
   ===================================================================================================*/
#include"lcd.h"
#include"keypad.h"
#include"util/delay.h"
#include"gpio.h"
#include"adc.h"


/* ===================================================================================================
                                        Macro Definition
   ===================================================================================================*/

/* 					VoltMeter					 */

/**
  * @brief the Ratio to use in the 3rd voltage Range Equation
  *
  * @details
  * - Type: define
  * - Range: 11U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define VOLT_RANGE3_RATIO     5
/**
  * @brief the Ratio to use in the 4th voltage Range Equation
  *
  * @details
  * - Type: define
  * - Range: 101U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define VOLT_RANGE4_RATIO     50
/**
  * @brief Voltage range 20 - 200 V key
  *
  * @details
  * - Type: define
  * - Range: 13
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_V_20_200   		  13

/**
  * @brief Voltage range 2 - 20 V key
  *
  * @details
  * - Type: define
  * - Range: 3
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_V_4_20     		  3

/**
  * @brief Voltage range 0.2 - 2 V key
  *
  * @details
  * - Type: define
  * - Range: 2
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_V_800m_4          2

/**
  * @brief Voltage range 1m - 0.2 V key
  *
  * @details
  * - Type: define
  * - Range: 1
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_V_1m_800m         1

/* 					Ameter					 */

/**
  * @brief Current range 450m - 2 A key
  *
  * @details
  * - Type: define
  * - Range: 14
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_A_50m_1          14

/**
  * @brief Current range 450m - 2 A Second key
  *
  * @details
  * - Type: define
  * - Range: 6
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_A_50m_1_BUT2     6

/**
  * @brief Current range 40m - 450m A key
  *
  * @details
  * - Type: define
  * - Range: 5
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_A_10m_50m        5

/**
  * @brief Current range 1m - 40m A key
  *
  * @details
  * - Type: define
  * - Range: 4
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_A_1m_10m          4


/* 					OhmMeter					 */

/**
  * @brief Resistance range 50K - 1M Ohm key
  *
  * @details
  * - Type: define
  * - Range: 15
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_R_50K_1M          15

/**
  * @brief Resistance range 50K - 1M Ohm Second key
  *
  * @details
  * - Type: define
  * - Range: 9
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_R_50K_1M_BUT2          9

/**
  * @brief Resistance range 1K - 50K Ohm key
  *
  * @details
  * - Type: define
  * - Range: 8
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_R_1K_50K          8

/**
  * @brief Resistance range 100 - 1K Ohm key
  *
  * @details
  * - Type: define
  * - Range: 7
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_R_400_1K          7

/* 					General					 */

/**
  * @brief AC MODE IS OFF
  *
  * @details
  * - Type: define
  * - Range: 0U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define AC_OFF 				  0
/**
  * @brief AC MODE IS ON
  *
  * @details
  * - Type: define
  * - Range: 1U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define AC_ON 				  1

/**
  * @brief DC mode key
  *
  * @details
  * - Type: define
  * - Range: 16
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_AC_OFF            16

/**
  * @brief AC mode key
  *
  * @details
  * - Type: define
  * - Range: 12
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define KEY_AC_ON             12

/**
  * @brief Password is incorrect State
  *
  * @details
  * - Type: define
  * - Range: 0
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define PASS_INCORRECT 		  0

/**
  * @brief Password is correct State
  *
  * @details
  * - Type: define
  * - Range: 1
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define PASS_CORRECT    	  1


/**
  * @brief Digital Multi Meter is closed State
  *
  * @details
  * - Type: define
  * - Range: 0
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define DMM_CLOSED			  0

/**
  * @brief Digital Multi Meter is opened State
  *
  * @details
  * - Type: define
  * - Range: 1
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define DMM_OPENED		 	  1

/**
  * @brief Maximum number of digits for password
  *
  * @details
  * - Type: define
  * - Range: 7
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define MAX_NUM_OF_DIGITS 	  7

/**
  * @brief Number of samples for AC measurements
  *
  * @details
  * - Type: define
  * - Range: 1
  * - Resolution: Fixed
  * - Unit: Bits
  */

#define Get_Real_Volt() ((ADC_readChannel(ADC_CHANNEL0) * ADC_REF_VOLT_VALUE / ADC_MAXIMUM_VALUE))

/* ===================================================================================================
										Types Declaration
   ===================================================================================================*/
/**
	* @brief Enumeration for Ranges Switch Selections.
	*
	*
	* @details
	* - Type: enum
	* - Range: 3,5,8,12,16,20,24,28,44,76,108,204,236
	* - Resolution: 1U
	* - Unit: Bits
	*/
typedef enum
{
  VOLT_RANGE_20_200 				= 0b00000011,
  VOLT_RANGE_4_20 					= 0b00000101,
  VOLT_RANGE_800MILLI_4 			= 0b00001000,
  VOLT_RANGE_200MILLI_800MILLI  	= 0b00001100,
  VOLT_RANGE_1MILLI_200MILLI	    = 0b00011100,

  AMP_RANGE_1MILLI_10MILLI 			= 0b11011100,
  AMP_RANGE_10MILLI_50MILLI 		= 0b11001100,
  AMP_RANGE_50MILLI_1		 		= 0b01001100,

  RES_RANGE_400_1K 					= 0b00110000,
  RES_RANGE_1K_50K 					= 0b00110100,
  RES_RANGE_50K_1M 					= 0b00111000

} Ranges_Sel;

/* ===================================================================================================
                                             Function Prototypes
   ===================================================================================================*/

/**
 *
 * This function Initiallizes the System Modules
 *
 * @param[in]  none
 * @param[out]  none
 * @return none
 */
void APP_sysInit(void);

/**
 *
 * This function Choose the Range Based on the Pressed Key of Keypad.
 *
 * @param[in]  none
 * @param[out]  none
 * @return none
 */
void APP_setRange(uint8 Pressedkey);

/**
 *
 * This function Calculate the value Based on chosen range.
 *
 * @param[in]  none
 * @param[out]  none
 * @return none
 */
void APP_getValue(void);

/**
 * @brief Checks the entered password.
 *
 * @param[in]  none
 * @param[out] none
 * @return uint8
 */
uint8 APP_passwordCheck(void);

/**
 * @brief Opens the Digital Multimeter and Check Password.
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void APP_dmmOpen(void);

/**
 * @brief Calculates the AC value based on the chosen range.
 *
 * This function calculates the AC value by sampling the ADC for a certain number
 * of iterations and selecting the maximum value obtained during the sampling.
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void APP_getValueAC(void);


#endif /* APP_H_ */

