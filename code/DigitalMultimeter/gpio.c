/**
 * @file 	gpio.c
 * @brief GPIO Source file.
 *
 * This file contains The Implementation of Functions of the GPIO module
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

/* ===================================================================================================
										   Includes
   ===================================================================================================*/

#include "gpio.h"

/* ===================================================================================================
										Function Definition
   ===================================================================================================*/

void GPIO_setupPinDirection(const GPIO_Port a_port_num, const GPIO_Pin a_pin_num, uint8 a_direction)
{
	if(a_port_num >= NUM_OF_PORTS || a_pin_num >= NUM_OF_PINS_PER_PORT)
	{
		/* Wrong Input*/
	}
	else
	{
		  switch(a_port_num)
	  {
		case PORTA_ID:
			if(a_direction==PIN_OUTPUT)
			{
				SET_BIT(DDRA,a_pin_num);/* Setting the Required pin on DDR Register to be output*/
			}
			else if(a_direction==PIN_INPUT)
			{
				CLR_BIT(DDRA,a_pin_num);/* Clearing the Required pin on DDR Register to be input*/
			}
			else
			{
				/*Wrong a_direction Error*/
			}
			break;
		case PORTB_ID:
			if(a_direction==PIN_OUTPUT)
				{
					SET_BIT(DDRB,a_pin_num);/* Setting the Required pin on DDR Register to be output*/
				}
				else if(a_direction==PIN_INPUT)
				{
					CLR_BIT(DDRB,a_pin_num);/* Clearing the Required pin on DDR Register to be input*/
				}
				else
				{
					/*Wrong a_direction Error*/
				}
				break;
		case PORTC_ID:
			if(a_direction==PIN_OUTPUT)
				{
					SET_BIT(DDRC,a_pin_num);/* Setting the Required pin on DDR Register to be output*/
				}
				else if(a_direction==PIN_INPUT)
				{
					CLR_BIT(DDRC,a_pin_num);/* Clearing the Required pin on DDR Register to be input*/
				}
				else
				{
					/*Wrong a_direction Error*/
				}
				break;
		case PORTD_ID:
			if(a_direction==PIN_OUTPUT)
				{
					SET_BIT(DDRD,a_pin_num);/* Setting the Required pin on DDR Register to be output*/
				}
				else if(a_direction==PIN_INPUT)
				{
					CLR_BIT(DDRD,a_pin_num);/* Clearing the Required pin on DDR Register to be input*/
				}
				else
				{
					/*Wrong a_direction Error*/
				}
					break;
		default:
			/*Wrong Port Error*/
		break;
	  }
	  }
	}

void GPIO_writePin(const GPIO_Port a_port_num, const GPIO_Pin a_pin_num, uint8 a_level)
{
	if(a_port_num >= NUM_OF_PORTS || a_pin_num >= NUM_OF_PINS_PER_PORT)
	{
		/* Wrong Input*/
	}
	else
	{
		  switch(a_port_num)
	  {
		case PORTA_ID:
			if(a_level == LOGIC_HIGH)
			{
				SET_BIT(PORTA,a_pin_num);/* Setting the Required pin on Port Register to Output a High logic 1 */
			}
			else
			{
				CLR_BIT(PORTA,a_pin_num);/* clearing the Required pin on Port Register to Output a low logic 0 */
			}
			break;
		case PORTB_ID:
			if(a_level == LOGIC_HIGH)
			{
				SET_BIT(PORTB,a_pin_num);/* Setting the Required pin on Port Register to Output a High logic 1 */
			}
			else
			{
				CLR_BIT(PORTB,a_pin_num);/* clearing the Required pin on Port Register to Output a low logic 0 */
			}
			break;
		case PORTC_ID:
			if(a_level == LOGIC_HIGH)
			{
				SET_BIT(PORTC,a_pin_num);/* Setting the Required pin on Port Register to Output a High logic 1 */
			}
			else
			{
				CLR_BIT(PORTC,a_pin_num);/* clearing the Required pin on Port Register to Output a low logic 0 */
			}
			break;
		case PORTD_ID:
			if(a_level == LOGIC_HIGH)
			{
				SET_BIT(PORTD,a_pin_num);/* Setting the Required pin on Port Register to Output a High logic 1 */
			}
			else
			{
				CLR_BIT(PORTD,a_pin_num);/* clearing the Required pin on Port Register to Output a low logic 0 */
			}
			break;
		default:
			/*Wrong Port Error*/
		    break;
	  }
}
}

uint8 GPIO_readPin(const GPIO_Port a_port_num, const GPIO_Pin a_pin_num)
{

	if(a_port_num >= NUM_OF_PORTS || a_pin_num >= NUM_OF_PINS_PER_PORT)
	{
		/* Wrong Input*/
	}
	else
	{
		  switch(a_port_num)
	  {
		case PORTA_ID:
			return GET_BIT(PINA,a_pin_num);
		case PORTB_ID:
			return GET_BIT(PINB,a_pin_num);
		case PORTC_ID:
			return GET_BIT(PINC,a_pin_num);
		case PORTD_ID:
			return GET_BIT(PIND,a_pin_num);
		default:
			/*Wrong Port Error*/
		break;
	  }
	}
	return 0;
}

void GPIO_setupPortDirection(GPIO_Port a_port_num, uint8 a_direction)
{
	if(a_port_num >= NUM_OF_PORTS)
		{
			/* Wrong Input*/
		}
		else
		{
			  switch(a_port_num)
		  {
			case PORTA_ID:
				DDRA = a_direction;
					break;
			case PORTB_ID:
				DDRB = a_direction;
					break;
			case PORTC_ID:
				DDRC = a_direction;
					break;
			case PORTD_ID:
				DDRD = a_direction;
					break;
			default:
				/*Wrong Port Error*/
				break;
		  }
		  }
}

void GPIO_writePort(const GPIO_Port a_port_num,uint8 a_level)
{
	if(a_port_num >= NUM_OF_PORTS)
			{
				/* Wrong Input*/
			}
			else
			{
				  switch(a_port_num)
			  {
				case PORTA_ID:
					PORTA = a_level;
						break;
				case PORTB_ID:
					PORTB = a_level;
						break;
				case PORTC_ID:
					PORTC = a_level;
						break;
				case PORTD_ID:
					PORTD = a_level;
						break;
				default:
					/*Wrong Port Error*/
					break;
			  }


			  }
}

uint8 GPIO_readPort(GPIO_Port a_port_num)
{
	if(a_port_num >= NUM_OF_PORTS)
		{
			/* Wrong Input*/
		}
		else
		{
			  switch(a_port_num)
			  {
			case PORTA_ID:
				return PINA;
			case PORTB_ID:
				return PINB;
			case PORTC_ID:
				return PINC;
			case PORTD_ID:
				return PIND;
			default:
				/*Wrong Port Error*/
				break;
			  }
		}
		return 0;
}

