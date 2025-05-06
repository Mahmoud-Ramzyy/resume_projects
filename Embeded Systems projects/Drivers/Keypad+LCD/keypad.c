
//#include "lcd.h"
#include "keypad.h"

//void Keypad_init (void)
//{
//	Keypad_IO=0xf0; /* upper 4 bits op (col) and lower 4 bits ip (rows) */
//	Keypad_OP=0x0f; /* enable the internal pull ups */
//}
#if (Keypad_col==3)
static uint8 Press_Num_3col (uint8 num)
{
	switch (num)
	{
	case 10 : return '*'; /*according to the keypad used in proteus*/
	break;
	case 11 : return '0';
	break;
	case 12 : return '#';
	break;
	default: return num;
	}
}
#elif (Keypad_col==4)
static uint8 Press_Num_4col (uint8 num)
{
	switch (num)
	{
	case 1: return 7; /*according to the keypad used in proteus*/
	break;
	case 2: return 8;
	break;
	case 3: return 9;
	break;
	case 4: return '%'; /* ASCII Code of % */
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
	default: return num;
	}
}
#endif

uint8 Keypad_get_Num (void)
{
	while (1)
	{
		for (uint8 col=0;col<Keypad_col;col++)
		{
  /*just the 4th pin (col 0) is op and other pins are ips in the beginning*/
			Keypad_IO = (0x10<<col);
  /*Enable the internal pull ups for rows(0->3 pins) and make other col high Z
		  except the current op pin make it low */
			Keypad_OP=  ~(0x10<<col);
			for (uint8 row=0;row<Keypad_row;row++)
			{
				if (BIT_IS_CLEAR(Keypad_IP,row))
				{
					#if (Keypad_col==3)
						return Press_Num_3col ((row*Keypad_col)+col+1);
					#elif (Keypad_col==4)
						return Press_Num_4col ((row*Keypad_col)+col+1);
					#endif
				}
			}
		}
	}
}


