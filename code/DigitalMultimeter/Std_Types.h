 /**
   * @file Std_Types.h
   * @brief Header file for the Std_Types.
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

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* ===================================================================================================
										Macro Definition
 ===================================================================================================*/

#define NULL_PTR ((void *)0)

/* Boolean Values */
#ifndef FALSE
#define FALSE 		(0u)
#endif
#ifndef TRUE
#define TRUE 		(1u)
#endif

#define LOGIC_LOW         (0u)
#define LOGIC_HIGH        (1u)

/* ===================================================================================================
								    	Standard Data Types
 ===================================================================================================*/
/* Boolean Data Type */
typedef unsigned char boolean;

typedef unsigned char         uint8;          /*           0 .. 255              */
typedef signed char           sint8;          /*        -128 .. +127             */
typedef unsigned short        uint16;         /*           0 .. 65535            */
typedef signed short          sint16;         /*      -32768 .. +32767           */
typedef unsigned long         uint32;         /*           0 .. 4294967295       */
typedef signed long           sint32;         /* -2147483648 .. +2147483647      */
typedef unsigned long long    uint64;         /*       0 .. 18446744073709551615  */
typedef signed long long      sint64;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float 				  float32;
typedef double		   	      float64;
typedef long double			  float128;

#endif /* STD_TYPES_H_ */
