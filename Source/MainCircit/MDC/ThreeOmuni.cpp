
#include <math.h>

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Signal.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>
#include <MainCircit/MDC/Wheel.h>
#include <MainCircit/MDC/ThreeOmuni.h>

/************************************************************************/

//----------------------------------------------------------------------//

ThreeOmuni::ThreeOmuni(const UartNum _uart_num)

	: Wheel(_uart_num, 3)
{}

//----------------------------------------------------------------------//

ThreeOmuni::ThreeOmuni
(
	const UartNum	_uart_num, 
	const MotorNum	_front_number, 
	const MotorNum	_left_number, 
	const MotorNum	_right_number
)

	: Wheel(_uart_num, 3)
{
	_motor[WheelPlace::FRONT].Reset(_front_number);
	_motor[WheelPlace::LEFT ].Reset(_left_number);
	_motor[WheelPlace::RIGHT].Reset(_right_number);
}

//----------------------------------------------------------------------//

void ThreeOmuni::Move(const double _deg)
{
	_motor[WheelPlace::FRONT].Drive(sin((_deg -   0) * PI / 180) * Get_pwm());
	_motor[WheelPlace::LEFT ].Drive(sin((_deg - 120) * PI / 180) * Get_pwm());
	_motor[WheelPlace::RIGHT].Drive(sin((_deg - 240) * PI / 180) * Get_pwm());
	
	if (_motor[WheelPlace::FRONT] == SIGNAL_BREAK)
	{
		_motor[WheelPlace::LEFT ] = Get_pwm();
		_motor[WheelPlace::RIGHT] = Get_pwm();
	}

	if (_motor[WheelPlace::LEFT ] == SIGNAL_BREAK)
	{
		_motor[WheelPlace::FRONT] = Get_pwm();
		_motor[WheelPlace::RIGHT] = Get_pwm();
	}

	if (_motor[WheelPlace::RIGHT] == SIGNAL_BREAK)
	{
		_motor[WheelPlace::FRONT] = Get_pwm();
		_motor[WheelPlace::LEFT ] = Get_pwm();
	}
}

//----------------------------------------------------------------------//

void ThreeOmuni::Move()
{	
	switch (Get_move_direc_y())
	{
		case Direction::NORTH:
		{
			switch (Get_move_direc_x())
			{
				case Direction::EAST:		Move(-45);	return (void)0;
				case Direction::WEST:		Move( 45);	return (void)0;
				case Direction::xCENTER:	Move(  0);	return (void)0;
			}
		}
		case Direction::SOUTH:
		{
			switch (Get_move_direc_x())
			{
				case Direction::EAST:		Move(-135);	return (void)0;
				case Direction::WEST:		Move( 135);	return (void)0;
				case Direction::xCENTER:	Move( 180);	return (void)0;
			}
		}
		case Direction::yCENTER:
		{
			switch (Get_move_direc_x())
			{
				case Direction::EAST:		Move(-90);	return (void)0;
				case Direction::WEST:		Move( 90);	return (void)0;
				case Direction::xCENTER:	Stop();		return (void)0;
			}
		}
	}
}

//----------------------------------------------------------------------//

void ThreeOmuni::SpinTurn(const YesNo _is_turn_l, const YesNo _is_turn_r)
{
	Set
	(
		_is_turn_l	? SIGNAL_REVERSE :
		_is_turn_r	? SIGNAL_FORWARD :
		SIGNAL_BREAK
	);
	
	Set_record_pwm();
}

//----------------------------------------------------------------------//

void ThreeOmuni::Adjust_power
(
	const double	_persent,
	const YesNo		_is_turn_l,
	const YesNo		_is_turn_r
)
{
	if (_is_turn_l)
	{
		for (uByte i = 0; i < 3; i++)
		{
			if (_motor[i] == SIGNAL_FORWARD)	_motor[i] *= (_persent / 100);
		}
	}
	
	if (_is_turn_r)
	{
		for (uByte i = 0; i < 3; i++)
		{
			if (_motor[i] == SIGNAL_REVERSE)	_motor[i] *= (_persent / 100);
		}
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
