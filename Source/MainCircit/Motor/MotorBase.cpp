
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <MainCircit/Signal.h>
#include <MainCircit/Motor/MotorBase/MotorBase.h>

#include <math.h>

/************************************************************************/

namespace ClassMotor
{
/************************************************************************/
/*	MotorOperate														*/
/************************************************************************/

//----------------------------------------------------------------------//

MotorOperate::MotorOperate()
{
	Initialize();
}

//----------------------------------------------------------------------//

MotorOperate::MotorOperate(const MotorNum _motor_num, const YesNo _is_signal_reverse /* = NO */)
{
	Initialize();
	
	Reset(_motor_num);
	
	Want_to_reverse_signal(_is_signal_reverse);
}

//----------------------------------------------------------------------//

void MotorOperate::Drive(const Power _power)
{
	if		(_power > 0)	Set(SIGNAL_FORWARD, _power);
	else if	(_power < 0)	Set(SIGNAL_REVERSE, _power * -1);
	else					Set(SIGNAL_BREAK);
}

//----------------------------------------------------------------------//

void MotorOperate::Drive_P
(
	const int		_target_value,
	const int		_current_value,
	const double	_p_constant
)
{
	if (_target_value > _current_value)
	{
		Set(SIGNAL_FORWARD);
		
		Set(((_target_value - _current_value) * _p_constant) / _target_value);
	}
	else if (_target_value < _current_value)
	{
		Set(SIGNAL_REVERSE);
		
		Set(((_current_value - _target_value) * _p_constant) / _target_value);
	}
	else
	{
		Set(SIGNAL_BREAK);
	}
}

//----------------------------------------------------------------------//

void MotorOperate::Drive_P
(
	const double	_target, 
	const double	_current,
	const double	_constant
)
{
	if (_target > _current)
	{
		Set(SIGNAL_FORWARD);
		
		Set((Pwm)(((_target - _current) * _constant) / _target));
	}
	else if (_target < _current)
	{
		Set(SIGNAL_REVERSE);
		
		Set((Pwm)(((_current - _target) * _constant) / _target));
	}
	else
	{
		Set(SIGNAL_BREAK);
	}
}

//----------------------------------------------------------------------//

void MotorOperate::operator ++ (int i)
{
	Set(Get_pwm() + 1);
}

//----------------------------------------------------------------------//

void MotorOperate::operator -- (int i)
{
	Set(Get_pwm() - 1);
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	MotorLCD															*/
/************************************************************************/

//----------------------------------------------------------------------//

MotorLCD::MotorLCD()
{
	if ( ! LCD::Is_initialize())
	{
		LCD::Initialize();
	}
}

//----------------------------------------------------------------------//

void MotorLCD::Display_power(const LcdAdrs _adrs)
{
	switch (MotorBase::Get_sig())
	{
		case SIGNAL_REVERSE:
		{
			LCD::Write(_adrs, '-');
			
			Display_pwm(_adrs + 1);
			
			break;
		}
		case SIGNAL_FORWARD:
		{
			LCD::Write(_adrs, ' ');
			
			Display_pwm(_adrs + 1);
			
			break;
		}
		default:
		{
			LCD::Write(_adrs, " 00");
			
			break;
		}
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
