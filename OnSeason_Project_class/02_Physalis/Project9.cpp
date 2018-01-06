
#include <MainCircit/MainCircit.h>

#include "Project9.h"

/************************************************************************/

namespace Physalis
{

namespace OneWayTicket
{

/************************************************************************/

Main :: Main()

	: _controller(Uart::NUM_0)
	
	, _uart_motor(Uart::NUM_1)
	, _motor_widch(0)
	, _motor_turn(1)
	
	,_uart_valve(Uart::NUM_2)
	, _valve_stopper(VALVE::NUM_0)
	, _valve_trigger(VALVE::NUM_1)
	
	, _check_enemy_line(IO::NUM_F, IO::BIT_0)
{
	Display_init();
	
	_is_movement_lock = YES;
	
	_is_lcd_change = YES;
	
	_motor_widch.Set_steps(STEPS_USE);
	
	_motor_widch = 15;
	
	_motor_turn.Set_steps(STEPS_USE);
	
	_motor_turn = 15;
	
	_past_valve_data = 0x00;
	
	_uart_valve.Transmit_8bit(0x00);
}

/************************************************************************/

void Main :: Display_init()
{
	LCD::Write(0x00, "210     Physalis", 75);
	LCD::Write(0x40, "    OneWayTicket");
}

/************************************************************************/

void Main :: Receive_operation()
{
	_controller.Read();
	
	if (_controller.Get_SELECT() | _controller.Get_error_state())
	{
		if (_controller.Get_START())
		{
			LCD::Initialize();
			
			Display_init();
		}
		else
		{
			LCD::Write(0x40, "Lock Mode       ");
		}
		
		_is_movement_lock = YES;
	}
	else if (_controller.Get_START())
	{
		_is_lcd_change = YES;
		
		_is_movement_lock = NO;
	}
}

/************************************************************************/

YesNo Main :: Is_movement_enable()
{
	return _is_movement_lock;
}

/************************************************************************/

void Main :: Move_glide_mode()
{
	if (_controller.Get_L3() | _check_enemy_line.Read())
	{
		_valve_stopper.Want_to_open(YES);
	}
	
	if (_controller.Get_Circle() & ~_valve_trigger.Is_open())
	{
		_valve_stopper.Want_to_open(NO);
	}
}

/************************************************************************/

void Main :: Move_bombard_mode()
{
	if (_valve_stopper.Is_open())
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
		
		if (_controller.Get_R3())
		{
			_valve_trigger.Want_to_open(YES);
		}
		
		if (_controller.Get_Square())
		{
			_valve_trigger.Want_to_open(NO);
		}
	}
}

/************************************************************************/

void Main :: Work()
{
	Main::Move_glide_mode();
	
	Main::Move_bombard_mode();
	
	if (_valve_stopper.Is_open())
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
		_valve_trigger.Get_data()	|
		_valve_stopper.Get_data()
	);
	
	if (_transmit_data != _past_valve_data)
	{
		_uart_valve.Transmit_8bit(_transmit_data);
		
		_past_valve_data = _transmit_data;
	}
}

/************************************************************************/

void Main :: Display()
{
	if (_valve_stopper.Is_open())
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
