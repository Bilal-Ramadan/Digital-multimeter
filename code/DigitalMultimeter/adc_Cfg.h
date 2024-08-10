/**
 * @file 	adc_Cfg.h
 * @brief ADC Configratuions Header File.
 *
 * This file contains the Configratuions for the ADC module
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
#ifndef ADC_CFG_H_
#define ADC_CFG_H_

#define NUMBER_ADC_CHANNEL_USED         1

/* ADC Static Configratuions*/
/*
 * Options:
 * ADC_POLLING
 * ADC_INTERRUPT
 * */
#define ADC_CALLING_TYPE 				ADC_POLLING

#endif /* ADC_CFG_H_ */
