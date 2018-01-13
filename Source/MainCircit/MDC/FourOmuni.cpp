
#include <math.h>

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Signal.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>
#include <MainCircit/MDC/Wheel.h>
#include <MainCircit/MDC/FourOmuni.h>

/************************************************************************/

//----------------------------------------------------------------------//

FourOmuni::FourOmuni(const UartNum _uart_num)

	: Wheel(_uart_num, 4)
{
	_mem_move_front_deg = 0;
}

//----------------------------------------------------------------------//

void FourOmuni::Move()
{
	switch (Get_move_direc_y())
	{
		case Direction::NORTH:
		{
			switch (Get_move_direc_x())
			{
				case Direction::EAST:		Move(DEG_MOVE_FRONT_RIGHT);	return (void)0;
				case Direction::WEST:		Move(DEG_MOVE_FRONT_LEFT);	return (void)0;
				case Direction::xCENTER:	Move(DEG_MOVE_FRONT);		return (void)0;
			}
		}
		case Direction::SOUTH:
		{
			switch (Get_move_direc_x())
			{
				case Direction::EAST:		Move(DEG_MOVE_BACK_RIGHT);	return (void)0;
				case Direction::WEST:		Move(DEG_MOVE_BACK_LEFT);	return (void)0;
				case Direction::xCENTER:	Move(DEG_MOVE_BACK);		return (void)0;
			}
		}
		case Direction::yCENTER:
		{
			switch (Get_move_direc_x())
			{
				case Direction::EAST:		Move(DEG_MOVE_RIGHT);	return (void)0;
				case Direction::WEST:		Move(DEG_MOVE_LEFT);	return (void)0;
				case Direction::xCENTER:	Stop();					return (void)0;
			}
		}
	}
}

//----------------------------------------------------------------------//

void FourOmuni::Move(const double _deg)
{
	_motor[WheelPlace::FRONT_RIGHT].Drive(Get_pwm() * sin((_deg -  45 + _mem_move_front_deg) * RAD_PER_DEG));
	_motor[WheelPlace::BACK_RIGHT ].Drive(Get_pwm() * sin((_deg - 135 + _mem_move_front_deg) * RAD_PER_DEG));
	_motor[WheelPlace::BACK_LEFT  ].Drive(Get_pwm() * sin((_deg - 225 + _mem_move_front_deg) * RAD_PER_DEG));
	_motor[WheelPlace::FRONT_LEFT ].Drive(Get_pwm() * sin((_deg - 315 + _mem_move_front_deg) * RAD_PER_DEG));
	
	if (_motor[WheelPlace::FRONT_RIGHT].Get_pwm() == _motor[WheelPlace::BACK_RIGHT].Get_pwm())
	{
		Set(Get_pwm());
	}
}

//----------------------------------------------------------------------//

void FourOmuni::SpinTurn()
{
	switch (Wheel::Get_turn_direc())
	{
		case LEFT_TURN:		MDC::Set(SIGNAL_REVERSE);	break;
		case RIGHT_TURN:	MDC::Set(SIGNAL_FORWARD);	break;
		default:			MDC::Set(SIGNAL_BREAK);		break;
	}
	
	Wheel::Set_record_pwm();
}

//----------------------------------------------------------------------//

void FourOmuni::PivotTurn(const FourWheelPlace _turn_pivot)
{
	SpinTurn();
	
	_motor[_turn_pivot] = SIGNAL_BREAK;
}

//----------------------------------------------------------------------//

void FourOmuni::Adjust_power(const double _persent)
{
	switch (Get_turn_direc())
	{
		case LEFT_TURN:
		{
			for (uByte i = 0; i < 4; i++)
			{
				if (_motor[i] == (_motor[i].Is_signal_reverse() ? SIGNAL_REVERSE : SIGNAL_FORWARD))
				{
					_motor[i] *= (_persent / 100);
				}
			}
			
			break;
		}
		case RIGHT_TURN:
		{
			for (uByte i = 0; i < 4; i++)
			{
				if (_motor[i] == (_motor[i].Is_signal_reverse() ? SIGNAL_FORWARD : SIGNAL_REVERSE))
				{
					_motor[i] *= (_persent / 100);
				}
			}
			
			break;
		}
		default:	break;
	}
}

//----------------------------------------------------------------------//

void FourOmuni::Adjust
(
	const double _fr_persent, 
	const double _br_persent, 
	const double _bl_persent, 
	const double _fl_persent
)
{
	_motor[WheelPlace::FRONT_RIGHT] *= (_fr_persent / 100);
	_motor[WheelPlace::BACK_RIGHT ] *= (_br_persent / 100);
	_motor[WheelPlace::BACK_LEFT  ] *= (_bl_persent / 100);
	_motor[WheelPlace::FRONT_LEFT ] *= (_fl_persent / 100);
}

//----------------------------------------------------------------------//

/************************************************************************/
