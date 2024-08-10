/**
  * @file keypad.h
  * @brief  Pre-Compile Configuration Header file for the Keypad module.
  *
  * This file contains the  Pre-Compile Configuration for the Keypad module
  *
  * @author [Mohamed Mabrouk]
  * @date [11 FEB 2024]
  *
  * @SWversion 1.0.0
  *
  * @remarks
  *    -Platform         : AVR
  *    -Peripherial      : Atmega32
  */
  /*==================================================================================================================================*/


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

/* ===================================================================================================
										Macro Definition
   ===================================================================================================*/
/* Use Standard keypad type */
/* #define STANDARD_KEYPAD */

/* Keypad Size */
#define KEYPAD_COL_NUM 4
#define KEYPAD_ROW_NUM 4

/* Keypad Pins ID */
#define KEYPAD_ROW_PORT_ID                PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID           PIN0_ID

#define KEYPAD_COL_PORT_ID                PORTA_ID
#define KEYPAD_FIRST_COL_PIN_ID           PIN3_ID

/*  Pull up or Down */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH




#endif /* KEYPAD_CFG_H_ */
