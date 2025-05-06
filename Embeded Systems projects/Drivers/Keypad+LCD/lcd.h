
#ifndef LCD_H_
#define LCD_H_
/*****************************includes******************************/
#include"common_macros.h"
#include"micro_config.h"
#include"std_types.h"

/********************** definitions and configurations *****************/
#define LCD_mode 4
/*  Hw connections*/
#define RS PB1
#define RW PB2
#define E  PB3
#define LCD_ctrl_IO DDRB
#define LCD_ctrl_PORT PORTB
#define LCD_data_IO DDRD
#define LCD_data_PORT PORTD
/* commands*/
#define LCD_clear_Screen 0x01
#define LCD_home 0x02  /*restore display from shift */
#define Cursor_Off 0x0c  /* cursor off & display on   */
#define Cursor_On  0x0E  /* cursor on & display on   */
#define Cursor_begin 0x80  /* force cursor to beginning of 1s line */
#define LCD_2lines_8bit_mode 0x38
#define LCD_2lines_4bit_mode 0x28

/********************* Functions prototypes ****************/
void LCD_init (void);
void LCD_commands (uint8 cmd);
void LCD_display_char (uint8 data);
void LCD_display_string (const char* str);
void LCD_shift_cursor_to (uint8 row,uint8 col);
void LCD_display_at_cursor (const char* str,uint8 row,uint8 col);
void LCD_clear (void);
void LCD_int_to_string (int num); /* used to translat nums into ascii*/


#endif /* LCD_H_ */
