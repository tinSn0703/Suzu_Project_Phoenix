
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

const double UNIT_SET_DEG[NUM_WHEEL] = {+45.0, +135.0, -135.0, -45.0};

#define MAX_LINIT_DEG +120
#define MIN_LINIT_DEG -120

//#define P_CONSTANT 0.344444444	//31/90
//#define P_CONSTANT 0.516666666	//31/60
#define P_CONSTANT 0.6888888888	//31/45

#define READ_CONSTANT -0.819444444

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

void FourSteer::Set_target_angle
(
	const double _deg_fr,
	const double _deg_br,
	const double _deg_bl,
	const double _deg_fl
)
{
	_target_deg[WheelPlace::FRONT_RIGHT	] = _deg_fr;
	_target_deg[WheelPlace::BACK_RIGHT	] = _deg_br;
	_target_deg[WheelPlace::BACK_LEFT	] = _deg_bl;
	_target_deg[WheelPlace::FRONT_LEFT	] = _deg_fl;
}

//----------------------------------------------------------------------//

void FourSteer::Set_target_angle(double _deg)
{
	while (1)
	{
		if		(_deg > +90)	_deg -= 180;
		else if	(_deg < -90)	_deg += 180;
		else	break;
	}
	
	_deg *= -1;
	
	Set_target_angle(_deg - 45, _deg + 45, _deg - 45, _deg + 45);
}

//----------------------------------------------------------------------//

void FourSteer::Set_target_angle(double _deg, const double _curve_persent)
{
	Set_target_angle(_deg);
	
	if (Wheel::Get_turn_direc() != NON_TURN)
	{
		class Ramuda
		{
			double _persent;
			
		public:
			
			Ramuda(double _persent)	{	this->_persent = _persent;	}
			
			double operator () (uByte i, double _low_min, double _low_max, double _high_min, double _high_max)
			{
				if ((_high_max >= UNIT_SET_DEG[i]) && (UNIT_SET_DEG[i] >  _high_min))	return (90 * _persent / 100);
				if ((_low_max  >  UNIT_SET_DEG[i]) && (UNIT_SET_DEG[i] >= _low_min))	return (90 * _persent / 100);
				
				return 0;
			}
		}
		Plus_curve(_curve_persent);
		
		switch (Wheel::Get_turn_direc())
		{
			case RIGHT_TURN:
			{
				for (uByte i = 0; i < NUM_WHEEL; i++)
				{
					if		(_deg > +90)	_target_deg[i] += Plus_curve(i, _deg - 270,	_deg - 180,	_deg - 90,	_deg		);
					else if	(_deg < -90)	_target_deg[i] += Plus_curve(i, _deg,		_deg + 90,	_deg + 180,	_deg + 270	);
					else					_target_deg[i] += Plus_curve(i, _deg - 90,	_deg,		_deg,		_deg + 90	);
				}
				
				break;
			}
			case LEFT_TURN:
			{
				for (uByte i = 0; i < NUM_WHEEL; i++)
				{
					if		(_deg > +90)	_target_deg[i] -= Plus_curve(i, _deg - 270,	_deg - 180,	_deg - 90,	_deg		);
					else if	(_deg < -90)	_target_deg[i] -= Plus_curve(i, _deg,		_deg + 90,	_deg + 180,	_deg + 270	);
					else					_target_deg[i] -= Plus_curve(i, _deg - 90,	_deg,		_deg,		_deg + 90	);
				}
				
				break;
			}
			default:	break;
		}
	}
}

//----------------------------------------------------------------------//

void FourSteer::Set_angle_motor_power()
{
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		if		(_target_deg[i] > +120)	_target_deg[i] -= 180;
		else if	(_target_deg[i] < -120)	_target_deg[i] += 180;
		
		if (_target_deg[i] > _current_deg[i])
		{
			_motor_angle[i].Set
			(
				SIGNAL_FORWARD, 
				(Power)((_target_deg[i] - _current_deg[i]) * P_CONSTANT)
			);
			
			if (_motor_angle[i].Get_pwm() < 3)	_motor_angle[i] = SIGNAL_BREAK;
			
			continue;
		}
		
		if (_target_deg[i] < _current_deg[i])
		{
			_motor_angle[i].Set
			(
				SIGNAL_REVERSE, 
				(Power)((_current_deg[i] - _target_deg[i]) * P_CONSTANT)
			);
			
			if (_motor_angle[i].Get_pwm() < 3)	_motor_angle[i] = SIGNAL_BREAK;
			
			continue;
		}
		
		_motor_angle[i].Set(SIGNAL_BREAK);
	}
}

//----------------------------------------------------------------------//

void FourSteer::Set_wheel_power(const TurnDirection _turn)
{
	switch (_turn)
	{
		case LEFT_TURN:
		{
			for (uByte i = 0; i < NUM_WHEEL; i++)
			{
				_motor[i].Set(Wheel::Get_pwm());
				
				if (_motor_angle[i].Get_pwm() < 2)	_motor[i].Set(SIGNAL_REVERSE);
				else								_motor[i].Set(SIGNAL_BREAK);
			}
			
			break;
		}
		case RIGHT_TURN:
		{
			for (uByte i = 0; i < NUM_WHEEL; i++)
			{
				_motor[i].Set(Wheel::Get_pwm());
				
				if (_motor_angle[i].Get_pwm() < 2)	_motor[i].Set(SIGNAL_FORWARD);
				else								_motor[i].Set(SIGNAL_BREAK);
			}
			
			break;
		}
		case NON_TURN:
		{
			MDC::Set(SIGNAL_BREAK);
			
			break;
		}
	}
}

//----------------------------------------------------------------------//

void FourSteer::Set_wheel_power(const double _deg)
{
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		if (_motor_angle[i].Get_pwm() < 4)
		{
			_motor[i].Set(Wheel::Get_pwm());
			
			if (sin((_deg - UNIT_SET_DEG[i] + _target_deg[i]) * RAD_PER_DEG) > 0)
			{
				_motor[i].Set(SIGNAL_FORWARD);
			}
			else
			{
				_motor[i].Set(SIGNAL_REVERSE);
			}
		}
		else
		{
			_motor[i].Set(SIGNAL_BREAK);
		}
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

void FourSteer::Read()
{
	for (int i = 0; i < NUM_WHEEL; i++)
	{
		_angle_meter[i].Read();
		
		_current_deg[i] = ((_angle_meter[i].Get_deg() - 180) * READ_CONSTANT);
	}
	
	_is_angle_set = YES;
}

//----------------------------------------------------------------------//

void FourSteer::Move_wheel_unit
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
				case Direction::EAST:		Move(+45);	return (void)0;
				case Direction::WEST:		Move(-45);	return (void)0;
				case Direction::xCENTER:	Move(0);	return (void)0;
			}
		}
		case Direction::SOUTH:
		{
			switch (Wheel::Get_move_direc_x())
			{
				case Direction::EAST:		Move(+135);	return (void)0;
				case Direction::WEST:		Move(-135);	return (void)0;
				case Direction::xCENTER:	Move(180);	return (void)0;
			}
		}
		case Direction::yCENTER:
		{
			switch (Wheel::Get_move_direc_x())
			{
				case Direction::EAST:		Move(+90);	return (void)0;
				case Direction::WEST:		Move(-90);	return (void)0;
				case Direction::xCENTER:	Stop();		return (void)0;
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
		
		Set_target_angle(_deg);
		
		Set_angle_motor_power();
		
		Set_wheel_power(_deg);
	}
	else
	{
		FourSteer::Stop();
	}
}

//----------------------------------------------------------------------//

void FourSteer::Curve(const double _curve_persent)
{
	switch (Wheel::Get_move_direc_y())
	{
		case Direction::NORTH:
		{
			switch (Wheel::Get_move_direc_x())
			{
				case Direction::EAST:		Curve(+45, _curve_persent);	return (void)0;
				case Direction::WEST:		Curve(-45, _curve_persent);	return (void)0;
				case Direction::xCENTER:	Curve(0, _curve_persent);	return (void)0;
			}
		}
		case Direction::SOUTH:
		{
			switch (Wheel::Get_move_direc_x())
			{
				case Direction::EAST:		Curve(+135, _curve_persent);	return (void)0;
				case Direction::WEST:		Curve(-135, _curve_persent);	return (void)0;
				case Direction::xCENTER:	Curve(180, _curve_persent);		return (void)0;
			}
		}
		case Direction::yCENTER:
		{
			switch (Wheel::Get_move_direc_x())
			{
				case Direction::EAST:		Curve(+90, _curve_persent);	return (void)0;
				case Direction::WEST:		Curve(-90, _curve_persent);	return (void)0;
				case Direction::xCENTER:	Stop();						return (void)0;
			}
		}
	}
}

//----------------------------------------------------------------------//

void FourSteer::Curve(double _deg, const double _curve_persent)
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
		
		Set_target_angle(_deg, _curve_persent);
		
		Set_angle_motor_power();
		
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
		Set_target_angle(0, 0, 0, 0);
		
		Set_angle_motor_power();
		
		Set_wheel_power(Wheel::Get_turn_direc());
	}
	else
	{
		FourSteer::Stop();
	}
}

//----------------------------------------------------------------------//

void FourSteer::PivotTurn(const FourWheelPlace _turn_pivot)
{
	if ((_is_angle_set) && (Wheel::Get_turn_direc() != NON_TURN))
	{
		switch (_turn_pivot)
		{
			case WheelPlace::FRONT_RIGHT:	Set_target_angle(90, -45, 0, 45);	break;
			case WheelPlace::BACK_RIGHT:	Set_target_angle(45, 90, -45, 0);	break;
			case WheelPlace::BACK_LEFT:		Set_target_angle(0, 45, 90, -45);	break;
			case WheelPlace::FRONT_LEFT:	Set_target_angle(-45, 0, 45, 90);	break;
		}
		
		Set_angle_motor_power();
		
		Set_wheel_power(Wheel::Get_turn_direc());
		
		_motor[_turn_pivot].Set(SIGNAL_BREAK);
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

void FourSteer::Write_clear()
{
	MDC::Write_clear();
	
	for (uByte i = 0; i < NUM_WHEEL; i++)
	{
		_motor_angle[i].Write_clear(MDC::Get_uart_adrs());
	}
	
	_is_angle_set = NO;
}

//----------------------------------------------------------------------//

void FourSteer::Dispaly_meter_data(const LcdAdrs _adrs)
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
