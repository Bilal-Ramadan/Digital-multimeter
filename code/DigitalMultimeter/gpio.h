/**
  * @file Gpio.h
  * @brief Header file for the GPIO module.
  *
  * This file contains the declarations and definitions for the GPIO module
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

 /**
 * \mainpage
 * \section Brief
 * This file includes headers and functions for the GPIO.
 * \section SoftwareContext
 * This service initializes GPIO I/O PINS with their different modes, initial states, and configurations.
 *
 * \section Creation
 * @startuml
 * json "<b>Creation" as J {
 * "Names": "Mohamed Mabrouk",
 * "Date": "29 DEC 2023",
 * "Driver type": "GPIO",
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
 * agent GPIO
 * GPIO --> GPIO_setupPinDirection #line:green;line.bold;text:green : Initializes the Gpio direction Pin
 * GPIO --> GPIO_writePin #line:green;line.bold;text:green : Write any Gpio Pin by a value
 * GPIO --> GPIO_readPin #line:green;line.bold;text:green : Read a Gpio Pin value
 * GPIO --> GPIO_setupPortDirection #line:green;line.bold;text:green :Initializes the Gpio direction Port
 * GPIO --> GPIO_writePort #line:green;line.bold;text:green : Write any Gpio Port by a value
 * GPIO --> GPIO_readPort #line:green;line.bold;text:green : Read a Gpio Port value
 * @enduml
 */

#ifndef GPIO_H_
#define GPIO_H_

/* ===================================================================================================
										   Includes
   ===================================================================================================*/
#include"Std_Types.h"
#include"Common_Macros.h"
#include"gpio_Regs.h"
/* ===================================================================================================
										Macro Definition
   ===================================================================================================*/
 /**
  * @brief Maximum number of Ports in MCU
  *
  * @details
  * - Type: define
  * - Range: 4U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define NUM_OF_PORTS            4
 /**
  * @brief Maximum number of pins per Ports in MCU
  *
  * @details
  * - Type: define
  * - Range: 8U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define NUM_OF_PINS_PER_PORT    8
 /**
  * @brief Setting a complete Register
  *
  * @details
  * - Type: define
  * - Range: 0xFFU
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define HIGH_REG 0xFF

/* ===================================================================================================
										Types Declaration
   ===================================================================================================*/

   /**
	* @brief Enumeration for Pin Type.
	*
	*
	* @details
	* - Type: enum
	* - Range: 0:7
	* - Resolution: 1U
	* - Unit: Bits
	*/
typedef enum
{
	PIN0_ID,
	PIN1_ID,
	PIN2_ID,
	PIN3_ID,
	PIN4_ID,
	PIN5_ID,
	PIN6_ID,
	PIN7_ID
}GPIO_Pin;

/**
	* @brief Enumeration for Port Type.
	*
	*
	* @details
	* - Type: enum
	* - Range: 0:3
	* - Resolution: 1U
	* - Unit: Bits
	*/
typedef enum
{
	PORTA_ID,
	PORTB_ID,
	PORTC_ID,
	PORTD_ID
}GPIO_Port;

/**
	* @brief Enumeration for Pin Direction type.
	*
	* @details
	* - Type: enum
	* - Range: 0:1
	* - Resolution: 1U
	* - Unit: Bits
	*/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirection;

/**
	* @brief Enumeration for Port Direction type.
	*
	* @details
	* - Type: enum
	* - Range: 0,0xFF
	* - Resolution: 1U
	* - Unit: Bits
	*/
typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirection;

/* ===================================================================================================
										Function Prototypes
   ===================================================================================================*/
/**
 *
 * Setup the direction of the required pin input/output..
 *
 * @param[in]  port_num     Type GPIO_Port     Range 0:3
 * @param[in]  pin_num      Type GPIO_Pin      Range 0:7
 * @param[in]  direction    Type uint8         Range 0:255
 * @return none
 */
void GPIO_setupPinDirection(const GPIO_Port a_port_num,const GPIO_Pin a_pin_num,uint8 a_direction);

/**
 *
 * This function Write the Pin with value Logic High or Logic Low.
 *
 * @param[in]  port_num     Type GPIO_Port     Range 0:3
 * @param[in]  pin_num      Type GPIO_Pin      Range 0:7
 * @param[in]  direction    Type uint8         Range 0:255
 * @return none
 */
void GPIO_writePin(const GPIO_Port a_port_num,const GPIO_Pin a_pin_num,uint8 a_level);
/**
 *
 * This function Read and return the value for the required pin.
 *
 * @param[in]  port_num     Type GPIO_Port     Range 0:3
 * @param[in]  pin_num      Type GPIO_Pin      Range 0:7
 * @return none
 */
uint8 GPIO_readPin(const GPIO_Port a_port_num,const GPIO_Pin a_pin_num);

/**
 *
 * This function Setup the direction of the required port all pins input/output.
 *
 * @param[in]  port_num     Type GPIO_Port     Range 0:3
 * @param[in]  direction    Type uint8         Range 0:255
 * @return none
 */
void GPIO_setupPortDirection(const GPIO_Port a_port_num, uint8 a_direction);

/**
 *
 * This function Write the value on the required port.
 *
 * @param[in]  port_num     Type GPIO_Port     Range 0:3
 * @param[in]  Level        Type uint8         Range 0:255
 * @return none
 */
void GPIO_writePort(const GPIO_Port a_port_num, uint8 a_level);

/**
 *
 * This function Read and return the value of the required port.
 *
 * @param[in]  port_num     Type GPIO_Port     Range 0:3
 * @return none
 */
uint8 GPIO_readPort(const GPIO_Port a_port_num);

#endif /* GPIO_H_ */
