
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

namespace Long
{

/************************************************************************/

static Clock _glo_clock;

/************************************************************************/

#define CK1_1US		10
#define CK1_1MS		10000
#define CK8_1MS		1250
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
		
		TCCR1A = 0x00;
		TCCR1B = 0x00;
		TIMSK1 = 0x00;
		OCR1A = 0x00;
		TCNT1 = 0x00;
	}
}

//----------------------------------------------------------------------//

void Set(const Clock _clock, const CountValue _value)
{
	_glo_clock = _clock;
	
	OCR1A = _value;
}

//----------------------------------------------------------------------//

void Set_us(const uSecond _time_us)
{
	if (_time_us < 1000)
	{
		Set(CLOCK_1, _time_us * CK1_1US);
	}
	else
	{
		Set_ms(_time_us * 0.001);
	}
}

//----------------------------------------------------------------------//

void Set_ms(const mSecond _time_ms)
{
	if (_time_ms < 6)
	{
		Set(CLOCK_1, _time_ms * CK1_1MS);
	}
	else if (_time_ms < 53)
	{
		Set(CLOCK_8, _time_ms * CK8_1MS);
	}
	else if (_time_ms < 420)
	{
		Set(CLOCK_64, _time_ms * CK64_1MS);
	}
	else if (_time_ms < 1678)
	{
		Set(CLOCK_256, _time_ms * CK256_1MS);
	}
	else if (_time_ms < 6711)
	{
		Set(CLOCK_1024, _time_ms * CK1024_1MS);
	}
	else
	{
		Set(CLOCK_1024, 65535);
	}
}

//----------------------------------------------------------------------//

void Start()
{
	TCNT1 = 0x00;
	TCCR1B = _glo_clock;
}

//----------------------------------------------------------------------//

void Start(const Clock _clock, const CountValue _value)
{
	_glo_clock = _clock;
	
	TCNT1 = 0x00;
	OCR1A = _value;
	TCCR1B = _clock;
}

//----------------------------------------------------------------------//

YesNo Is_count_finshed()
{
	return (YesNo)((TIFR1 >> OCF1A) & 1);
}

//----------------------------------------------------------------------//

void Stop()
{
	TCCR1B = 0x00;
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

/************************************************************************/

#endif

/************************************************************************/
