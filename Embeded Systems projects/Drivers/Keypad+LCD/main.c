
#include "lcd.h"
#include "keypad.h"

int main()
{
	uint8 key;
	LCD_init(); /* initialize LCD */
	LCD_display_string("Welcome To LCD");
	LCD_display_at_cursor("4 Bits Data Mode",1,0);
	LCD_display_at_cursor("line 3",2,0);
	LCD_shift_cursor_to(3,0);


    while(1)
    {
    	key=Keypad_get_Num ();
		if((key <= 9) && (key >= 0))
		{
			LCD_int_to_string(key); /* display the pressed keypad switch */
		}
		else if (key==13)  /* Õ … ‘ﬁ«Ê… „‰Ì */
		{
			LCD_clear();
		}
		else
		{
			LCD_display_char(key); /* display the pressed keypad switch */
		}
		_delay_ms(500);
    }
}
