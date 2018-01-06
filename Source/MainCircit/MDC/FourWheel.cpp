
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/AVR.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Signal.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>
#include <MainCircit/MDC/Wheel.h>
#include <MainCircit/MDC/FourWheel.h>

/************************************************************************/

//----------------------------------------------------------------------//

FourWheel::FourWheel(const UartNum _uart_num)

	: Wheel(_uart_num, 4)
{}

//----------------------------------------------------------------------//

FourWheel::FourWheel
(
	const UartNum	_uart_num, 
	const MotorNum	_fr_num, 
	const MotorNum	_br_num, 
	const MotorNum	_bl_num, 
	const MotorNum	_fl_num
)

	: Wheel(_uart_num, 4)
{
	_motor[WheelPlace::FRONT_RIGHT].Reset(_fr_num);
	_motor[WheelPlace::BACK_RIGHT ].Reset(_br_num);
	_motor[WheelPlace::BACK_LEFT  ].Reset(_bl_num);
	_motor[WheelPlace::FRONT_LEFT ].Reset(_fl_num);
}

//----------------------------------------------------------------------//

void FourWheel::Move()
{
	const Signal _temp_right = To_Signal(			Get_move_direc_y());
	const Signal _temp_left  = To_Signal(Reversal(	Get_move_direc_y()));
	
	_motor[WheelPlace::FRONT_RIGHT] = _temp_right;
	_motor[WheelPlace::BACK_RIGHT ] = _temp_right;
	_motor[WheelPlace::BACK_LEFT  ] = _temp_left;
	_motor[WheelPlace::FRONT_LEFT ] = _temp_left;
	
	Set_record_pwm();
}

//----------------------------------------------------------------------//

void FourWheel::SpinTurn(const YesNo _is_turn_l, const YesNo _is_turn_r)
{
	Set
	(
		_is_turn_l ? SIGNAL_FORWARD :
		_is_turn_r ? SIGNAL_REVERSE :
		SIGNAL_BREAK
	);
	
	Set_record_pwm();
}

//----------------------------------------------------------------------//

void FourWheel::Curve
(
	const double	_curve_persent, 
	const YesNo		_is_turn_l, 
	const YesNo		_is_turn_r
)
{
	Move();
	
	if (_is_turn_l)
	{
		_motor[WheelPlace::FRONT_RIGHT] *= (_curve_persent / 100);
		_motor[WheelPlace::BACK_RIGHT ] *= (_curve_persent / 100);
	}
	else if (_is_turn_r)
	{
		_motor[WheelPlace::FRONT_LEFT ] *= (_curve_persent / 100);
		_motor[WheelPlace::BACK_LEFT  ] *= (_curve_persent / 100);
	}
}

//----------------------------------------------------------------------//

void FourWheel::Stop()
{
	_motor[0].Set(SIGNAL_BREAK);
	_motor[1].Set(SIGNAL_BREAK);
	_motor[2].Set(SIGNAL_BREAK);
	_motor[3].Set(SIGNAL_BREAK);
}

//----------------------------------------------------------------------//

/************************************************************************/