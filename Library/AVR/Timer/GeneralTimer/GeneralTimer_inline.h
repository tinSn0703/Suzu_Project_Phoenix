/*
 * GeneralTimer_inline.h
 *
 * Created: 2017/03/05 13:58:30
 *  Author: Suzu
 */ 


#pragma once

extern Byte _glo_counter_high;

//----------------------------------------------------------------------//

inline Byte Read_counter_high ()	{	return _glo_counter_high;	}

//----------------------------------------------------------------------//

inline DataTime Timer_Read ()
{
	Time _temp;
	
	_temp._counter._low  = TCNT5;
	_temp._counter._high = Read_counter_high();
	
	return _temp._all;
}

//----------------------------------------------------------------------//

inline void Timer_Set (Time *_arg_timer, MeasureTime _arg_time_ms)
{
	_arg_timer->_counter._low	= TCNT5;
	_arg_timer->_counter._high	= Read_counter_high();
	
	_arg_timer->_all += _arg_time_ms * _CHANGE_COUNT_NUM_;
}

//----------------------------------------------------------------------//

inline BOOL Timer_Comp (const Time *_time)
{
	return ((_time->_all >= Timer_Read()) ? FALSE : TRUE);
}

//----------------------------------------------------------------------//

inline MeasureTime Timer_Change (const DataTime _arg_time)
{
	return _arg_time * _CHANGE_MS_;
}

//----------------------------------------------------------------------//
