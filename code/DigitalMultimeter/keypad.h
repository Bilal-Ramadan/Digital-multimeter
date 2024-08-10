/**
  * @file keypad.h
  * @brief Header file for the Keypad module.
  *
  * This file contains the declarations and definitions for the Keypad module
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


#ifndef KEYPAD_H_
#define KEYPAD_H_

/* ===================================================================================================
										   Includes
   ===================================================================================================*/

#include"Std_Types.h"
#include "keypad_Cfg.h"
#include"common_macros.h"
#include <util/delay.h>

   /**
   * \mainpage
   * \section Brief
   * This file includes headers and functions for the KEYPAD.
   * \section SoftwareContext
   * This service initializes The Keypad and Get the Pressed Button.
   *
   * \section Creation
   * @startuml
   * json "<b>Creation" as J {
   * "Names": "Mohamed Mabrouk",
   * "Date": "11 FEB 2024",
   * "Driver type": "KEYPAD",
   * "Version": "V1.0"
   * }
   * @enduml
   *
   * \section References
   * @startuml
   * json "<b>References" as J {
   * "First reference": "Atmega32",
   * "Second reference": "Web page plantuml.com"
   * }
   * @enduml
   *
   *
   * \section Functions Description
   * @startuml
   * agent KEYPAD
   * KEYPAD --> KEYPAD_init #line:green;line.bold;text:green : Initializes the Keypad Pins
   * KEYPAD --> KEYPAD_getPressedKey #line:green;line.bold;text:green : It get which key in the KeyPad is pressed
   * @enduml
   */

/* ===================================================================================================
										Macro Definition
   ===================================================================================================*/
#define NO_INPUT_NUM 50
/* ===================================================================================================
										Function Prototypes
   ===================================================================================================*/
 /**
   *
   * This Function Initializes the Keypad Pins
   *
   * @param[in]   none
   * @param[out]  none
   * @return none
   */
void KEYPAD_init(void);
/**
  *
  * This Function Get which Button is Pressed 
  *
  * @param[in]   none
  * @param[out]  none
  * @return uint8
  */
uint8 KEYPAD_getPressedKey(void);


#endif /* KEYPAD_H_ */
