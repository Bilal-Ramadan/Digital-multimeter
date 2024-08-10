/**
 * @file adc_Regs.h
 * @brief Header file for the ADC Registers.
 *
 * This file contains the Registers for the ADC module
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
#ifndef ADC_REGS_H_
#define ADC_REGS_H_
/* ===================================================================================================
											  Includes
   ===================================================================================================*/
#include "Std_Types.h"
/* ===================================================================================================
											ADC Registers
   ===================================================================================================*/
#define ADMUX  *((volatile uint8* const)(0x27))
#define ADCSRA *((volatile uint8* const)(0x26))

#define ADCH   *((volatile uint8* const)(0x25))
#define ADCL   *((volatile uint8* const)(0x24))
#define ADC    *((volatile uint16* const)(0x24))

#ifndef SREG
#define SREG   *((volatile uint8* const)(0x5F))
#define IBIT 7
#endif

/* ADMUX */
#define REFS1 7
#define REFS0 6
#define ADLAR 5
#define MUX4 4
#define MUX3 3
#define MUX2 2
#define MUX1 1
#define MUX0 0

/* ADCSRA */
#define ADEN 7
#define ADSC 6
#define ADATE 5
#define ADIF 4
#define ADIE 3
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0
#endif /* ADC_REGS_H_ */
