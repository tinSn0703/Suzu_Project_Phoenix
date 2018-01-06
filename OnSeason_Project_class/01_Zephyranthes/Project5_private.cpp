
#include <MainCircit/MainCircit.h>

#include "Project5.h"

/************************************************************************/

namespace Zephyranthes
{

namespace Warhead
{

/************************************************************************/

//----------------------------------------------------------------------//

void Main :: Count_wheel_pwm(const YesNo _is_up, const YesNo _is_down)
{
	if (_is_up		& _mem_is_enabled_pwm_up)	_wheel ++;
	if (_is_down	& _mem_is_enabled_pwm_down)	_wheel --;
	
	_mem_is_enabled_pwm_up	 = ~_is_up;
	_mem_is_enabled_pwm_down = ~_is_down;
}

//----------------------------------------------------------------------//

void Main :: Transformation(YesNo _is_stand, YesNo _is_lie)
{
	if (_is_stand)
	{
		_motor_stand = SIGNAL_REVERSE;
		_motor_stand = PWM_STAND_MOVE;

		return (void)0;
	}
	
	if (_is_lie)
	{
		_motor_stand = SIGNAL_FORWARD;
		_motor_stand = PWM_STAND_MOVE;

		return (void)0;
	}

	_motor_stand = SIGNAL_BREAK;
}

//----------------------------------------------------------------------//

void Main :: Stretch_rod(uByte _number, mSecond _count_time)
{
	_rod[_number].Want_to_open(YES);

	_mem_timer[_number] = Timer::General::Set_counter(_count_time);
}

//----------------------------------------------------------------------//

void Main :: Stop_rod(uByte _number)
{
	if	(
			Timer::General::Is_current_bigger_than(_mem_timer[_number]) && 
			_mem_is_enabled_move_rod
		)
	{
		_rod[_number].Want_to_open(NO);
	}
}

//----------------------------------------------------------------------//

void Main :: Set_rod_permission()
{
	_mem_is_enabled_move_rod = 
	(
		_rod[0].Is_open() | 
		_rod[1].Is_open() | 
		_rod[2].Is_open() | 
		_rod[3].Is_open() 
	);
}

//----------------------------------------------------------------------//

void Main :: Attack(YesNo _is_rod_stretch)
{
	if (_is_rod_stretch & ~_mem_is_enabled_move_rod)
	{
		Stretch_rod(0, OPEN_TIME_VALVE_0);
		Stretch_rod(1, OPEN_TIME_VALVE_1);
		Stretch_rod(2, OPEN_TIME_VALVE_2);
		Stretch_rod(3, OPEN_TIME_VALVE_3);

		_mem_is_enabled_move_rod = YES;
	}

	Stop_rod(0);
	Stop_rod(1);
	Stop_rod(2);
	Stop_rod(3);

	Set_rod_permission();
}

//----------------------------------------------------------------------//

void Main :: Display()
{
	_wheel.Display_signal(0x40);
	_wheel.Display_pwm(0x48);
}

//----------------------------------------------------------------------//

/************************************************************************/

}

}

/************************************************************************/