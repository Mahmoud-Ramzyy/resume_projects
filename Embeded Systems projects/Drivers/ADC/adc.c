
#include "adc.h"

void ADC_init(void)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage
	 * through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization */
	ADMUX=0x00;
	/*7:enable ADC
	 * 1 &0 : prescalar=8
	 */
	ADCSRA= (1<<7)|(1<<1)|(1<<0);
	ADC=0;
}

uint16 ADC_readChannel(uint8 ch_num)
{
	ACD_io |= ch_num;
    /* clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set
     * the required channel */
	ADMUX &= 0xE0;
	ADMUX |= ch_num;
	SET_BIT(ADCSRA,6); /*start converting*/
	while (BIT_IS_CLEAR(ADCSRA,ADIF)); /*w8 till flag is set which mean conversion is complete */
	SET_BIT(ADCSRA,ADIF); /* clear ADIF by write '1' to it :) */
	return ADC;
}
