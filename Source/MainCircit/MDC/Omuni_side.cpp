
#include <math.h>

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>
#include <MainCircit/MDC/Wheel.h>
#include <MainCircit/MDC/Omuni.h>

/************************************************************************/

namespace Four
{

namespace Side
{

/************************************************************************/

//----------------------------------------------------------------------//

Omuni :: Omuni(MotorNumber _min_num, UartNum _uart_num)

	: Wheel(_min_num, _uart_num, 4)
{}

//----------------------------------------------------------------------//

void Omuni :: Move()
{
	//2017 4/5
	//ちゃんと動くかわかってないのでチェックを忘れないでください
	
	_motor[FRONT] = To_Signal(Reversal(	Get_direc_x()));
	_motor[LEFT ] = To_Signal(Reversal(	Get_direc_y()));
	_motor[BACK ] = To_Signal(			Get_direc_x());
	_motor[RIGHT] = To_Signal(			Get_direc_y());
	
	Set_record_pwm();
}

//----------------------------------------------------------------------//

void Omuni :: Move(const double _deg)
{
	const double _rad = (_deg * PI / 180);
	
	_motor[FRONT].Set_action(Get_pwm() * +sin(_rad));
	_motor[RIGHT].Set_action(Get_pwm() * -cos(_rad));
	_motor[BACK ].Set_action(Get_pwm() * -sin(_rad));
	_motor[LEFT ].Set_action(Get_pwm() * +cos(_rad));
	
	if (_motor[FRONT].Get_pwm() == _motor[RIGHT].Get_pwm())
	{
		Set(Get_pwm());
	}
}

//----------------------------------------------------------------------//

void Omuni :: SpinTurn(const YesNo _is_turn_l, const YesNo _is_turn_r)
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

void Omuni :: Adjust_power
(
	const double	_persent,
	const YesNo		_is_turn_l,
	const YesNo		_is_turn_r
)
{
	if (_is_turn_l)
	{
		for (uByte i = 0; i < 4; i++)
		{
			if (_motor[i] == SIGNAL_FORWARD)	_motor[i] *= (_persent / 100);
		}
	}
	
	if (_is_turn_r)
	{
		for (uByte i = 0; i < 4; i++)
		{
			if (_motor[i] == SIGNAL_REVERSE)	_motor[i] *= (_persent / 100);
		}
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

/************************************************************************/
