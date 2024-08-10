/**
 * @file 	adc.h
 * @brief ADC Header file.
 *
 * This file contains the declarations and definitions for the ADC module
 *
 * @author [Mohamed Mabrouk]
 * @date [16 FEB 2024]
 *
 * @SWversion 1.0.0
 *
 * @remarks
 *    -Platform         : AVR
 *    -Peripherial      : Atmega32
 */
  /*==================================================================================================================================*/
#ifndef ADC_H_
#define ADC_H_

/* ===================================================================================================
										   Includes
   ===================================================================================================*/
#include"std_types.h"
#include"adc_Regs.h"
#include"adc_Cfg.h"
/* ===================================================================================================
	     						   	    Macro Definition
   ===================================================================================================*/
   /**
	 * @brief Adc precision
	 *
	 * @details
	 * - Type: define
	 * - Range: 1024U
	 * - Resolution: Fixed
	 * - Unit: Bits
	 */
#define ADC_MAXIMUM_VALUE    1024.0
	 /**
	   * @brief Adc used Reference Volt
	   *
	   * @details
	   * - Type: define
	   * - Range: 5U
	   * - Resolution: Fixed
	   * - Unit: Bits
	   */
#define ADC_REF_VOLT_VALUE   5.0

/* Adc Reading Options*/
#define ADC_POLLING						0
#define ADC_INTERRUPT 					1
/* ===================================================================================================
										Types Declaration
   ===================================================================================================*/

   /**
	* @brief Enumeration for Adc Prescaler.
	*
	*
	* @details
	* - Type: enum
	* - Range: 0:7
	* - Resolution: 1U
	* - Unit: Bits
	*/
typedef enum
{
	ADC_PRESCALLER_2 = 0,
	ADC_PRESCALLER_4 = 2,
	ADC_PRESCALLER_8 ,
	ADC_PRESCALLER_16 ,
	ADC_PRESCALLER_32 ,
	ADC_PRESCALLER_64 ,
	ADC_PRESCALLER_128
}ADC_Prescaler;

/**
	* @brief Enumeration for Adc Reference Volt.
	*
	*
	* @details
	* - Type: enum
	* - Range: 0:3
	* - Resolution: 1U
	* - Unit: Bits
	*/
typedef enum
{
	ADC_REF_AREF,
	ADC_REF_AVCC,
	ADC_REF_INTERNAL = 3
}ADC_RefVolt;

/**
	* @brief Enumeration for Adc Channels.
	*
	*
	* @details
	* - Type: enum
	* - Range: 0:28
	* - Resolution: 1U
	* - Unit: Bits
	*/
typedef enum
{
	ADC_CHANNEL0,
	ADC_CHANNEL1,
	ADC_CHANNEL2,
	ADC_CHANNEL3,
	ADC_CHANNEL4,
	ADC_CHANNEL5,
	ADC_CHANNEL6,
	ADC_CHANNEL7,
	ADC_DIFF_CHANNEL0_CHANNEL_0_10X,
	ADC_DIFF_CHANNEL1_CHANNEL_0_10X,
	ADC_DIFF_CHANNEL0_CHANNEL_0_200X,
	ADC_DIFF_CHANNEL1_CHANNEL_0_200X,
	ADC_DIFF_CHANNEL2_CHANNEL_2_10X,
	ADC_DIFF_CHANNEL3_CHANNEL_2_10X,
	ADC_DIFF_CHANNEL2_CHANNEL_2_200X,
	ADC_DIFF_CHANNEL3_CHANNEL_2_200X,
	ADC_DIFF_CHANNEL0_CHANNEL_1_1X,
	ADC_DIFF_CHANNEL1_CHANNEL_1_1X,
	ADC_DIFF_CHANNEL2_CHANNEL_1_1X,
	ADC_DIFF_CHANNEL3_CHANNEL_1_1X,
	ADC_DIFF_CHANNEL4_CHANNEL_1_1X,
	ADC_DIFF_CHANNEL5_CHANNEL_1_1X,
	ADC_DIFF_CHANNEL6_CHANNEL_1_1X,
	ADC_DIFF_CHANNEL7_CHANNEL_1_1X,
	ADC_DIFF_CHANNEL0_CHANNEL_2_1X,
	ADC_DIFF_CHANNEL1_CHANNEL_2_1X,
	ADC_DIFF_CHANNEL2_CHANNEL_2_1X,
	ADC_DIFF_CHANNEL3_CHANNEL_2_1X,
	ADC_DIFF_CHANNEL4_CHANNEL_2_1X

}ADC_Channel;

typedef struct
{
	ADC_RefVolt RefVoltSource;
	ADC_Prescaler Prescaler;

}ADC_ConfigType;

extern const ADC_ConfigType ADC_Configuration ;

#if (ADC_CALLING_TYPE == ADC_INTERRUPT)
extern uint16 g_AdcValue;
#endif
/* ===================================================================================================
										Function Prototypes
   ===================================================================================================*/

/**
 *
 * This Function responsible for initialize the ADC driver.
 *
 * @param[in]  Config_Ptr Type ADC_ConfigType
 * @param[out] none
 * @return none
 */
void ADC_init(const ADC_ConfigType *Config_Ptr);

#if (ADC_CALLING_TYPE == ADC_POLLING)
/**
 *
 * This function Reads the Analog Value Of a Specific Channel .
 *
 * @param[in]  Channel     Type ADC_Channel     Range 0:28
 * @param[out] none
 * @return	   uint16
 */
uint16 ADC_readChannel(const ADC_Channel channel);

#elif (ADC_CALLING_TYPE == ADC_INTERRUPT)

/**
 *
 * This function Reads the Analog Value Of a Specific Channel .
 *
 * @param[in]  Channel     Type ADC_Channel     Range 0:28
 * @param[out] none
 * @return none
 */
void ADC_readChannel(ADC_Channel channel);

void __vector_16(void) __attribute__((signal));
#endif


#endif /* ADC_H_ */
