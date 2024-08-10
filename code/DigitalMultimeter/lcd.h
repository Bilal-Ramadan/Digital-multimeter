/**
  * @file lcd.h
  * @brief Header file for the LCD module.
  *
  * This file contains the declarations and definitions for the LCD module
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

#ifndef LCD_H_
#define LCD_H_
/* ===================================================================================================
										   Includes
   ===================================================================================================*/

#include"Std_Types.h"

/* ===================================================================================================
										Macro Definition
   ===================================================================================================*/

/* LCD Commands */
#define LCD_CLEAR_SCREEN                     0x01
#define LCD_GO_TO_HOME                       0x02
#define DISPLAY_OFF_CURSOR_OFF				 0x08
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define CURSOR_SHIFT_LEFT 					 0x10
#define CURSOR_SHIFT_RIGHT 					 0x14
#define DISPLAY_SHIT_LEFT 					 0x18
#define DISPLAY_SHIFT_RIGHT 				 0x1C
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_SET_CURSOR_LOCATION              0x80

#define LCD_EIGHT_BIT_DATA_MODE 8
#define LCD_FOUR_BIT_DATA_MODE  4

/* ===================================================================================================
										Function Prototypes
   ===================================================================================================*/
/**
 *
 * This function Initiallize the LCD .
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void LCD_init(void);
/**
 *
 * This function Send the Required Command to be used.
 *
 * @param[in]  a_command     Type uint8     Range 0x00:0xFF
 * @return none
 */
void LCD_sendCommand(uint8 a_command);
/**
 *
 * This function Displayed the send Character.
 *
 * @param[in]  a_data     Type uint8     Range 0x00:0xFF
 * @return none
 */
void LCD_displayCharacter(uint8 a_data);
/**
 *
 * This function Displayed the send String.
 *
 * @param[in]  string     Type uint8 *
 * @return none
 */
void LCD_displayString(const char * string);
/**
 *
 * This function Move the Cursor to a Specific place.
 *
 * @param[in]  row     Type uint8     Range 0x00:0x0F
 * @param[in]  column  Type uint8     Range 0x00:0x01
 * @return none
 */
void LCD_moveCursor(uint8 row ,uint8 column);
/**
 *
 * This function Display A string in a Specific Place.
 *
 * @param[in]  row     Type uint8     Range 0x00:0x0F
 * @param[in]  column  Type uint8     Range 0x00:0x01
 * @param[in]  string     Type uint8 *
 * @return none
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *str);
/**
 *
 * This function Clears the screen and automatically return the Cursor to the beginning.
 *
 * @param[in]  none
 * @return none
 */
void LCD_clearScreen(void);

void LCD_intgerToString(int data);

void LCD_floatToString(float32 data,uint8 decimal_places);
#endif /* LCD_H_ */
