
#include <math.h>

#include <MainCircit/MainCircit.h>

#include "Project8.h"

/************************************************************************/

namespace Physalis
{

namespace Kerberos_chan
{

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	: _controller(Uart::NUM_0)
	
	, _wheel(Uart::NUM_1, 2, 0, 1)
	
	, _uart_valve(Uart::NUM_2)
	, _valve_catapult_trigger(VALVE::NUM_0)
	, _valve_gun_trigger_Veni(VALVE::NUM_1)
	, _valve_gun_trigger_Vidi(VALVE::NUM_2)
	, _valve_gun_trigger_Vici(VALVE::NUM_3)
{
	Display_init();
	
	_is_movement_lock = YES;
	
	_wheel.Record_pwm(15);
}

//----------------------------------------------------------------------//

void Main :: Display_init()
{
	LCD::Write(0x00, "200     Physalis", 75);
	LCD::Write(0x40, "   Kerberos-chan");
}

//----------------------------------------------------------------------//

void Main :: Receive_operation()
{
	_controller.Read();
	
	if (_controller.Get_SELECT() || (_controller.Get_error_state() == READ_FAILURE))
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
		LCD::Clear_under();
		
		_is_movement_lock = NO;
	}
}

//----------------------------------------------------------------------//

YesNo Main :: Is_movement_lock()
{
	return _is_movement_lock;
}

//----------------------------------------------------------------------//

void Main :: Control_fire()
{
	_valve_catapult_trigger.Open_or_Close(_controller.Get_Cross());
	_valve_gun_trigger_Veni.Open_or_Close(_controller.Get_Circle());
	_valve_gun_trigger_Vidi.Open_or_Close(_controller.Get_Triangle());
	_valve_gun_trigger_Vici.Open_or_Close(_controller.Get_Square());
}

//----------------------------------------------------------------------//

void Main :: Move()
{
	_wheel.Set_move_direction(_controller.Get_L_stick_x(), _controller.Get_L_stick_y());
	
	_wheel.Set_turn_direction
	(
		_controller.Get_L1() | _controller.Get_L2(),
		_controller.Get_R1() | _controller.Get_R2()
	);
	
	if (_controller.Push_R3())	_wheel ++;
	if (_controller.Push_L3())	_wheel --;
	
	if (_wheel.Is_move())
	{
		_wheel.Curve(75);
	}
	else
	{
		if	(
				(_controller.Get_L1() & _controller.Get_L2()) |
				(_controller.Get_R1() & _controller.Get_R2())
			)
		{
			_wheel.SpinTurn();
		}
		else if (_controller.Get_L1() | _controller.Get_L2())
		{
			_wheel.PivotTurn(WheelPlace::RIGHT, _controller.Get_L2(), _controller.Get_L1());
		}
		else if (_controller.Get_R1() | _controller.Get_R2())
		{
			_wheel.PivotTurn(WheelPlace::LEFT , _controller.Get_R1(), _controller.Get_R2());
		}
		else
		{
			_wheel.Stop();
		}
	}
}

//----------------------------------------------------------------------//

void Main :: Work()
{
	Control_fire();
	
	Move();
	
	_wheel.Write();
	
	_uart_valve.Transmit_8bit
	(
		_valve_catapult_trigger.Get_data() |
		_valve_gun_trigger_Veni.Get_data() |
		_valve_gun_trigger_Vidi.Get_data() |
		_valve_gun_trigger_Vici.Get_data()
	);
}

//----------------------------------------------------------------------//

void Main :: Stop()
{
	_wheel.Write_clear();
}

//----------------------------------------------------------------------//

void Main :: Display()
{
	if (_valve_gun_trigger_Veni.Is_open())
	{
		LCD::Write(0x40, "Veni ");
	}
	else
	{
		LCD::Write(0x40, "     ");
	}
	
	if (_valve_gun_trigger_Vidi.Is_open())
	{
		LCD::Write(0x45, "vidi ");
	}
	else
	{
		LCD::Write(0x40, "     ");
	}
	
	if (_valve_gun_trigger_Vici.Is_open())
	{
		LCD::Write(0x4a, "vici ");
	}
	else
	{
		LCD::Write(0x40, "     ");
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}

}

/************************************************************************/
