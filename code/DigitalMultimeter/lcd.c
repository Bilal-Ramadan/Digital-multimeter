/**
 * @file 	lcd.c
 * @brief LCD Source file.
 *
 * This file contains The Implementation of Functions of the LCD module
  *
  * @author [Mohamed Mabrouk]
  * @date [10 FEB 2024]
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
#include "lcd.h"
#include "lcd_Cfg.h"
#include "gpio.h"
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "common_macros.h"


/* ===================================================================================================
										Function Definition
   ===================================================================================================*/

/**
 *
 * This function Initiallize the LCD .
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */

void LCD_init(void)
{
/* Set The RS Pin As Output */
GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);

/* Set The E Pin As Output */
GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

_delay_ms(20);    /* Delay 20 ms as LCD Need 15 ms to Startup */

#if (LCD_DATA_MODE==LCD_EIGHT_BIT_DATA_MODE)

/* Set The Data Port As Output */
GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);

/* initialize the lCD by 8 bit data mode */
LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);


#elif (LCD_DATA_MODE==LCD_FOUR_BIT_DATA_MODE)
/* initialize the lCD 4 bit Mode Pins */
GPIO_setupPinDirection(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN1, PIN_OUTPUT);
GPIO_setupPinDirection(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN2, PIN_OUTPUT);
GPIO_setupPinDirection(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN3, PIN_OUTPUT);
GPIO_setupPinDirection(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN4, PIN_OUTPUT);

/* initialize the lCD by 4 bit data Mode */
LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

/* Use 2-lines LCD and 4 Bit Mode */
LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#endif

/* Set cursor and clear the screen */
LCD_sendCommand(LCD_CURSOR_OFF);
LCD_sendCommand(LCD_CLEAR_SCREEN);

}

/**
 *
 * This function Send the Required Command to be used.
 *
 * @param[in]  a_command     Type uint8     Range 0x00:0xFF
 * @return none
 */
void LCD_sendCommand(uint8 a_command)
{
GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
_delay_ms(1);  /* delay for processing Tas = 50ns */
GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
_delay_ms(1);  /* delay for processing Tpw - Tdws = 190ns */
#if (LCD_DATA_MODE==LCD_EIGHT_BIT_DATA_MODE)
GPIO_writePort(LCD_DATA_PORT_ID, a_command);
_delay_ms(1); /* delay for processing Tdsw = 100ns */
GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
_delay_ms(1); /* delay for processing Th = 13ns */

#elif (LCD_DATA_MODE==LCD_FOUR_BIT_DATA_MODE)

GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN1, GET_BIT(a_command,4));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN2, GET_BIT(a_command,5));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN3, GET_BIT(a_command,6));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN4, GET_BIT(a_command,7));

_delay_ms(1); /* delay for processing Tdsw = 100ns */
GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
_delay_ms(1); /* delay for processing Th = 13ns */
GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN1, GET_BIT(a_command,0));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN2, GET_BIT(a_command,1));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN3, GET_BIT(a_command,2));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN4, GET_BIT(a_command,3));

_delay_ms(1); /* delay for processing Tdsw = 100ns */
GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

/**
 *
 * This function Displayed the send Character.
 *
 * @param[in]  a_data     Type uint8     Range 0x00:0xFF
 * @return none
 */

void LCD_displayCharacter(uint8 a_data)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	_delay_ms(1); /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1); /* delay for processing Th = 13ns */
#if (LCD_DATA_MODE==LCD_EIGHT_BIT_DATA_MODE)
	GPIO_writePort(LCD_DATA_PORT_ID, a_data);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#elif (LCD_DATA_MODE==LCD_FOUR_BIT_DATA_MODE)
/*sending the High 4 bits First*/
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN1, GET_BIT(a_data,4));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN2, GET_BIT(a_data,5));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN3, GET_BIT(a_data,6));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN4, GET_BIT(a_data,7));

/*  Then Set E=0 And ReEnable E=1 To send the Low 4 bits*/
_delay_ms(1); /* delay for processing Tdsw = 100ns */
GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
_delay_ms(1); /* delay for processing Th = 13ns */
GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

/*sending the Low 4 bits*/
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN1, GET_BIT(a_data,0));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN2, GET_BIT(a_data,1));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN3, GET_BIT(a_data,2));
GPIO_writePin(LCD_FOUR_BIT_DATA_PORT_ID, LCD_FOUR_BIT_PIN4, GET_BIT(a_data,3));

_delay_ms(1); /* delay for processing Tdsw = 100ns */
GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
_delay_ms(1); /* delay for processing Th = 13ns */
#endif

}

/**
 *
 * This function Displayed the send String.
 *
 * @param[in]  string     Type uint8 *
 * @return none
 */

void LCD_displayString(const char * string)
{
uint8 i=0;
while(string[i]!='\0')
{
	LCD_displayCharacter(string[i]);
	i++;
}
}

/**
 *
 * This function Move the Cursor to a Specific place.
 *
 * @param[in]  row     Type uint8     Range 0x00:0x0F
 * @param[in]  column  Type uint8     Range 0x00:0x01
 * @return none
 */
void LCD_moveCursor(uint8 row ,uint8 column)
{

uint8 Cursor_address=0;
switch(row)
{
case 0:
	Cursor_address=column;  		/* Case being in the row 0 address start with 0x00 */
	break;
case 1:
	Cursor_address=column+0x40;		/* Case being in the row 1 address start with 0x40 */
	break;
case 2:
	Cursor_address=column+0x10;		/* Case being in the row 2 address start with 0x10 */
	break;
case 3:
	Cursor_address=column+0x50;		/* Case being in the row 3 address start with 0x50 */
	break;
default:
	/* Wrong Input*/
	break;
}
/* Move the Cursor to a Specific place */
LCD_sendCommand(Cursor_address | LCD_SET_CURSOR_LOCATION);
}

/**
 *
 * This function Display the required string in a specified row and column index on the screen.
 *
 * @param[in]  row     Type uint8     Range 0x00:0x0F
 * @param[in]  column  Type uint8     Range 0x00:0x01
 * @param[in]  string     Type uint8 *
 * @return none
 */

void LCD_displayStringRowColumn(uint8 row, uint8 column, const char *str)
{
	/* Move the Cursor to a Specific place */
	LCD_moveCursor(row,column);
	/* Display the send String */
	LCD_displayString(str);
}

/**
 *
 * This function Clears the screen and automatically return the Cursor to the beginning.
 *
 * @param[in]  none
 * @return none
 */

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}

/**
 *
 * This function Display the required decimal value on the screen.
 *
 * @param[in]  none
 * @return none
 */
void LCD_intgerToString(int data)
{
char buff[16];
/* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
itoa(data,buff,10);
/* Display the String */
LCD_displayString(buff);
}


void LCD_floatToString(float32 data,uint8 decimal_places)
{
	    // Convert float to string with specified decimal places
	    char buffer[20];
	    dtostrf(data, 5, decimal_places, buffer);

	    // Display the string on LCD
	    LCD_displayString(buffer);
}
