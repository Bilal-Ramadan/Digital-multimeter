/**
 * @file 	keypad.c
 * @brief Keypad Source file.
 *
 * This file contains The Implementation of Functions of the Keypad module
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

/* ===================================================================================================
										   Includes
   ===================================================================================================*/
#include "keypad.h"
#include "gpio.h"
/* ===================================================================================================
									Static Function Prototypes
   ===================================================================================================*/
#ifndef STANDARD_KEYPAD

#if (KEYPAD_COL_NUM == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 Key_num);

#elif (KEYPAD_COL_NUM == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 Key_num);

#endif

#endif

/* ===================================================================================================
										Function Definition
   ===================================================================================================*/

   /**
	 *
	 * This Function Initializes the Keypad Pins
	 *
	 * @param[in]   none
	 * @param[out]  none
	 * @return none
	 */
void KEYPAD_init(void)
{
/* Setting up the direction of Row pins as Output */
GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID,   PIN_OUTPUT);
GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, PIN_OUTPUT);
GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, PIN_OUTPUT);
GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, PIN_OUTPUT);

/* Setting up the direction of Column pins as Input */
GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, PIN_INPUT);
GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, PIN_INPUT);
GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, PIN_INPUT);
#if(KEYPAD_COL_NUM == 4)
GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, PIN_INPUT);
#endif

/* Initilailzing the Row with initiale value which indicate no Button is Pressed  */
GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID, KEYPAD_BUTTON_RELEASED);
GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, KEYPAD_BUTTON_RELEASED);
GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, KEYPAD_BUTTON_RELEASED);
GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, KEYPAD_BUTTON_RELEASED);

//GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, LOGIC_HIGH);
//GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, LOGIC_HIGH);
//GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, LOGIC_HIGH);
//GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, LOGIC_HIGH);
}

/**
  *
  * This Function Get which Button is Pressed
  *
  * @param[in]   none
  * @param[out]  none
  * @return uint8
  */
uint8 KEYPAD_getPressedKey(void)
{
uint8 col, row, key = NO_INPUT_NUM;
/* Enable only one Row at atime and loop on the rows*/
for(row=0;row<KEYPAD_ROW_NUM;row++)
{
	/* Enabling the Row */
	GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);
	/* Looping on the columns to see if any of them detect a Button Pressed */
	for(col=0;col<KEYPAD_COL_NUM;col++)
	{
		if(GPIO_readPin(KEYPAD_COL_PORT_ID, (KEYPAD_FIRST_COL_PIN_ID + col))== KEYPAD_BUTTON_PRESSED)
		{
#if (KEYPAD_COL_NUM == 3)
						#ifdef STANDARD_KEYPAD
							key = ((row * KEYPAD_COL_NUM)+col+1);
						#else
							key =  KEYPAD_4x3_adjustKeyNumber((row * KEYPAD_COL_NUM)+col+1);
						#endif
#elif (KEYPAD_COL_NUM == 4)
						#ifdef STANDARD_KEYPAD
							key = ((row * KEYPAD_COL_NUM)+col+1);
						#else
							key =  KEYPAD_4x4_adjustKeyNumber((row * KEYPAD_COL_NUM)+col+1);
						#endif
#endif
							break;
		}
	}
	GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_RELEASED);
	_delay_ms(5);

}
return key;
}

#ifndef STANDARD_KEYPAD
#if (KEYPAD_COL_NUM == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 Key_num)
{
	uint8 keypad_button = 0;
	switch(Key_num)
		{
		case 10: keypad_button = '*'; // ASCII Code of *
				break;
		case 11: keypad_button = 0;
				break;
		case 12: keypad_button = '#'; // ASCII Code of #
				break;
		default: keypad_button = Key_num;
				break;
		}
	return keypad_button;
}
#elif (KEYPAD_COL_NUM == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 Key_num)
{
	uint8 keypad_button = 0;
	switch(Key_num)
	{
		case 1: keypad_button = 1;
				break;
		case 2: keypad_button = 2;
				break;
		case 3: keypad_button = 3;
				break;
		case 4: keypad_button = 13; /* ASCII Code of '/' */
				break;
		case 5: keypad_button = 4;
				break;
		case 6: keypad_button = 5;
				break;
		case 7: keypad_button = 6;
				break;
		case 8: keypad_button = 14; /* ASCII Code of '*' */
				break;
		case 9: keypad_button = 7;
				break;
		case 10: keypad_button = 8;
				break;
		case 11: keypad_button = 9;
				break;
		case 12: keypad_button = 15; /* ASCII Code of '-' */
				break;
		case 13: keypad_button = 10;  /* ASCII of Enter */
				break;
		case 14: keypad_button = 0;
				break;
		case 15: keypad_button = 12; /* ASCII Code of '=' */
				break;
		case 16: keypad_button = 16; /* ASCII Code of '+' */
				break;
		default: keypad_button = Key_num;
				break;
	}
	return keypad_button;
}
#endif

#endif

