
#include <MainCircit/MainCircit.h>

#include "Project4.h"

/************************************************************************/

namespace Project4
{

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	: _controller(UART_NUM_0)
	, _wheel(0, UART_NUM_1)
	, _valve(UART_NUM_2)

{
	_mem_is_movement_enabled = NO;
	
	_mem_timer = 0;
	
	_wheel.Set_wheel_place(Four::FRONT_LEFT	,0);
	_wheel.Set_wheel_place(Four::BACK_LEFT	,1);
	_wheel.Set_wheel_place(Four::FRONT_RIGHT	,2);
	_wheel.Set_wheel_place(Four::BACK_RIGHT	,3);
	
	_wheel.Set(31);
	
	_wheel.Want_to_use_steps(YES);
	
	_valve.Want_to_open_1(YES);
	
	LCD_Init();
	
	LCD_Write_str(0x00, "Suzu Project4");
	LCD_Write_str(0x40, "Lock");
	
	GeneralTimer::Initialize();
}

//----------------------------------------------------------------------//

void Main :: Receive_operation()
{
	_controller.Receive();
	
	if (_controller.Get_START())
	{
		LCD_Clear_un();
		
		_mem_is_movement_enabled = YES;	
	}
	if (_controller.Get_SELECT())
	{
		LCD_Write_str(0x40, "Lock             ");
		
		_mem_is_movement_enabled = NO;
	}
}

//----------------------------------------------------------------------//

void Main :: Operate()
{
//	if (_mem_timer == 0)
//	{
		_wheel.Set_direc(_controller.Get_cross_y());
		_wheel.Set_turn(_controller.Get_R1(), _controller.Get_L1());
//	}
//	else
//	{
//		_wheel.Set_direc(NORTH);
//		_wheel.Set_turn(NO, NO);
//	}
}

//----------------------------------------------------------------------//

void Main :: Move_valve()
{
	if ((_controller.Push_L3()) && (_mem_timer == 0))
	{
		_mem_timer = GeneralTimer::Read();
		
		_valve.Want_to_open_1(NO);
		_valve.Want_to_open_2(YES);
	}
	
	if (GeneralTimer::Change_ms(GeneralTimer::Read() - _mem_timer) > 1300)
	{
		_valve.Want_to_open_1(YES);
		
		_mem_timer = 0;
	}
	else if (GeneralTimer::Change_ms(GeneralTimer::Read() - _mem_timer) > 650)
	{
		_valve.Want_to_open_0(NO);
		_valve.Want_to_open_2(NO);
	}
	else if (GeneralTimer::Change_ms(GeneralTimer::Read() - _mem_timer) > 150)
	{
		_valve.Want_to_open_0(YES);
	}
}

//----------------------------------------------------------------------//

void Main :: Move_wheel()
{
	if (_controller.Push_Tri())	_wheel ++;
	if (_controller.Push_Cro())	_wheel --;
		
	if (_wheel.Is_turn_l() | _wheel.Is_turn_r())
	{
		_wheel.Turning();
	}
	else
	{
		_wheel.Move_front_or_back();
	}
}

//----------------------------------------------------------------------//

void Main :: Work()
{
	Operate();
	
	Move_valve();
	
	Move_wheel();
	
	_valve.Transmit();
	_wheel.Transmit();
}

//----------------------------------------------------------------------//

void Main :: Stop()
{
	_wheel.Transmit_clear();
}

//----------------------------------------------------------------------//

void Main :: Display()
{
	if (_wheel.Is_turn_l())
	{
		LCD::Write(0x40, "lTurn");
	}
	else if (_wheel.Is_turn_r())
	{
		LCD::Write(0x40, "rTurn");
	}
	else
	{
		LCD::Write(0x40, "  ,  ");
		LCD::Write(0x41, _wheel.Get_direc_x(), 1, DECIMAL_10);
		LCD::Write(0x43, _wheel.Get_direc_y(), 1, DECIMAL_10);
	}
		
	LCD::Write(0x46, _wheel.Get_pwm(), 2, DECIMAL_10);
	
	_valve.Display(0x48, DECIMAL_02);
	
	LCD::Write(0x48, "   ");
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/