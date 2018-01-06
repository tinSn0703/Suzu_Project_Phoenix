
#include <math.h>

#include <MainCircit/MainCircit.h>

#include "Project6.h"

/************************************************************************/

namespace Zephyranthes
{

namespace Catapult
{

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	: _controller(Uart::NUM_0)
	, _wheel(Uart::NUM_1)
	, _catapult_lock(VALVE::NUM_0)
	, _uart_valve(Uart::NUM_3)
{
	DDRA  = 0xff;
	PORTA = 0x00;
	
	_wheel.Record_pwm(15);
	
	_catapult_lock.Want_to_open(NO);
	
	_is_movement_lock = YES;
	_is_catapult_enable = NO;
	
	_is_lcd_change = YES;
	
	LCD::Write(0x00, "110 Zephyranthes", 75);
	LCD::Write(0x40, "Name    Catepult");
}

//----------------------------------------------------------------------//

void Main :: Input()
{
	_controller.Read();
	
	if (_controller.Push_SELECT())
	{
		LCD::Write(0x40, "Lock Mode       ");
		
		_is_catapult_enable = NO;
		
		_is_movement_lock = YES;
	}
	if (_controller.Push_START())
	{
		PORTA = 0xff;
		
		LCD::Clear_under();
		
		_is_movement_lock = NO;
	}
}

//----------------------------------------------------------------------//

void Main :: Process()
{
	_wheel.Set_move_direction(_controller.Get_L_stick_x(), _controller.Get_L_stick_y());
	
	_wheel.Set_turn_direction
	(
		_controller.Get_L1() | _controller.Get_L2(), 
		_controller.Get_R1() | _controller.Get_R2()
	);
	
	if (_controller.Push_Triangle())	_wheel ++;
	if (_controller.Push_Cross())		_wheel --;
	
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
			_wheel.PivotTurn(WheelPlace::LEFT, _controller.Get_L1(), _controller.Get_L2());
		}
		else if (_controller.Get_R1() | _controller.Get_R2())
		{
			_wheel.PivotTurn(WheelPlace::RIGHT, _controller.Get_R1(), _controller.Get_R2());
		}
		else
		{
			_wheel.Stop();
		}
	}
	
	if (_controller.Push_Square() & ~_controller.Get_Circle())
	{
		_catapult_lock.Want_to_open(NO);
		
		_is_catapult_enable = Reversal(_is_catapult_enable);
	}
	
	if (_controller.Push_Circle() & ~_controller.Get_Square() & _is_catapult_enable)
	{
		_catapult_lock.Want_to_open(YES);
		
		_is_catapult_enable = NO;
	}
}

//----------------------------------------------------------------------//

void Main :: Output()
{
	_wheel.Write();
	
	_uart_valve.Transmit_8bit(_catapult_lock.Get_data());
}

//----------------------------------------------------------------------//

void Main :: Stop()
{
	_wheel.Write_clear();
}

//----------------------------------------------------------------------//

void Main :: Display()
{
	if (_is_catapult_enable)
	{
		if (_is_lcd_change == YES)
		{
			LCD::Write(0x00, "Release Safety  ");
			LCD::Write(0x40, "Are you okay?...", 75);
			
			_is_lcd_change = NO;
		}
	}
	else
	{
		if (_is_lcd_change == NO)
		{
			LCD::Write(0x00, "110 Zephyranthes");
			LCD::Clear_under();
			
			_is_lcd_change = YES;
		}
		
		_wheel.Display_power(0x40);
		
		LCD::Write(0x4f, _catapult_lock.Is_open(), 1, DECIMAL_02);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}

}

/************************************************************************/
