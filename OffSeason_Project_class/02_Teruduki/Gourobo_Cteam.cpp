/*
 * Gourobo_Cteam.cpp
 *
 * Created: 2018/01/13 12:34:32
 *  Author: FUJITSU
 */ 

#include "Gourobo_Cteam.h"

/************************************************************************/

namespace Off2017
{

namespace Teruduki
{
	
namespace Gourobo_Cteam
{

/************************************************************************/

#define INIT_LED()	DDRA = 0xff; PORTA = 0x00

#define PORT_LED	PORTA

#define LED_STATE_LOCK		0x00
#define LED_STATE_UNLOCK	0x0f

/************************************************************************/

//----------------------------------------------------------------------//

Main::Main()

	: _controller(Uart::NUM_0)

	, _wheel(Uart::NUM_1)
	, _motor_arm_raise(4)
	, _motor_arm_thrust(5)

	, _uart_valve(Uart::NUM_3)
	, _valve_thrust(VALVE::NUM_0, VALVE::NUM_1)
{
	if (LCD::Is_initialize())	LCD::Initialize();
	
	INIT_LED();
	
	_wheel.Set_wheel_place(WheelPlace::FRONT_RIGHT,	0);
	_wheel.Set_wheel_place(WheelPlace::BACK_RIGHT,	1);
	_wheel.Set_wheel_place(WheelPlace::BACK_LEFT,	2);
	_wheel.Set_wheel_place(WheelPlace::FRONT_LEFT,	3);
	
	_wheel.Set_front(90);
	
	_wheel.Set(15);
	
	_is_movement_lock = YES;
	
	_is_error_happen = NO;
	
	_is_machine_init = YES;
	
	Dispaly_init();
}

//----------------------------------------------------------------------//

void Main::Dispaly_init()
{
	LCD::Initialize();
	
	LCD::Write(0x00, "  Gourobo C-team");
	LCD::Clear_under();
}

//----------------------------------------------------------------------//

void Main::Lock()
{
	if	(
			(_controller.Get_error_state() == READ_INCOMPLETE)	||
			(_controller.Get_error_state() == READ_FAILURE)
		)
	{
		if (_is_movement_lock == NO)
		{
			_is_error_happen = YES;
		}
		
		_is_movement_lock = YES;
	}
	
	if (_controller.Get_SELECT())
	{
		_is_movement_lock = YES;
	}
}

//----------------------------------------------------------------------//

void Main::Unlock()
{
	if (_controller.Get_error_state() == READ_SUCCESS)
	{
		if (_controller.Get_START())
		{
			_is_machine_init = NO;
			
			_is_movement_lock = NO;
			
			_is_error_happen = NO;
		}
		
		if (_is_error_happen & _controller.Is_commnad_push())
		{
			_is_movement_lock = NO;
			
			_is_error_happen = NO;
		}
	}
}

//----------------------------------------------------------------------//

void Main :: Input()
{
	_controller.Read();
	
	Unlock();
	
	Lock();
	
	_is_move_front	= _controller[L_STICK_NORTH];
	_is_move_back	= _controller[L_STICK_SOUTH];
	_is_move_right	= _controller[L_STICK_EAST];
	_is_move_left	= _controller[L_STICK_WEST];
}

//----------------------------------------------------------------------//

void Main::Set_wheel_turn()
{
	if (_controller.Get_L())
	{
		_wheel.Set_turn_direction(LEFT_TURN);
	}
	else if (_controller.Get_R())
	{
		_wheel.Set_turn_direction(RIGHT_TURN);
	}
	else
	{
		_wheel.Set_turn_direction(NON_TURN);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_right()
{
	if (_is_move_front)
	{
		_wheel.Set_steps(STEPS_USE);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK_LEFT);
	}
	else if (_is_move_back)
	{
		_wheel.Set_steps(STEPS_USE);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK_RIGHT);
	}
	else
	{
		_wheel.Set_steps(STEPS_USE);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_RIGHT);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_left()
{
	if (_is_move_front)
	{
		_wheel.Set_steps(STEPS_USE);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_FRONT_LEFT);
	}
	else if (_is_move_back)
	{
		_wheel.Set_steps(STEPS_USE);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK_LEFT);
	}
	else
	{
		_wheel.Set_steps(STEPS_USE);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_LEFT);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_front()
{
	if (_is_move_right)
	{
		_wheel.Set_steps(STEPS_USE);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_FRONT_RIGHT);
	}
	else if (_is_move_left)
	{
		_wheel.Set_steps(STEPS_USE);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_FRONT_LEFT);
	}
	else
	{
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_FRONT);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_back()
{
	if (_is_move_right)
	{
		_wheel.Set_steps(STEPS_USE);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK_RIGHT);
	}
	else if (_is_move_left)
	{
		_wheel.Set_steps(STEPS_USE);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK_LEFT);
	}
	else
	{
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_turn()
{
	_wheel.Set_steps(STEPS_USE);
	
	_wheel.SpinTurn();
}

//----------------------------------------------------------------------//

void Main::Move_wheel()
{
	Set_wheel_turn();
	
	if (_is_move_front)
	{
		Move_wheel_front();
	}
	else if (_is_move_back)
	{
		Move_wheel_back();
	}
	else if (_is_move_right)
	{
		Move_wheel_right();
	}
	else if (_is_move_left)
	{
		Move_wheel_left();
	}
	else if (_wheel.Get_turn_direc() != NON_TURN)
	{
		Move_wheel_turn();
	}
	else
	{
		_wheel.Stop();
	}
}

//----------------------------------------------------------------------//

void Main::Process()
{
	if (_is_movement_lock == NO)
	{
		Move_wheel();
		
		if		(_controller.Get_X())	_motor_arm_raise.Set(SIGNAL_FORWARD, 15);
		else if	(_controller.Get_B())	_motor_arm_raise.Set(SIGNAL_REVERSE, 15);
		else							_motor_arm_raise.Set(SIGNAL_BREAK);
		
		if		(_controller.Get_A())	_motor_arm_thrust.Set(SIGNAL_FORWARD, 7);
		else if	(_controller.Get_Y())	_motor_arm_thrust.Set(SIGNAL_REVERSE, 7);
		else							_motor_arm_thrust.Set(SIGNAL_BREAK);
		
		_valve_thrust.Open_and_Close(_controller.Get_cross_key(Direction::NORTH), 500);
	}
}

//----------------------------------------------------------------------//

void Main :: Output()
{
	if (_is_movement_lock)
	{
		if (PORT_LED == LED_STATE_UNLOCK)
		{
			if (_is_machine_init == NO)
			{
				if (_controller.Get_error_state() == READ_FAILURE)
				{
					LCD::Write(0x00, "      Read Error");
					LCD::Write(0x00, "         Failure");
				}
				else if (_controller.Get_error_state() == READ_INCOMPLETE)
				{
					LCD::Write(0x00, "      Read Error");
					LCD::Write(0x40, "      Incomplete");
				}
				else
				{
					LCD::Write(0x00, "       Lock Mode");
					LCD::Clear_under();
				}
			}
			
			PORT_LED = LED_STATE_LOCK;
		}
		
		_wheel.Write_clear();
		
		_motor_arm_raise.Write_clear(_wheel.Get_uart_adrs());
		
		_motor_arm_thrust.Write_clear(_wheel.Get_uart_adrs());
	}
	else
	{
		if (PORT_LED == LED_STATE_LOCK)
		{
			Dispaly_init();
			
			PORT_LED = LED_STATE_UNLOCK;
		}
		
		_uart_valve.Transmit_8bit(_valve_thrust.Get_data());
		
		_wheel.Write();
		
		_motor_arm_raise.Write(_wheel.Get_uart_adrs());
		
		_motor_arm_thrust.Write(_wheel.Get_uart_adrs());
		
		_wheel.Display_power(0x40);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}
}
}

/************************************************************************/
