#include "lcd.h"

void LCD_init (void)
{
	LCD_ctrl_IO=0x0E; /*RW,RS,E are ops */
#if (LCD_mode==4)
	LCD_commands(LCD_home); /*remember to try comment this*/
	LCD_commands(LCD_2lines_4bit_mode);
	LCD_data_IO=0x0f; /*data bus --> first four pins*/
#else
	LCD_commands(LCD_2lines_8bit_mode);
	LCD_data_IO=0xff; /*data bus*/
#endif
	LCD_commands(Cursor_Off);
	LCD_commands(LCD_clear_Screen);
}

void LCD_commands (uint8 cmd)
{
	CLEAR_BIT(LCD_ctrl_PORT,RS); /*command register is selected*/
	CLEAR_BIT(LCD_ctrl_PORT,RW); /*write mode*/
	_delay_ms(1); /*ts=50ns delay(address setup time) */
	SET_BIT(LCD_ctrl_PORT,E); /*Enable data*/
	_delay_ms(1); /*tpw-tdsw=190ns delay(E high level width- data setup time) */
#if (LCD_mode==4)
	LCD_data_PORT= (LCD_data_PORT & 0xf0) | (cmd>>4); /* 4 upper bits*/
	_delay_ms(1); /*tdsw =100ns*/
	/* second insertion preparation */
	CLEAR_BIT(LCD_ctrl_PORT,E); /*disable data*/
	_delay_ms(1); /*tah delay (data hold time)*/
	SET_BIT(LCD_ctrl_PORT,E); /*Enable data again to insert the other 4 lower bits*/
	_delay_ms(1); /*tpw-tdsw=190ns delay(E high level width- data setup time) */
	LCD_data_PORT= (LCD_data_PORT & 0xf0) | cmd; /*lower 4 bits*/
#else
	LCD_data_PORT= cmd;  /* cas of8 bit data bus*/
#endif
	_delay_ms(1); /*tdsw =100ns*/
	CLEAR_BIT(LCD_ctrl_PORT,E); /*disable data*/
	_delay_ms(1); /*tah delay (data hold time)*/
}

void LCD_display_char (uint8 data)
{
	SET_BIT(LCD_ctrl_PORT,RS); /*data register is selected*/
	CLEAR_BIT(LCD_ctrl_PORT,RW); /*write mode*/
	_delay_ms(1); /*ts=50ns delay(address setup time) */
	SET_BIT(LCD_ctrl_PORT,E); /*Enable data*/
	_delay_ms(1); /*tpw-tdsw=190ns delay(E high level width- data setup time) */

#if (LCD_mode==4)
	LCD_data_PORT= (LCD_data_PORT & 0xf0) | (data>>4); /* 4 upper bits*/
	_delay_ms(1);                          /*tdsw =100ns*/
	           /* second insertion preparation */
	CLEAR_BIT(LCD_ctrl_PORT,E);         /*disable data*/
	_delay_ms(1);                      /*tah delay (data hold time)*/
	SET_BIT(LCD_ctrl_PORT,E); /*Enable data again to insert the other 4 lower bits*/
	_delay_ms(1);       /*tpw-tdsw=190ns delay(E high level width- data setup time) */
	LCD_data_PORT= (LCD_data_PORT & 0xf0) | data;       /*lower 4 bits*/
#else
	LCD_data_PORT= data;  /* cas of8 bit data bus*/
#endif
	_delay_ms(1);                /*tdsw =100ns*/
	CLEAR_BIT(LCD_ctrl_PORT,E); /*disable data*/
	_delay_ms(1);              /*tah delay (data hold time)*/
}

void LCD_display_string (const char* str)
{
	while ((*str) !='\0')
	{
		LCD_display_char ( *str );
		str++;
	}
}

void LCD_shift_cursor_to (uint8 row,uint8 col)
{
	uint8 address;
	switch (row)
	{
	case 0 :
		address=col;             /* first line*/
	break;
	case 1 :
		address=col+0x40;        /* 2nd line */
	break;
	case 2 :
		address=col+0x10;        /* 3rd line  */
	break;
	case 3 :
		address=col+0x50;        /* 4th line  */
	break;
	}
	LCD_commands (address | Cursor_begin );

}

void LCD_display_at_cursor (const char* str,uint8 row,uint8 col)
{
	LCD_shift_cursor_to (row,col);
	LCD_display_string (str);
}

void LCD_clear (void)
{
	LCD_commands (LCD_clear_Screen);
}

void LCD_int_to_string (int num)
{
	   char buff[16]; /* String to hold the ascii result */
	   itoa(num,buff,10); /* 10 for decimal */
	   LCD_display_string (buff);
}
