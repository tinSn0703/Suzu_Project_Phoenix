

#include <avr/io.h>
#include <avr/interrupt.h>
#include <Others/BOOL.h>
#include <AVR/Timer/GeneralTimer/GeneralTimer.h>

/************************************************************************/

Byte _glo_counter_high = 0;

/************************************************************************/

ISR(TIMER5_OVF_vect)
{
	cli();
	
	_glo_counter_high ++;
	
//	TCCR5B = CLOCK_1;
	TCCR5B = CLOCK_1024;
		
	sei();
}

/************************************************************************/

//----------------------------------------------------------------------//

void Timer_Init ()
{
	static BOOL _can_i_run = TRUE;
	
	if (_can_i_run)
	{
		TCCR5A = 0x00;
		TCCR5B = ((1 << CS52) | (1 << CS50)); //1024[ck]
		TCCR5C = 0x00;
		TIMSK5 = (1 << TOIE5);
		
		_glo_counter_high = 0;
		
		_can_i_run = FALSE;
		
		sei();
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
