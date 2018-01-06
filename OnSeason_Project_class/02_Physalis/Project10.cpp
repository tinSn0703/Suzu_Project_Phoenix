
#include <math.h>

#include <MainCircit/MainCircit.h>

#include "Project10.h"

/************************************************************************/

namespace Physalis
{

namespace Otegine
{

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	: _controller(Uart::NUM_0)
	
	, _wheel(Uart::NUM_1, 1, 2, 3, 0)
	
	, _uart_valve(Uart::NUM_2)
	, _valve_rod(VALVE::NUM_4)
{
	_is_movement_lock = YES;
	
	_wheel.Record_pwm(15);
	
	LCD::Write(0x00, "220     Physalis", 75);
	LCD::Write(0x40, "         Otegine");
}

//----------------------------------------------------------------------//

void Main :: Input()
{
	_controller.Read();
}

//----------------------------------------------------------------------//

void Main :: Process()
{
	if (_controller.Push_SELECT())
	{
		if (_controller.Get_START())
		{
			LCD::Initialize();
			
			LCD::Write(0x00, "220     Physalis", 75);
		}
		
		LCD::Write(0x40, "Lock Mode       ");
		
		_is_movement_lock = YES;
	}
	else if (_controller.Push_START())
	{
		LCD::Clear_under();
		
		_is_movement_lock = NO;
	}
	
	if (_is_movement_lock == NO)
	{
		_wheel.Set_move_direction(_controller.Get_L_stick_x(), Reversal(_controller.Get_L_stick_y()));
		
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
			if (
			(_controller.Get_L1() & _controller.Get_L2()) |
			(_controller.Get_R1() & _controller.Get_R2())
			)
			{
				_wheel.SpinTurn();
			}
			else if (_controller.Get_L1() | _controller.Get_L2())
			{
				_wheel.PivotTurn(WheelPlace::FRONT_RIGHT, _controller.Get_L2(), _controller.Get_L1());
			}
			else if (_controller.Get_R1() | _controller.Get_R2())
			{
				_wheel.PivotTurn(WheelPlace::FRONT_LEFT , _controller.Get_R1(), _controller.Get_R2());
			}
			else
			{
				_wheel.Stop();
			}
		}
		
		_valve_rod.Open_and_Close(_controller.Get_Circle(), 450); //’Þ‚èŠÆ
	}
}

//----------------------------------------------------------------------//

void Main :: Output()
{
	if (_is_movement_lock)
	{
		_wheel.Write_clear();
	}
	else
	{
		_wheel.Write();
		
		_uart_valve.Transmit_8bit(_valve_rod.Get_data());
		
		_wheel.Display_power(0x40);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}

}

/************************************************************************/
