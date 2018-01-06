
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Others/BOOL.h>
#include <AVR/Timer/GeneralTimer.h>

/************************************************************************/

namespace Timer
{

namespace General
{

/************************************************************************/

#if defined(_AVR_IOM640_H_)

#define TIMER_OVF_vect TIMER5_OVF_vect

#define TCCRA TCCR5A
#define TCCRB TCCR5B
#define TCCRC TCCR5C
#define TIMSK TIMSK5
#define TCNT TCNT5

#elif defined(_AVR_IOM164_H_)

#define TIMER_OVF_vect TIMER1_OVF_vect

#define TCCRA TCCR1A
#define TCCRB TCCR1B
#define TCCRC TCCR1C
#define TIMSK TIMSK1
#define TCNT TCNT1

#else

#error "It is an unsupported microcomputer."

#endif

/************************************************************************/

union Counter
{
//variable
private:
	
	struct BitCounter
	{
		DataBit16	_low	:16;
		DataBit8	_high	:8;
	}
	_counter;
	
	CountValue _all :24;
	
//function
public:
	
//----------------------------------------------------------------------//
	
	Counter()
	{
		_all = 0;
		
		TCCRA = 0x00;
		TCCRC = 0x00;
		TIMSK = (1 << TOIE0);
		TCNT  = 0x00;
		TCCRB = CLOCK_1024;
		
		sei();
	}
	
//----------------------------------------------------------------------//
	
	CountValue Current()
	{
		_counter._low = TCNT;
		
		return _all;
	}
	
//----------------------------------------------------------------------//
	
	void Count_up()
	{
		_counter._high ++;
	}
	
//----------------------------------------------------------------------//
	
};

/************************************************************************/

static Counter _glo;

/************************************************************************/

#define COUNTER_MAX_VALUE 16777215
#define CHANGE_COUNT_VALUE	9.765625
#define CHANGE_MS			0.1024

/************************************************************************/

//----------------------------------------------------------------------//

ISR(TIMER_OVF_vect)
{
	cli();
	
	TCCRB = 0x00;
	
	_glo.Count_up();
	
	TCCRB = CLOCK_1024;
		
	sei();
}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

CountValue Read()
{
	return _glo.Current();
}

//----------------------------------------------------------------------//

CountValue To_count_value(const mSecond _time_ms)
{
	 return _time_ms * CHANGE_COUNT_VALUE;
}

//----------------------------------------------------------------------//

CountValue Set_counter(const mSecond _measure_time_ms)
{
	return _glo.Current() + (_measure_time_ms * CHANGE_COUNT_VALUE);
}

//----------------------------------------------------------------------//

BOOL Is_current_bigger_than(const CountValue _time)
{
	return ((_time >= _glo.Current()) ? FALSE : TRUE);
}

//----------------------------------------------------------------------//

mSecond To_ms(const CountValue _time)
{
	return _time * CHANGE_MS;
}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

Count :: Count(const mSecond _count_time)

	: _mem_count_time(_count_time)
{
	_mem_counter = COUNTER_MAX_VALUE;
}

//----------------------------------------------------------------------//

YesNo Count :: Is_count_running()
{
	return (_mem_counter != COUNTER_MAX_VALUE ? YES : NO);
}

//----------------------------------------------------------------------//

void Count :: Start()
{
	_mem_counter = _glo.Current() + (_mem_count_time * CHANGE_COUNT_VALUE);
}

//----------------------------------------------------------------------//

YesNo Count :: Is_count_finish()
{
	if (_glo.Current() >= _mem_counter)
	{
		_mem_counter = COUNTER_MAX_VALUE;
		
		return YES;
	}
	
	return NO;
}

//----------------------------------------------------------------------//

void Count :: End()
{
	_mem_counter = COUNTER_MAX_VALUE;
}

//----------------------------------------------------------------------//

/************************************************************************/

}

}

/************************************************************************/
