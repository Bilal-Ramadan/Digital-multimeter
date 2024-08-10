/*
 * @file adc_Cfg.c
 * @brief source file for the Adc module configuration.
 *
 * This file contains the declarations and definitions for the Adc module in accordance
 * with the AUTOSAR standard.
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
#include "adc.h"
#include"adc_Cfg.h"
/*====================================================================================*/
const ADC_ConfigType ADC_Configuration =
{
		ADC_REF_AVCC,ADC_PRESCALLER_128
};
