/**
  * @file 	main.c
  * @brief APP Source file.
  *
  * This file contains The Application of Digital Multi Meter
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

/* ===================================================================================================
										   Includes
   ===================================================================================================*/
#include "app.h"

/* ===================================================================================================
                                                 Main Project
   ===================================================================================================*/

int main(void)
{
	/* Initialize system */
    APP_sysInit();

    /* Open digital multimeter */
    //APP_dmmOpen();

    LCD_moveCursor(0, 0);

    /* Variable to store pressed key, initialized to NO_INPUT_NUM */
    uint8 Pressedkey = NO_INPUT_NUM;

    /* Display "Select A Range" message on LCD In Start*/
    LCD_displayString("Select A Range");

    /* Infinite loop for continuous operation */
    for (;;)
    {
        /* Get the pressed key from the keypad */
        Pressedkey = KEYPAD_getPressedKey();

        /* Check if a key is pressed */
        if (Pressedkey != NO_INPUT_NUM)
        {
            /* Move cursor to First line to View Selected Range on LCD */
            LCD_moveCursor(0, 0);

            /* Set range according to the pressed key */
            APP_setRange(Pressedkey);
        }

        /* Move cursor to the Second line to view measured value */
        LCD_moveCursor(1, 0);

        /* Get value from digital multimeter and display it on LCD */
        APP_getValue();
    }
}
