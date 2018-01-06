/*
 * MainCircit.cpp
 *
 * Created: 2017/12/22 13:10:41
 *  Author: conde_000
 */ 

#include <MainCircit/MainCircit.h>

TimerCounter::TimerCounter()
{
	_timer = TIMER_INITAL_VALUE;
}

YesNo TimerCounter::Is_finish_wait(const YesNo _is_start, const mSecond _wait_time)
{
	if (_is_start)
	{
		if (_timer == TIMER_INITAL_VALUE)
		{
			_timer = Timer::General::Set_counter(_wait_time);
		}
		
		if (Timer::General::Is_current_bigger_than(_timer))
		{
			return YES;
		}
	}
	else
	{
		if (Timer::General::Is_current_bigger_than(_timer))
		{
			_timer = TIMER_INITAL_VALUE;
		}
	}
	
	return NO;
}

