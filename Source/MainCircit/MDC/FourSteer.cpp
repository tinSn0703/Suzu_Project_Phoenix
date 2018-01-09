
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

#define FR_SET_DEG +45.0
#define BR_SET_DEG +135.0
#define BL_SET_DEG -135.0
#define FL_SET_DEG -45.0

#define MAX_LINIT_DEG +120
#define MIN_LINIT_DEG -120

//#define P_CONSTANT 0.344444444	//31/90
//#define P_CONSTANT 0.516666666	//31/60
#define P_CONSTANT 0.6888888888	//31/45

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

void FourSteer::Move_angle_unit(double _deg)
{
	while (1)
	{
		if		(_deg > +90)	_deg -= 180;
		else if	(_deg < -90)	_deg += 180;
		else	break;
	}
	
	_deg *= -1;
	
	_target_deg[WheelPlace::FRONT_RIGHT	] = _deg - 45;
	_target_deg[WheelPlace::BACK_RIGHT	] = _deg + 45;
	_target_deg[WheelPlace::BACK_LEFT	] = _deg - 45;
	_target_deg[WheelPlace::FRONT_LEFT	] = _deg + 45;
	
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		if		(_target_deg[i] > +90)	_target_deg[i] -= 180;
		else if	(_target_deg[i] < -90)	_target_deg[i] += 180;
	}
	
	Matched_wheel_angle();
}

//----------------------------------------------------------------------//

void FourSteer::Matched_wheel_angle()
{
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		if ((_target_deg[i] > _current_deg[i]) && (_current_deg[i] < MAX_LINIT_DEG))
		{
			_motor_angle[i].Set(SIGNAL_FORWARD, (Power)((_target_deg[i] - _current_deg[i]) * P_CONSTANT));
			
			continue;
		}
		
		if ((_target_deg[i] < _current_deg[i]) && (_current_deg[i] > MIN_LINIT_DEG))
		{
			_motor_angle[i].Set(SIGNAL_REVERSE, (Power)((_current_deg[i] - _target_deg[i]) * P_CONSTANT));
			
			continue;
		}
		
		_motor_angle[i].Set(SIGNAL_BREAK);
	}
}

//----------------------------------------------------------------------//

void FourSteer::Set_wheel_power(const double _deg)
{
	if (sin(_deg - FR_SET_DEG + _target_deg[WheelPlace::FRONT_RIGHT]) > 0)
		_motor[WheelPlace::FRONT_RIGHT].Set(SIGNAL_FORWARD);
	else
		_motor[WheelPlace::FRONT_RIGHT].Set(SIGNAL_REVERSE);
	
	if (sin(_deg - BR_SET_DEG + _target_deg[WheelPlace::BACK_RIGHT]) > 0)
		_motor[WheelPlace::BACK_RIGHT].Set(SIGNAL_FORWARD);
	else
		_motor[WheelPlace::BACK_RIGHT].Set(SIGNAL_REVERSE);
	
	if (sin(_deg - BL_SET_DEG + _target_deg[WheelPlace::BACK_LEFT]) > 0)
		_motor[WheelPlace::BACK_LEFT].Set(SIGNAL_FORWARD);
	else
		_motor[WheelPlace::BACK_LEFT].Set(SIGNAL_REVERSE);
	
	if (sin(_deg - FL_SET_DEG + _target_deg[WheelPlace::FRONT_LEFT]) > 0)
		_motor[WheelPlace::FRONT_LEFT].Set(SIGNAL_FORWARD);
	else
		_motor[WheelPlace::FRONT_LEFT].Set(SIGNAL_REVERSE);
	
	Wheel::Set_record_pwm();
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

void FourSteer::Read()
{
	for (int i = 0; i < NUM_WHEEL; i++)
	{
		_angle_meter[i].Read();
		
		_current_deg[i] = ((_angle_meter[i].Get_deg() - 180) * -0.819444444);
	}
	
	_is_angle_set = YES;
}

//----------------------------------------------------------------------//

void FourSteer::Drive_angle_motor
(
	const FourWheelPlace	_place, 
	const Signal			_sig, 
	const Pwm				_pwm
)
{
	if	(
			(_is_angle_set == NO) ||
			((_sig == SIGNAL_FORWARD) && (_current_deg[_place] > MAX_LINIT_DEG)) ||
			((_sig == SIGNAL_REVERSE) && (_current_deg[_place] < MIN_LINIT_DEG))
		)
	{
		_motor_angle[_place].Set(SIGNAL_BREAK);
	}
	else
	{
		_motor_angle[_place].Set(_sig, _pwm);
	}
}

//----------------------------------------------------------------------//

void FourSteer::Move()
{
	switch (Wheel::Get_move_direc_y())
	{
		case Direction::NORTH:
		{
			switch (Wheel::Get_move_direc_x())
			{
				case Direction::EAST:		Move(DEG_MOVE_FRONT_RIGHT);	return (void)0;
				case Direction::WEST:		Move(DEG_MOVE_FRONT_LEFT);	return (void)0;
				case Direction::xCENTER:	Move(DEG_MOVE_FRONT);		return (void)0;
			}
		}
		case Direction::SOUTH:
		{
			switch (Wheel::Get_move_direc_x())
			{
				case Direction::EAST:		Move(DEG_MOVE_BACK_RIGHT);	return (void)0;
				case Direction::WEST:		Move(DEG_MOVE_BACK_LEFT);	return (void)0;
				case Direction::xCENTER:	Move(DEG_MOVE_BACK);		return (void)0;
			}
		}
		case Direction::yCENTER:
		{
			switch (Wheel::Get_move_direc_x())
			{
				case Direction::EAST:		Move(DEG_MOVE_RIGHT);	return (void)0;
				case Direction::WEST:		Move(DEG_MOVE_LEFT);	return (void)0;
				case Direction::xCENTER:	SpinTurn();				return (void)0;
			}
		}
	}
}

//----------------------------------------------------------------------//

void FourSteer::Move(double _deg)
{
	if (_is_angle_set)
	{
		_deg += _machine_front_deg;
		
		while (1)
		{
			if		(_deg > +180)	_deg -= 360;
			else if	(_deg < -180)	_deg += 360;
			else	break;
		}
		
		Move_angle_unit(_deg);
		
		Set_wheel_power(_deg);
	}
	else
	{
		FourSteer::Stop();
	}
}

//----------------------------------------------------------------------//

void FourSteer::SpinTurn()
{
	if ((_is_angle_set) && (Wheel::Get_turn_direc() != NON_TURN))
	{
		_target_deg[WheelPlace::FRONT_RIGHT	] = 0;
		_target_deg[WheelPlace::BACK_RIGHT	] = 0;
		_target_deg[WheelPlace::BACK_LEFT	] = 0;
		_target_deg[WheelPlace::FRONT_LEFT	] = 0;
		
		Matched_wheel_angle();
		
		switch (Wheel::Get_turn_direc())
		{
			case LEFT_TURN:		MDC::Set(SIGNAL_FORWARD);	break;
			case RIGHT_TURN:	MDC::Set(SIGNAL_REVERSE);	break;
			default:	break;
		}
		
		Wheel::Set_record_pwm();
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
		LCD::Write(_adrs + i * 4, _angle_meter[i].Get_data(), 4, DECIMAL_10);
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

/************************************************************************/
