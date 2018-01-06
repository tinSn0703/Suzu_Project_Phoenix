
#include <math.h>
#include <stdio.h>

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/ADChange/ADChange.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Signal.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>
#include <MainCircit/MDC/Wheel.h>
#include <MainCircit/MDC/FourSteer.h>

/************************************************************************/

#define RAD_PER_AD 0.006141921	//2ƒÎ/1023
#define DEG_PER_AD 0.351906158	//360/1023

#define P_CONSTANT 0.344444444	//31/90

/************************************************************************/

//----------------------------------------------------------------------//

FourSteer::FourSteer(const UartNum _uart_num)

	: Wheel(_uart_num, 4)
{
	_is_angle_set = NO;
	
	_machine_front_deg = 0;
	
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		_target_deg[i]  = 0;
		_current_deg[i] = 0;
		
		_motor_angle[i].Reset(i + 4);
	}
}

//----------------------------------------------------------------------//

void FourSteer::Set_angle_unit_place
(
	const FourWheelPlace	_place, 
	const MotorNum			_motoro_num, 
	const ADNum				_ad_num
)
{
	_motor_angle[_place].Reset(_motoro_num);
	_meter_angle[_place].Reset(_ad_num, NO);
}

//----------------------------------------------------------------------//

void FourSteer::Set_wheel_place(const FourWheelPlace _place, const MotorNum _num)
{
	_motor[_place].Reset(_num);
}

//----------------------------------------------------------------------//

void FourSteer::Move_wheel(const double _move_deg)
{
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		_target_deg[i] = _move_deg;
		
		if ((_current_deg[i] > 0) && (_target_deg[i] == -180))
			_target_deg[i] = +180;
		else if ((_current_deg[i] < 0) && (_target_deg[i] == +180))
			_target_deg[i] = -180;

		if ((_target_deg[i] > 0) || ((_target_deg[i] == 0) && (_current_deg[i] < 0)))
		{
			if ((_target_deg[i] - 90) > _current_deg[i])
			{
				_target_deg[i] -= 180;
				
				_motor[i].Set(SIGNAL_REVERSE);
			}
			else
			{
				_motor[i].Set(SIGNAL_FORWARD);
			}
		}
		else if ((_target_deg[i] < 0) || ((_target_deg[i] == 0) && (_current_deg[i] > 0)))
		{
			if ((_target_deg[i] + 90) < _current_deg[i])
			{
				_target_deg[i] += 180;

				_motor[i].Set(SIGNAL_REVERSE);
			}
			else
			{
				_motor[i].Set(SIGNAL_FORWARD);
			}
		}
	}
	
	Wheel::Set_record_pwm();
}

//----------------------------------------------------------------------//

void FourSteer::Matched_wheel_angle()
{
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		_motor_angle[i].Control((Power)((_target_deg[i] - _current_deg[i]) * P_CONSTANT));
	}
}

//----------------------------------------------------------------------//

void FourSteer::Read()
{
	for (int i = 0; i < NUM_WHEEL; i++)
	{
		_current_deg[i] = ((((double)_meter_angle[i].Read() * DEG_PER_AD) - 180) * -1);
	}
	
	_is_angle_set = YES;
}

//----------------------------------------------------------------------//

void FourSteer::Move_angle_motor
(
	const FourWheelPlace	_place, 
	const Signal			_sig, 
	const Pwm				_pwm
)
{
	if	(
			(_is_angle_set == NO) ||
			((_sig == SIGNAL_FORWARD) && (_current_deg[_place] >= +170)) ||
			((_sig == SIGNAL_REVERSE) && (_current_deg[_place] <= -170))
		)
	{
		return (void)0;
	}
	
	_motor_angle[_place].Set(_sig, _pwm);
}

//----------------------------------------------------------------------//

void FourSteer::Move(const double _deg)
{
	if (_is_angle_set)
	{
		Move_wheel(_deg);
		
		Matched_wheel_angle();
	}
	else
	{
		FourSteer::Stop();
	}
}

//----------------------------------------------------------------------//

void FourSteer::Move(const Pwm _r, const double _deg)
{
	Wheel::Record_pwm(_r);
	
	Move(_deg);
}

//----------------------------------------------------------------------//

void FourSteer::SpinTurn()
{
	if (_is_angle_set)
	{
		_target_deg[WheelPlace::FRONT_RIGHT	] = -45;
		_target_deg[WheelPlace::BACK_RIGHT	] = +45;
		_target_deg[WheelPlace::BACK_LEFT	] = -45;
		_target_deg[WheelPlace::FRONT_LEFT	] = +45;
		
		switch (Wheel::Get_turn_direc())
		{
			case LEFT_TURN:		Set(SIGNAL_FORWARD);	break;
			case RIGHT_TURN:	Set(SIGNAL_REVERSE);	break;
			default:			Set(SIGNAL_BREAK);		break;
		}
		
		Wheel::Set_record_pwm();
		
		Matched_wheel_angle();
	}
	else
	{
		FourSteer::Stop();
	}
}

//----------------------------------------------------------------------//

void FourSteer::Stop()
{
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		_motor[i].Set(SIGNAL_BREAK);
		_motor_angle[i].Set(SIGNAL_BREAK);
	}
}

//----------------------------------------------------------------------//

void FourSteer::Write()
{
	MDC::Write();
	
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		_motor_angle[i].Write(MDC::Get_uart_adrs());
	}
	
	_is_angle_set = NO;
}

//----------------------------------------------------------------------//

void FourSteer::Dispaly_ad_data(const LcdAdrs _adrs)
{
	for (uByte i = 0; i < NUM_WHEEL; i ++)
	{
		LCD::Write(_adrs + i * 4, _meter_angle[i].Get_data(), 4, DECIMAL_10);
	}
}

//----------------------------------------------------------------------//

void FourSteer::Dispaly_angle(const LcdAdrs _adrs, const double _deg)
{
	if ((-1 < _deg) && (_deg < 1))
	{
		LCD::Write(_adrs, " 000");
	}
	else if (_deg > 0)
	{
		LCD::Write(_adrs, '+');
		
		LCD::Write(_adrs + 1, (int)_deg, 3, DECIMAL_10);
	}
	else if (_deg < 0)
	{
		LCD::Write(_adrs, '-');
		
		LCD::Write(_adrs + 1, (int)(_deg * -1), 3, DECIMAL_10);
	}
}

//----------------------------------------------------------------------//

void FourSteer::Dispaly_current_angle(const LcdAdrs _adrs)
{
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		Dispaly_angle(_adrs + 4 * i, _current_deg[i]);
	}
}

//----------------------------------------------------------------------//

void FourSteer::Dispaly_target_angle(const LcdAdrs _adrs)
{
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		Dispaly_angle(_adrs + 4 * i, _target_deg[i]);
	}
}

//----------------------------------------------------------------------//

void FourSteer::Display_angle_motor_power(const LcdAdrs _adrs)
{
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		_motor_angle[i].Display_power(_adrs + 3 * i);
	}
}

//----------------------------------------------------------------------//

void FourSteer::Display_wheel_power(const LcdAdrs _adrs)
{
	Display_power(_adrs);
}

//----------------------------------------------------------------------//

/************************************************************************/
