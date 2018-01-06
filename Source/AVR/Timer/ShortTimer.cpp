
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Others/BOOL.h>
#include <AVR/Timer/GeneralTimer.h>
#include <AVR/Timer/NormalTimer.h>

/************************************************************************/

#ifdef _AVR_IOM640_H_

/************************************************************************/

namespace Timer
{

namespace Short
{

/************************************************************************/

static Clock _glo_clock;

/************************************************************************/

#define CK1_1US		10
#define CK8_1US		1.25
#define CK64_1US	0.15625

#define CK64_1MS	156
#define CK256_1MS	39.0625
#define CK1024_1MS	9.765625

/************************************************************************/

//----------------------------------------------------------------------//

void Initialize()
{
	static BOOL _can_i_run = TRUE;
	
	if (_can_i_run)
	{
		_glo_clock = CLOCK_1;
		
		TCCR0A = 0x00;
		TCCR0B = 0x00;
		TIMSK0 = 0x00;
		OCR0A = 0x00;
		TCNT0 = 0x00;
	}
}

//----------------------------------------------------------------------//

void Set(const Clock _clock, const CountValue _value)
{
	_glo_clock = _clock;
	
	OCR0A = _value;
}

//----------------------------------------------------------------------//

void Set_us(const uSecond _time_us)
{
	if (_time_us < 26)
	{
		Set(CLOCK_1, _time_us * CK1_1US);
	}
	else if (_time_us < 204)
	{
		Set(CLOCK_8, _time_us * CK8_1US);
	}
	else if (_time_us < 1000)
	{
		Set(CLOCK_64, _time_us * CK64_1US);
	}
	else
	{
		Set_ms(_time_us * 0.001);
	}
}

//----------------------------------------------------------------------//

void Set_ms(const mSecond _time_ms)
{
	if (_time_ms < 2)
	{
		Set(CLOCK_64, _time_ms * CK64_1MS);
	}
	else if (_time_ms < 7)
	{
		Set(CLOCK_256, _time_ms * CK256_1MS);
	}
	else if (_time_ms < 27)
	{
		Set(CLOCK_1024, _time_ms * CK1024_1MS);
	}
	else
	{
		Set(CLOCK_1024, 255);
	}
}

//----------------------------------------------------------------------//

void Start()
{
	TCNT0 = 0x00;
	TCCR0B = _glo_clock;
}

//----------------------------------------------------------------------//

void Start(const Clock _clock, const CountValue _value)
{
	_glo_clock = _clock;
	
	TCNT0 = 0x00;
	OCR0A = _value;
	TCCR0B = _clock;
}

//----------------------------------------------------------------------//

YesNo Is_count_finshed()
{
	return (YesNo)((TIFR0 >> OCF0A) & 1);
}

//----------------------------------------------------------------------//

void Stop()
{
	TCCR0B = 0x00;
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

/************************************************************************/

#endif

/************************************************************************/
