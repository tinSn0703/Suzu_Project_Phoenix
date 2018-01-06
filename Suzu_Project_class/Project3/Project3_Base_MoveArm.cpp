
#include <MainCircit/MainCircit.h>

#include "Project3_define.h"
#include "Project3_Base_MoveArm.h"

/************************************************************************/

namespace Project3
{

namespace Base
{

namespace MoveArm
{

/************************************************************************/

//----------------------------------------------------------------------//

MoveUpOrDown :: MoveUpOrDown(const MotorNumber _motor_num, UartTransmit *_uart)

	: _mem_motor(_motor_num)

{
	_mem_is_move_down = _mem_is_move_up = NO;
	
	_mem_motor.Set_uart(_uart);
	
	_mem_motor.Want_to_use_steps(YES);
	
	_mem_motor = 15;
}

//----------------------------------------------------------------------//

void MoveUpOrDown :: Move()
{
	_mem_motor =
	(
		_mem_is_move_up 	? SIGNAL_REVERSE	:
		_mem_is_move_down	? SIGNAL_FORWARD	:
		SIGNAL_BREAK
	);
}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

MoveRotation :: MoveRotation
(
	const MotorNumber	 _motor_num, 
	UartTransmit		*_uart,
	const UartNum		 _lolita_uart_num
)

	: _mem_motor(_motor_num, _uart)
	, _mem_lolita(_lolita_uart_num)
{	
	_mem_is_turn_left = _mem_is_turn_right = NO;
	
	_mem_is_auto_enabled = NO;
	
	_mem_is_o_current = YES;
	
	_mem_target_value = 512;
	
	_mem_data_o = 512;
	_mem_data_r = 0;
	
	_mem_motor.Want_to_use_steps(YES);
	
	_mem_motor = PWM_ROTATION;
}

//----------------------------------------------------------------------//

void MoveRotation :: Read()
{
	_mem_lolita.Receive();
	
	_mem_data_o = _mem_lolita.Get();	
	
	if (_mem_data_o >= 512)		_mem_data_r = _mem_data_o - 512;
	else if (_mem_data_o >= 0)	_mem_data_r = _mem_data_o + 512;
}

//----------------------------------------------------------------------//

void MoveRotation :: Operate(const Direction _move_direction)
{
	_mem_is_auto_enabled = YES;
	
	switch (_move_direction)
	{
		case FRONT:
			_mem_is_o_current = YES;
			_mem_target_value = 512;
		break;
		
		case BACK:
			_mem_is_o_current = NO;
			_mem_target_value = 512;
		break;
		
		case RIGHT:
			_mem_is_o_current = YES;
			_mem_target_value = 256;
		break;
	
		case LEFT:
			_mem_is_o_current = NO;
			_mem_target_value = 256;
		break;
		
		default:
			_mem_is_auto_enabled = NO;
		break;
	}
}

//----------------------------------------------------------------------//

void MoveRotation :: Move_auto()
{
	if (_mem_is_auto_enabled)
	{
		_mem_motor.Adjust_for(8);
		
		_mem_motor.Control_P
		(
			_mem_target_value,
			Truncate(Get_current(), _mem_target_value, 3),
			31,
			NO
		);
	}
	else
	{
		_mem_motor = SIGNAL_BREAK;
	}
}

//----------------------------------------------------------------------//

void MoveRotation :: Move()
{
	if (_mem_is_turn_left)
	{
		_mem_motor.Adjust_for(0);
		
		_mem_motor = PWM_ROTATION;
		
		_mem_motor = SIGNAL_REVERSE;
	}
	else if (_mem_is_turn_right)
	{
		_mem_motor.Adjust_for(0);
		
		_mem_motor = PWM_ROTATION;
		
		_mem_motor = SIGNAL_FORWARD;
	}
	else
	{
		Move_auto();
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

MoveBelt :: MoveBelt(const MotorNumber _motor_num, UartTransmit *_uart)

	: _mem_motor(_motor_num)
{
	_mem_is_turn_left = _mem_is_turn_right = NO;
	
	_mem_motor.Want_to_use_steps(YES);
	
	_mem_motor.Set_uart(_uart);
	
	_mem_motor = 15;
}

//----------------------------------------------------------------------//

void MoveBelt :: Move()
{
	_mem_motor = 
	(
		_mem_is_turn_left	? SIGNAL_REVERSE	:
		_mem_is_turn_right	? SIGNAL_FORWARD	:
		SIGNAL_BREAK
	);
}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

MoveShoulder :: MoveShoulder(const MotorNumber _motor_num, UartTransmit *_uart)

: _mem_motor(_motor_num)
{
	_mem_is_turn_left = _mem_is_turn_right = NO;
	
	_mem_motor.Set_uart(_uart);
	
	_mem_motor.Want_to_use_steps(YES);
	
	_mem_motor = 15;
}

//----------------------------------------------------------------------//

void MoveShoulder :: Move()
{
	_mem_motor =
	(
		_mem_is_turn_left	? SIGNAL_REVERSE	:
		_mem_is_turn_right	? SIGNAL_FORWARD	:
		SIGNAL_BREAK
	);
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

};

/************************************************************************/
