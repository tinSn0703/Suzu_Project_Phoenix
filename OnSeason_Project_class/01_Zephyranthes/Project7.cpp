
#include <MainCircit/MainCircit.h>

#include "Project7.h"

/************************************************************************/

namespace Zephyranthes
{

namespace Shotgun
{

/************************************************************************/

Main :: Main()

	: _controller(Uart::NUM_0)
	
	, _uart_motor(Uart::NUM_1)
	, _motor_widch(0)
	, _motor_turn(1)
	
	,_uart_valve(Uart::NUM_2)
	, _valve_transform(VALVE::NUM_1)
	, _valve_stopper(VALVE::NUM_0)
	, _valve_trigger(VALVE::NUM_2)
	
	, _check_enemy_line(IO::NUM_F, IO::BIT_0)
{
	LCD::Initialize();
	
	LCD::Write(0x00, "102 Zephyranthes", 75);
	LCD::Write(0x40, "Name     Shotgun");
	
	_is_movement_lock = YES;
	
	_is_transform_enable = YES;
	
	_is_lcd_change = YES;
	
	_motor_widch.Set_steps(STEPS_USE);
	
	_motor_widch = 15;
	
	_motor_turn.Set_steps(STEPS_USE);
	
	_motor_turn = 15;
	
	_timer_transform = 0;
	
	_before_valve_data = 0x00;
	
	_uart_valve.Transmit_8bit(0x00);
}

/************************************************************************/

void Main :: Receive_operation()
{
	_controller.Read();
	
	if (_controller.Get_SELECT() | _controller.Get_error_state())
	{
		LCD::Write(0x40, "Lock Mode       ");
		
		_is_movement_lock = YES;
	}
	
	if (_controller.Get_START())
	{
		_is_lcd_change = YES;
		
		_is_movement_lock = NO;
	}
}

/************************************************************************/

YesNo Main :: Is_movement_lock()
{
	return _is_movement_lock;
}

/************************************************************************/

void Main :: Move_glide_mode()
{
	if (_controller.Get_L3() | _check_enemy_line.Read())
	{
		if (_timer_transform == 0)
		{
			_valve_stopper.Want_to_open(YES);
			
			_timer_transform = Timer::General::Set_counter(200);
		}
	}
	else
	{
		_is_transform_enable = YES;
	}
	
	if	(
			Timer::General::Is_current_bigger_than(_timer_transform)	&
			_valve_stopper.Is_open()								&
			_is_transform_enable
		)
	{
		_valve_transform.Want_to_open(YES);
		
		_is_transform_enable = NO;
		
		_timer_transform = 0;
	}
	
	if (_controller.Get_Circle())
	{
		_valve_transform.Want_to_open(NO);
		
		_valve_stopper.Want_to_open(NO);
	}
}

/************************************************************************/

void Main :: Move_bombard_mode()
{
	if (_valve_transform.Is_open())
	{
		_motor_widch =
		(
			_controller.Get_R1() ? SIGNAL_REVERSE :
			_controller.Get_L1() ? SIGNAL_FORWARD :
			SIGNAL_BREAK
		);
		
		_motor_turn =
		(
			_controller.Get_R2() ? SIGNAL_REVERSE :
			_controller.Get_L2() ? SIGNAL_FORWARD :
			SIGNAL_BREAK
		);
		
		_valve_trigger.Want_to_open(_controller.Get_R3() | _valve_trigger.Is_open());
		
		if (_controller.Get_Square())	_valve_trigger.Want_to_open(NO);
	}
}

/************************************************************************/

void Main :: Work()
{
	Main::Move_glide_mode();
	
	Main::Move_bombard_mode();
	
	if (_valve_transform.Is_open())
	{
		_motor_turn.Write(_uart_motor);
		
		_motor_widch.Write(_uart_motor);
	}
	else
	{
		_motor_turn.Write_clear(_uart_motor);
		
		_motor_widch.Write_clear(_uart_motor);
	}
	
	const UartData8bit _transmit_data =
	(
		_valve_transform.Get_data()	|
		_valve_trigger.Get_data()	|
		_valve_stopper.Get_data()
	);
	
	if (_transmit_data != _before_valve_data)
	{
		_uart_valve.Transmit_8bit(_transmit_data);
		
		_before_valve_data = _transmit_data;
	}
}

/************************************************************************/

void Main :: Display()
{
	if (_valve_transform.Is_open())
	{
		if (_valve_trigger.Is_open())
		{
			LCD::Write(0x40, "Mission Complete");
		}
		else
		{
			LCD::Write(0x40, "Bombard Mode    ");
		}
	}
	else
	{
		LCD::Write(0x40, "Glide Mode      ");
	}
}

/************************************************************************/

void Main :: Stop()
{
	_motor_turn.Write_clear(_uart_motor);
	
	_motor_widch.Write_clear(_uart_motor);
}

/************************************************************************/

}

}

/************************************************************************/
