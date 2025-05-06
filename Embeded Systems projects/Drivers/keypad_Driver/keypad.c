
#include"keypad.h"

#if (N_col==3)
/*we have a 4x3 keypad*/
static uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number)
{
	switch (button_number)
	{
	case 10 : return '*'; /*according to the keypad used in proteus*/
	break;
	case 11 : return '0';
	break;
	case 12 : return '#';
	break;
	default: return button_number;
	}
}

#elif (N_col==4)

/*we have a 4x3 keypad*/
static uint8 KeyPad_4x4_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
		{
			case 1: return 7; /*according to the keypad used in proteus*/
					break;
			case 2: return 8;
					break;
			case 3: return 9;
					break;
			case 4: return '%'; // ASCII Code of %
					break;
			case 5: return 4;
					break;
			case 6: return 5;
					break;
			case 7: return 6;
					break;
			case 8: return '*'; /* ASCII Code of '*' */
					break;
			case 9: return 1;
					break;
			case 10: return 2;
					break;
			case 11: return 3;
					break;
			case 12: return '-'; /* ASCII Code of '-' */
					break;
			case 13: return 13;  /* ASCII of Enter */
					break;
			case 14: return 0;
					break;
			case 15: return '='; /* ASCII Code of '=' */
					break;
			case 16: return '+'; /* ASCII Code of '+' */
					break;
			default: return button_number;
		}
}
#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
uint8 KeyPad_getPressedKey(void)
{
	while (1)
	{
		for (int col=0;col<N_col;col++)
		{
			/*just the 4th pin (col 0) is op and other pins are ips in the beginning*/
			KEYPAD_PORT_DIR=(0x10<<col);

			/*Enable the internal pull ups for rows(0->3 pins) and make other col high Z
		  except the current op pin make it low
			 */
			KEYPAD_OUT=~(0x10<<col);
			for (int row=0;row<N_row;row++)
			{
				if (BIT_IS_CLEAR(KEYPAD_IN,row))
				{
					#if (N_col == 3)
						return KeyPad_4x3_adjustKeyNumber((row*N_col)+col+1);
					#elif (N_col == 4)
						return KeyPad_4x4_adjustKeyNumber((row*N_col)+col+1);
					#endif
				}
			}
		}
	}

}
