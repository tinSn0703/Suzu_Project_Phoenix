/*
 *	Timer5‚ðŽg—p
 */ 

#pragma once

/************************************************************************/

typedef enum
{
	CLOCK_1		= 0x1,
	CLOCK_8		= 0x2,
	CLOCK_64	= 0x3,
	CLOCK_256	= 0x4,
	CLOCK_1024	= 0x5
}
Clock;

typedef ullint CountValue;
typedef DataBit16 mSecond;

/************************************************************************/

namespace GeneralTimer
{

/************************************************************************/

void Initialize();

CountValue Read();

CountValue Set_counter(mSecond _measure_time_ms);

YesNo Is_current_bigger_than(CountValue _time);

CountValue Change_count_value(mSecond _measure_time_ms);

mSecond Change_ms(CountValue _time);

/************************************************************************/

}

/************************************************************************/
