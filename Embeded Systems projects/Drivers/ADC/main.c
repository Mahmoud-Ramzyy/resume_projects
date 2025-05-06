
#include "lcd.h"
#include "adc.h"

int main()
{
	ADC_init();
	LCD_init();
	uint16 value=0;
	LCD_displayString("ADC Value=");
	while (1)
	{

		value=ADC_readChannel(0);
		LCD_intgerToString (value);
	}

}
