/**
 * @file gpio_Regs.h
 * @brief Header file for the GPIO Registers.
 *
 * This file contains the Registers for the GPIO module
 *
 * @author [Mohamed Mabrouk]
 * @date [29 DEC 2023]
 *
 * @SWversion 1.0.0
 *
 * @remarks
 *    -Platform         : AVR
 *    -Peripherial      : Atmega32
 */
 /*==================================================================================================================================*/
#ifndef GPIO_REGS_H_
#define GPIO_REGS_H_
/* ===================================================================================================
											  Includes
   ===================================================================================================*/
#include "Std_Types.h"
 /* ===================================================================================================
											GPIO Registers
	===================================================================================================*/
/* GPIO A*/
#define PORTA *((volatile uint8* const)(0x3B))
#define DDRA  *((volatile uint8* const)(0x3A))
#define PINA  *((volatile const uint8* const)(0x39))

/* GPIO B*/
#define PORTB *((volatile uint8* const)(0x38))
#define DDRB  *((volatile uint8* const)(0x37))
#define PINB  *((volatile const uint8* const)(0x36))

/* GPIO C*/
#define PORTC *((volatile uint8* const)(0x35))
#define DDRC  *((volatile uint8* const)(0x34))
#define PINC  *((volatile const uint8* const)(0x33))

/* GPIO D*/
#define PORTD *((volatile uint8* const)(0x32))
#define DDRD  *((volatile uint8* const)(0x31))
#define PIND  *((volatile const uint8* const)(0x30))

#endif
