/*
 * GeneralTimer.h
 *
 * Created: 2017/03/04 15:45:02
 *  Author: Suzu
 *
 *	Timer5‚ðŽg—p
 */ 

#pragma once

/************************************************************************/

#define _CHANGE_COUNT_NUM_ 9.765625
#define _CHANGE_MS_ 0.1024

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

typedef ullint DataTime;
typedef DataBit16 MeasureTime;

/************************************************************************/

typedef union
{
	struct PartsTime
	{
		DataBit16	_low :16;
		Byte	_high :8;
	}
	_counter;
	
	DataTime _all :24;
}
Time;

/************************************************************************/

#ifdef __cplusplus

	extern "C"	{

#endif /*__cplusplus*/

/************************************************************************/

Byte Read_counter_high ();

void Timer_Init ();

inline DataTime Timer_Read ();

inline void Timer_Set (Time *_timer, MeasureTime _time_ms);

inline BOOL Timer_Comp (const Time *_time);

inline MeasureTime Timer_Change (DataTime _time);

/************************************************************************/

#ifdef __cplusplus

	};

#endif /*__cplusplus*/

/************************************************************************/

#include "GeneralTimer_inline.h"

/************************************************************************/

#undef _CHANGE_COUNT_NUM_
#undef _CHANGE_MS_
