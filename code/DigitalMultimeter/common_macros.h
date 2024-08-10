 /**
   * @file Common_Macros.h
   * @brief Header file for the Common_Macros.
   *
   * @author [Mohamed Mabrouk]
   * @date [9 DEC 2023]
   *
   * @SWversion 1.0.0
   *
   * @remarks
   *    -Platform         : AVR
   *    -Peripherial      : Atmega32
   */
   /*==================================================================================================================================*/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define SET_BIT(REG,BIT) 		(REG|=(1<<BIT))

#define CLR_BIT(REG,BIT) 		(REG&=(~(1<<BIT)))

#define TOGGLE_BIT(REG,BIT)	    (REG^=1<<BIT)

#define GET_BIT(REG,BIT) 		((REG>>BIT)&1)

#define BIT_IS_SET(REG,BIT) 	(REG & (1<<BIT))

#define BIT_IS_CLEAR(REG,BIT) 	(!(REG & (1<<BIT)))

#define ROR(REG,NUM) 			(REG = (REG>>NUM)|(REG<<(8-NUM)))

#define ROL(REG,NUM) 			(REG = (REG<<NUM)|(REG>>(8-NUM)))

#define ENABLE_INTERRUPTS()		asm("SEI")
#define DISABLE_INTERRUPTS()	asm("CLI")


#endif /* COMMON_MACROS_H_ */
