#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char ticks=0, count=0,reset_flag=0;

//Ext interrupt 0:
ISR(INT0_vect)
{
	reset_flag=1;
}

//interrupt of timer1:
ISR (TIMER1_COMPA_vect)
{
	if (ticks==5) //at 5th interrupt we have 1 sec
	{
		ticks=0;
		count++;
	}
	else
		ticks++; //number of interrupts
}

//initialization of intterupt 0:
void interrupt0_init(void)
{
	//SREG&=~(1<<7);
	GICR |=(1<<6); //enable int0
	MCUCR |=(1<<1);//Trigger INT0 with the falling edge
	//SREG |=(1<<7);
}
//initialization of timer 1:
void timer1_init (void)
{
	TCNT1=0;
	OCR1A=25000;   //top value: 1sec=10^6us--->40 interrupts are needed to get 1 sec
	TCCR1A=(1<<3)|(1<<2);// CTC MODE:normal
	TCCR1B=(1<<3)|(1<<1);//Prescaler=8--> now just 5 interrupts are needed
	TIMSK |=(1<<4); //enable the interrupt of Timer 1
}

int main()
{
	DDRC=0x0f;      //7-segment op
	PORTC=0x00;     //init with zero
	DDRA=0x3f;      //we use lcd consists of 6*(7-segments)
	PORTA=0x3f;     //turn on all the 7 segments

	DDRD&=~(1<<2);  //interrupt for reset
	PORTD |=(1<<2); //Enable the internal pull up

	SREG |=(1<<7);  //enable global interrupt

	//var will use to update the time
	unsigned char sec=0,min1=0,min2=0,hr1=0,hr2=0;

	timer1_init();
	interrupt0_init();

	for (;;)
	{
		if (reset_flag==0)
		{
			if (count==10) //if we have 10 sec
			{
				count =0; //reset the first col with 0
				sec++; //increase the sec col
			}
			if (sec==6)//if we have 60 sec=1min
			{
				sec=0;
				min1++;
			}
			if (min1==10) //if we have 10 min
			{
				min1=0;
				min2++;
			}
			if (min2==6) //if we have 60 min=1hr
			{
				min2=0;
				hr1++;
			}
			if (hr1==10) //if we have 10 hrs
			{
				hr1=0;
				hr2++;
			}
		}
		else
		{
			count=0;
			sec=0;
			min1=0;
			min2=0;
			hr1=0;
			hr2=0; //it works:v
			reset_flag=0;

		}
		//update first column of seconds
		PORTA=(PORTA & 0xc0) | 0x01; //turn on the first 7-segment only in LCD
		PORTC=(PORTC & 0xf0) | count;
		// make small delay to see the changes in the 7-segment
		// 2Miliseconds delay will not effect the seconds count
		_delay_ms(2);

		//update 2nd column of seconds
		PORTA=(PORTA & 0xc0) | 0x02;
		PORTC=(PORTC & 0xf0) | sec;
		_delay_ms(2);

		//update first column of minutes
		PORTA=(PORTA & 0xc0) | 0x04;
		PORTC=(PORTC & 0xf0) | min1;
		_delay_ms(2);

		//update 2nd column of minutes
		PORTA=(PORTA & 0xc0) | 0x08;
		PORTC=(PORTC & 0xf0) | min2;
		_delay_ms(2);

		//update first column of hours
		PORTA=(PORTA & 0xc0) | 0x10;
		PORTC=(PORTC & 0xf0) | hr1;
		_delay_ms(2);

		//update 2nd column of seconds
		PORTA=(PORTA & 0xc0) | 0x20;
		PORTC=(PORTC & 0xf0) | hr2;
		_delay_ms(2);

	}


}
