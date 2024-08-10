/**
 * @file 	adc.c
 * @brief ADC Source file.
 *
 * This file contains The Implementation of Functions of the ADC module
  *
  * @author [Mohamed Mabrouk]
  * @date [16 FEB 2024]
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
#include"adc.h"
#include"lcd.h"
#include"common_macros.h"
/* ===================================================================================================
											  Global Variables
   ===================================================================================================*/
#if (ADC_CALLING_TYPE == ADC_INTERRUPT)
uint16 g_AdcValue = 0;
#endif
/* ===================================================================================================
										Function Definition
   ===================================================================================================*/

/**
 *
 * This Function responsible for initialize the ADC driver.
 *
 * @param[in]  Config_Ptr Type ADC_ConfigType
 * @param[out] none
 * @return none
 */
void ADC_init(const ADC_ConfigType *Config_Ptr)
{
switch(Config_Ptr->RefVoltSource)
{
/* Choosing Adc Reference Volt Source */
case ADC_REF_AREF:
CLR_BIT(ADMUX,REFS0);
CLR_BIT(ADMUX,REFS1);
break;
case ADC_REF_AVCC:
SET_BIT(ADMUX,REFS0);
CLR_BIT(ADMUX,REFS1);
break;
case ADC_REF_INTERNAL:
SET_BIT(ADMUX,REFS0);
SET_BIT(ADMUX,REFS1);
break;
default:
/* Error */
break;
}
/* Enabling the Adc Module */
SET_BIT(ADCSRA,ADEN);
/* Choosing the Suitable Prescaler */
ADCSRA = (ADCSRA & 0xF8) | ((Config_Ptr->Prescaler) & 0x07) ;
#if (ADC_CALLING_TYPE == ADC_INTERRUPT)
/* Enabling the Adc Module Interrupt */
SET_BIT(ADCSRA,ADIE);
#endif
}

/**
 *
 * This Function responsible for Deinitialize the ADC driver.
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void ADC_deInit(void)
{
	ADMUX = 0;
	ADCSRA = 0;
}


#if (ADC_CALLING_TYPE == ADC_POLLING)

/**
 *
 * This function Reads the Analog Value Of a Specific Channel .
 *
 * @param[in]  Channel     Type ADC_Channel     Range 0:28
 * @param[out] none
 * @return	   uint16
 */
uint16 ADC_readChannel(ADC_Channel channel)
{
/* Clear the Previous Choosen Channel And Choose the One you want */
ADMUX = (ADMUX & 0xF0) | (channel & 0x1F);

/* Start ADC Conversion */
SET_BIT(ADCSRA,ADSC);

/* Wait until ADC Finish Conversion*/
while(!GET_BIT(ADCSRA,ADIF));

/* Clear the ADC Flag*/
SET_BIT(ADCSRA,ADIF);

/* Return the Value*/
return ADC;

}

#elif (ADC_CALLING_TYPE == ADC_INTERRUPT)

/**
 *
 * This function Reads the Analog Value Of a Specific Channel .
 *
 * @param[in]  Channel     Type ADC_Channel     Range 0:28
 * @param[out] none
 * @return none
 */
void ADC_readChannel(const ADC_Channel channel)
{
/* Clear the Previous Choosen Channel And Choose the One you want */
ADMUX = (ADMUX & 0xF0) | (channel & 0x1F);

/* Start ADC Conversion */
SET_BIT(ADCSRA,ADSC);
}


/* ADC ISR */
void __vector_16(void)
{
	g_AdcValue = ADC;
}


#endif

