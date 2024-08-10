/**
 * @file 	app.c
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
//#include "math.h"
/* ===================================================================================================
                                              Global Variables
   ===================================================================================================*/

/*
 * Variable to represent the sign of a value, initialized to positive.
 * It is used for indicating negative values or direction in calculations.
 */
sint8 neg = 1;

/*
 * Variable to store the selected range of measurement.
 * It holds values representing different measurement ranges.
 */
uint8 Range = 0;

/*
 * Variable to store the lowest value corresponding to the selected measurement range.
 * It is used for Knowing lowest Measured Value in Used Range.
 */
float64 Range_lowest_val = 0;

/*
 * Variable to store the highest value corresponding to the selected measurement range.
 * It is used for Knowing highest Measured Value in Used Range.
 */
float64 Range_highest_val = 0;

/*
 * Variable to store the ratio used for scaling ADC readings to physical units based on the selected range.
 * It represents the conversion factor between ADC counts and physical units.
 */
float32 Range_Ratio = 1;

/*
 * Variable to store the raw ADC value obtained from the analog-to-digital converter.
 * It represents the sampled voltage value before any processing or scaling.
 */
float128 Adc_value = 0;

/*
 * Variable to store the calculated AC value based on the chosen range.
 * It represents the maximum value obtained during AC measurement.
 */
float128 Ac_value = 0;

/*
 * Variable to store the mode of measurement operation.
 * It holds values representing Is the mode Ac or Dc
 */
uint8 Ac_Mode = AC_OFF;  // Default mode is AC_OFF

/*
 * Variable to store the Correct Used Password.
 */
volatile static uint8 Correct_Password[MAX_NUM_OF_DIGITS] = { 2, 7, 9, 2, 0, 0, 3 };
static uint8 Dmm_State = DMM_CLOSED;

/* ===================================================================================================
                                              Function Definition
   ===================================================================================================*/

/**
 *
 * This function Initiallizes the System Modules
 *
 * @param[in]  none
 * @param[out]  none
 * @return none
 */
void APP_sysInit(void)
{
  /* Initialize the LCD display module */
  LCD_init();

  /* Initialize the keypad */
  KEYPAD_init();

  /* Initialize the Analog-to-Digital Converter */
  ADC_init(&ADC_Configuration);

  /* Set up the direction of PORTC as output Which is the pins Responsible for Selections */
  GPIO_setupPortDirection(PORTD_ID, PORT_OUTPUT);
  /* Set up the direction of PORTA as PIN 7 As Input To Be Use For Sign Detection  */
  GPIO_setupPinDirection(PORTA_ID, PIN7_ID, PIN_INPUT);
  /* Set up the direction of PORTB as PIN 4 As Output To Be Use For Buzzer */
  GPIO_setupPinDirection(PORTB_ID, PIN4_ID, PIN_OUTPUT);
}

/**
 *
 * This function Choose the Range Based on the Pressed Key of Keypad.
 *
 * @param[in]  none
 * @param[out]  none
 * @return none
 */
void APP_setRange(uint8 Pressedkey)
{
	/* Turn Buzzer On */
	GPIO_writePin(PORTB_ID, PIN4_ID, LOGIC_HIGH);
	_delay_ms(100);
	GPIO_writePin(PORTB_ID, PIN4_ID, LOGIC_LOW);
  /* Depending on the pressed range configure the Selections */
  switch (Pressedkey)
	{
	case KEY_V_20_200:
	  /* Display voltage range 20 - 200 V */
	  LCD_displayString("V 20 -> 200   ");
	  Range = VOLT_RANGE_20_200;
	  Range_lowest_val = 20;
	  Range_highest_val = 200;
	  break;

	case KEY_V_4_20:
	  /* Display voltage range 2 - 20 V */
	  LCD_displayString("V 4 -> 20     ");
	  Range = VOLT_RANGE_4_20;
	  Range_lowest_val = 4;
	  Range_highest_val = 20;
	  break;

	case KEY_V_800m_4:
	  /* Display voltage range 0.2 - 2 V */
	  LCD_displayString("V 0.8 -> 4    ");
	  Range = VOLT_RANGE_800MILLI_4;
	  Range_lowest_val = 0.8;
	  Range_highest_val = 4;
	  break;

	case KEY_V_1m_800m:
	  /* Display voltage range 1m - 0.2 V */
	  LCD_displayString("V 1m -> 0.8   ");
	  Range = VOLT_RANGE_200MILLI_800MILLI;
	  Range_lowest_val = 1;
	  Range_highest_val = 800;
	  break;

	case KEY_A_50m_1:
	case KEY_A_50m_1_BUT2:
	  /* Display current range 450m - 2 A */
	  LCD_displayString("A 50m -> 1    ");
	  Range = AMP_RANGE_50MILLI_1;
	  Range_lowest_val = 0.05;
	  Range_highest_val = 1;
	  break;

	case KEY_A_10m_50m:
	  /* Display current range 40m - 450m A */
	  LCD_displayString("A 10m -> 50m  ");
	  Range = AMP_RANGE_10MILLI_50MILLI;
	  Range_lowest_val = 0.010;
	  Range_highest_val = 0.05;
	  break;

	case KEY_A_1m_10m:
	  /* Display current range 1m - 40m A */
	  LCD_displayString("A 1m -> 10m   ");
	  Range = AMP_RANGE_1MILLI_10MILLI;
	  Range_lowest_val = 0.001;
	  Range_highest_val = 0.010;
	  break;

	case KEY_R_50K_1M:
	case KEY_R_50K_1M_BUT2:
	  /* Display resistance range 50K - 1M Ohm */
	  LCD_displayString("R 50K -> 1M   ");
	  Range = RES_RANGE_50K_1M;
	  Range_lowest_val = 50000;
	  Range_highest_val = 3000000;
	  break;

	case KEY_R_1K_50K:
	  /* Display resistance range 1K - 50K Ohm */
	  LCD_displayString("R 1K -> 50K    ");
	  Range = RES_RANGE_1K_50K;
	  Range_lowest_val = 1000;
	  Range_highest_val = 50000;
	  break;

	case KEY_R_400_1K:
	  /* Display resistance range 100 - 1K Ohm */
	  LCD_displayString("R 400 -> 1K    ");
	  Range = RES_RANGE_400_1K;
	  Range_lowest_val = 400;
	  Range_highest_val = 1000;
	  break;

	case KEY_AC_OFF:
	  /* Set AC mode to off */
	  Ac_Mode = AC_OFF;
	  break;

	case KEY_AC_ON:
	  /* Set AC mode to on */
	  Ac_Mode = AC_ON;
	  break;
	}


  /* Configure the correct range by changing switch selection pins */
  GPIO_writePort(PORTD_ID, Range);

  /* Delay for stability */
  _delay_ms(100);

  /* Display if it is AC mode or DC or a Resistance */
  if (Range == RES_RANGE_400_1K || Range == RES_RANGE_1K_50K || Range == RES_RANGE_50K_1M)
	{
	  LCD_displayString("         ");
	}
  else if (Ac_Mode == AC_ON)
	{
	  LCD_moveCursor(0, 14);
	  LCD_displayString("AC       ");
	}
  else
	{
	  LCD_moveCursor(0, 14);
	  LCD_displayString("DC       ");
	}

}

/**
 *
 * This function Calculate the value Based on chosen range.
 *
 * @param[in]  none
 * @param[out]  none
 * @return none
 */
void APP_getValue(void)
{
  /* Check If The Volt is Negative */
  neg = (GPIO_readPin(PORTA_ID, PIN7_ID) ? -1 : 1);
  /* Switch based on the selected range */
  switch (Range)
	{
	case VOLT_RANGE_20_200:
	  /* Check if in AC mode */
	  if (Ac_Mode)
		{
		  /* If AC mode, get AC value */
		  Range_Ratio = VOLT_RANGE4_RATIO;
		  APP_getValueAC();
		}
	  else
		{
		  Adc_value = Get_Real_Volt() * VOLT_RANGE4_RATIO * neg;
		}
	  /* Print the calculated voltage as float with 3 decimal digits */
	  LCD_floatToString(Adc_value, 3);
	  LCD_displayString(" V         ");
	  break;

	case VOLT_RANGE_4_20:
	  /* Check if in AC mode */
	  if (Ac_Mode)
		{
		  /* If AC mode, get AC value */
		  Range_Ratio = VOLT_RANGE3_RATIO;
		  APP_getValueAC();
		}
	  else
		{
		  Adc_value = Get_Real_Volt() * VOLT_RANGE3_RATIO * neg;
		}
	  /* Print the calculated voltage as float with 3 decimal digits */
	  LCD_floatToString(Adc_value, 3);
	  LCD_displayString(" V         ");
	  break;

	case VOLT_RANGE_800MILLI_4:


	  /* Check if in AC mode */
	  if (Ac_Mode)
		{
		  Range_Ratio = 1;
		  /* If AC mode, get AC value */
		  APP_getValueAC();
		}
	  else{

		  Adc_value = Get_Real_Volt() * -neg;

	  }
	  /* Check if voltage is greater than 1V, if so, display in volts, otherwise in mV */
	  if (Adc_value >= 1 || Adc_value <= -1)
		{
		  /* Print the calculated voltage as float with 3 decimal digits */
		  LCD_floatToString(Adc_value, 3);
		  LCD_displayString(" V         ");
		}
	  else
		{
		  /* Print the calculated In mV as float with 3 decimal digits */
		  LCD_floatToString(Adc_value * 1000, 3);
		  LCD_displayString(" mV         ");
		}
	  break;
	case VOLT_RANGE_200MILLI_800MILLI:

	  /* Print the Gain of Op Amp*/
	  LCD_moveCursor(0, 12);
	  LCD_intgerToString(5);

	  /* Check if in AC mode */
	  LCD_moveCursor(1, 0);
	  if (Ac_Mode)
		{
		  Range_Ratio = 200;
		  /* If AC mode, get AC value */
		  APP_getValueAC();
		}
	  else{
		  Adc_value = Get_Real_Volt() * -200 * neg;
	  	  }
	  /* Check if the calculated value is greater than or equal to 100mV or less than or equal to -100mV */
	  if (Adc_value >= 200 || Adc_value <= -200)
		{
		  /* Print the calculated millivolt as float with 3 decimal digits */
		  LCD_floatToString(Adc_value, 3);
		  LCD_displayString(" mV        ");
		}
	  else
		{
		  /* If the calculated value is within -100mV to 100mV, switch to VOLT_RANGE_1MILLI_200MILLI range */
		  Range = VOLT_RANGE_1MILLI_200MILLI;
		  GPIO_writePort(PORTD_ID, Range);
		  _delay_ms(200);

		}
	  break;
	case VOLT_RANGE_1MILLI_200MILLI:
	  /* Print the Gain of Op Amp*/
	  LCD_moveCursor(0, 12);
	  LCD_intgerToString(20);

	  /* Check if in AC mode */
	  LCD_moveCursor(1, 0);
	  if (Ac_Mode)
		{
		  Range_Ratio = 50;
		  /* If AC mode, get AC value */
		  APP_getValueAC();
		}
	  else{
		  Adc_value = Get_Real_Volt() * -50 * neg;
	  	  }
	  /* Check if the calculated value is less than 100mV or greater than -100mV */
	  if (Adc_value < 200 && Adc_value > -200)
		{
		  /* Print the calculated Value in mV as float with 3 decimal digits */
		  LCD_floatToString(Adc_value, 3);
		  LCD_displayString(" mV        ");
		}
	  else
		{
		  /* If the calculated value is within -100mV to 100mV, switch back to VOLT_RANGE_200MILLI_800MILLI range */
		  Range = VOLT_RANGE_200MILLI_800MILLI;
		  GPIO_writePort(PORTD_ID, Range);
		  _delay_ms(200);
		}
	  break;
	case AMP_RANGE_50MILLI_1:
	  /* Check if in AC mode */
	  if (Ac_Mode)
		{
		  Range_Ratio = 1;
		  /* If AC mode, get AC value */
		  APP_getValueAC();
		}
	  else{

		  Adc_value = Get_Real_Volt() * -neg;

	  }
	  /* Check if the calculated value is greater than or equal to 1A or less than or equal to -1A */
	  if (Adc_value >= 1 || Adc_value <= -1)
		{
		  /* Print the calculated current as float with 3 decimal digits */
		  LCD_floatToString(Adc_value, 3);
		  LCD_displayString(" A         ");
		}
	  else
		{
		  /* If the calculated value is within -1A to 1A, print it in mA */
		  LCD_floatToString(Adc_value * 1000, 3);
		  LCD_displayString(" mA         ");
		}
	  break;
	case AMP_RANGE_10MILLI_50MILLI:

	  /* Check if in AC mode */
	  if (Ac_Mode)
		{
		  Range_Ratio = 0.02;
		  /* If AC mode, get AC value */
		  APP_getValueAC();
		}
	  else{

		  Adc_value = Get_Real_Volt() * 0.02 * -neg;

	  }
	  /* Print the calculated current in mA */
	  LCD_floatToString(Adc_value * 1000, 3);
	  LCD_displayString(" mA         ");
	  break;
	case AMP_RANGE_1MILLI_10MILLI:
	  /* Check if in AC mode */
	  if (Ac_Mode)
		{
		  Range_Ratio = 0.005;
		  /* If AC mode, get AC value */
		  APP_getValueAC();
		}
	  else{

		  Adc_value = Get_Real_Volt() * 0.005 * -neg;

	  }
	  /* Print the calculated current in mA */
	  LCD_floatToString(Adc_value * 1000, 3);
	  LCD_displayString(" mA         ");
	  break;
	case RES_RANGE_50K_1M:
	  {
		/* Calculate the resistance from the read ADC value */
		Adc_value = Get_Real_Volt();
		/* Perform resistance calculation based on the range */
		Adc_value = (Adc_value * 940180) / (4.95 - Adc_value);
		Adc_value = 1.007 * Adc_value + 20430;
		/* Check if the calculated resistance is in KOhm */
		/* Print the calculated resistance in KOhm with 3 decimal digits */
		LCD_floatToString(Adc_value / 1000, 2);
		LCD_displayString(" KOhm          ");

		break;
	  }
	case RES_RANGE_1K_50K:
	  {
		/* Calculate the resistance from the read ADC value */
		Adc_value = Get_Real_Volt();
		/* Perform resistance calculation based on the range */
		Adc_value = (Adc_value * 18220) / (4.95 - Adc_value);
		Adc_value = 0.9985 * Adc_value + 560.5;
		/* Check if the calculated resistance is in KOhm */
		/* Print the calculated resistance in KOhm with 3 decimal digits */
		LCD_floatToString(Adc_value / 1000, 2);
		LCD_displayString(" KOhm          ");

		break;
	  }
	case RES_RANGE_400_1K:
	  {
		/* Calculate the resistance from the read ADC value */
		Adc_value = Get_Real_Volt();
		/* Perform resistance calculation based on the range */
		Adc_value = (float64) (Adc_value * 700) / (4.95 - Adc_value);
		Adc_value = (Adc_value > 400 ? (0.9359 * Adc_value + 46.27) : (0.964 * Adc_value + 17.8));
		/* Print the calculated resistance in Ohm with 3 decimal digits */
		LCD_floatToString(Adc_value, 2);
		LCD_displayString(" Ohm           ");
		break;
	  }
	}

  /* Move cursor to the end of the Second line on LCD to Display if Value is In Range or not */
  LCD_moveCursor(1, 15);

  /* Check if the displayed value is within the specified range */
  if ((Adc_value==0)||(Adc_value >= Range_lowest_val && Adc_value <= Range_highest_val) || (Adc_value <= -Range_lowest_val && Adc_value >= -Range_highest_val))
	{
	  /* Display a space if value is within range */
	  LCD_displayCharacter(' ');
	}
  else
	{
	  /* Display 'X' if value is out of range */
	  LCD_displayCharacter('X');
	}

}

/**
 * @brief Checks the entered password.
 *
 * @param[in]  none
 * @param[out] none
 * @return uint8
 */
uint8 APP_passwordCheck(void)
{
  uint8 Pass_digit;
  uint8 Correct_num = 0;
  uint8 Password[MAX_NUM_OF_DIGITS] = { 0 };
  /* Loop to get each digit of the password */
  for (Pass_digit = 0; Pass_digit < MAX_NUM_OF_DIGITS; Pass_digit++)
	{
	  /* Get the pressed key from the keypad */
	  Password[Pass_digit] = KEYPAD_getPressedKey();

	  /* Wait until a key is pressed */
	  while (Password[Pass_digit] == NO_INPUT_NUM)
		{
		  Password[Pass_digit] = KEYPAD_getPressedKey();
		}

	  /* Wait until the key is released */
	  while (Password[Pass_digit] == KEYPAD_getPressedKey())
		;

	  /* Display '*' on LCD to hide the entered digit */
	  LCD_displayCharacter('*');

	  /* Check if the entered digit matches the correct password digit */
	  if (Password[Pass_digit] == Correct_Password[Pass_digit])
		{
		  Correct_num++;/* Increment correct digit counter */
		}
	}

  /* Check if all digits are correct */
  if (Correct_num == MAX_NUM_OF_DIGITS)
	{
	  return PASS_CORRECT;/* Return PASS_CORRECT if all digits are correct */
	}
  else
	{
	  return PASS_INCORRECT;/* Return PASS_INCORRECT if any digit is incorrect */
	}
}

/**
 * @brief Opens the Digital Multimeter and Check Password.
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void APP_dmmOpen(void)
{
  uint8 Pass = 0, Try = 3;
  /* Set digital multimeter state to opened */
  Dmm_State = DMM_OPENED;
  LCD_displayStringRowColumn(0, 3, " Welcome ");
  _delay_ms(1000);

  /* Loop until the correct password is entered or the number of tries becomes zero */
  while (Pass != PASS_CORRECT)
	{
	  /* Check if there are remaining tries */
	  if (Try > 0)
		{
		  /* Clear the screen and prompt the user to enter the password */
		  LCD_clearScreen();
		  LCD_displayStringRowColumn(0, 0, "Enter the Pass :");
		  LCD_moveCursor(1, 0);

		  /* Check the entered password */
		  Pass = APP_passwordCheck();

		  /* Check if the password is correct */
		  if (Pass == PASS_CORRECT)
			{
			  /* Clear the screen and display welcome messages */
			  LCD_clearScreen();
			  LCD_displayStringRowColumn(0, 1, "Welcome to AVR");
			  LCD_displayStringRowColumn(1, 3, "MULTI METER");
			  _delay_ms(2000);
			  /* go to the Application */
			  return;
			}
		  /* Check if the password is incorrect */
		  else if (Pass == PASS_INCORRECT)
			{
			  /* Decrement the number of tries */
			  Try--;
			  /* Clear the screen and display a message indicating incorrect password and remaining tries */
			  LCD_clearScreen();
			  LCD_displayStringRowColumn(0, 1, "Incorrect Pass");
			  LCD_displayStringRowColumn(1, 1, "Remaining try ");
			  LCD_intgerToString(Try);
			  _delay_ms(500);
			}
		}
	  /* If there are no remaining tries */
	  else
		{
		  /* Reset the number of tries to 3 */
		  Try = 3;
		  /* Clear the screen and display a message indicating to wait for 5 seconds */
		  LCD_clearScreen();
		  LCD_displayStringRowColumn(0, 1, "Wait for 5 Sec");
		  /* Delay for 5 seconds as you Entered Password for 3 times Incorrect */
		  _delay_ms(5000);
		}
	}

}

/**
 * @brief Calculates the AC value based on the chosen range.
 *
 * This function calculates the AC value by sampling the ADC for a certain number
 * of iterations and selecting the maximum value obtained during the sampling.
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void APP_getValueAC(void)
{
    Ac_value = 0;
    /* Press the Row button associated with the DC measurement to Check on it if Mode Changed*/
    GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + 3, KEYPAD_BUTTON_PRESSED);
    for (uint8 i = 0; i < 200; i++)
    {
        /* Read the ADC value and scale it based on the chosen range */
        Adc_value = Get_Real_Volt() * Range_Ratio;
        /* Update the AC value with the maximum ADC value obtained */
        Ac_value = (Ac_value < Adc_value ? Adc_value : Ac_value);

        /* Check if the button associated with the DC measurement is Pressed */
        if (GPIO_readPin(KEYPAD_COL_PORT_ID, (KEYPAD_FIRST_COL_PIN_ID + 3)) == KEYPAD_BUTTON_PRESSED)
        {
            break;
        }
    }
    /* Release the Row button associated with the DC measurement */
    GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + 3, KEYPAD_BUTTON_RELEASED);
    /* Add a delay for debouncing */
    _delay_ms(5);
    /* Update the ADC value with the calculated AC value */
    Adc_value = Ac_value;
}

