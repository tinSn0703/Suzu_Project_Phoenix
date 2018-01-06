
#include <MainCircit/MainCircit.h>

#include "Project5.h"

/************************************************************************/

namespace Project5
{

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	: _controller(UART_NUM_0)
	, _wheel(0, UART_NUM_1)
	, _motor_stand(3, _wheel.Get_uart())
	, _uart_valve(UART_NUM_2)
{
	_motor_stand.Want_to_use_steps(YES);
	_motor_stand = 31;
	
	_wheel.Want_to_use_steps(YES);
	_wheel.Set(15);
	
	_valve[0].Reset(NUM_VALVE_0);
	_valve[1].Reset(NUM_VALVE_1);
	_valve[2].Reset(NUM_VALVE_2);
	_valve[3].Reset(NUM_VALVE_3);
	
	_mem_is_movement_enabled = NO;
	
	_mem_timer = 0;
	
	GeneralTimer::Initialize();
	
	LCD::Write(0x00, "Suzu Project 5");
}

//----------------------------------------------------------------------//

void Main :: Receive_operation()
{
	_controller.Receive();
	
	if (_controller.Push_SELECT())	_mem_is_movement_enabled = NO;
	if (_controller.Push_START())	_mem_is_movement_enabled = YES;
}

//----------------------------------------------------------------------//

YesNo Main :: Is_movement_enabled()
{
	return _mem_is_movement_enabled;
}

//----------------------------------------------------------------------//

void Main :: Work()
{
	_wheel.Set_direc(_controller.Get_cross_x(), _controller.Get_cross_y());
	_wheel.Set_turn(_controller.Get_L1(), _controller.Get_R1());
	
	if (_controller.Push_Tri())	_wheel ++;
	if (_controller.Push_Cro())	_wheel --;
	
	if (_wheel.Is_turn_l() | _wheel.Is_turn_r())
	{
		_wheel.Turning();
	}
	else
	{
		_wheel.Move();
	}
	
	switch (_controller.Get_stick_Ly())
	{
		case NORTH:		_motor_stand = SIGNAL_FORWARD;	break;
		case SOUTH:		_motor_stand = SIGNAL_REVERSE;	break;
		case CENTER_Y:	_motor_stand = SIGNAL_BREAK;	break;
	}
	
	if (_controller.Push_Cir())
	{
		for (uByte i = 0; i < 4; i++)	_valve[i].Want_to_open(YES);
		
		_mem_timer = GeneralTimer::Set_counter(300);
	}
	
	if (GeneralTimer::Is_current_bigger_than(_mem_timer))
	{
		for (uByte i = 0; i < 4; i++)	_valve[i].Want_to_open(NO);
	}
	
	_wheel.Transmit();
	
	_motor_stand.Transmit();
	
	const UartData8bit _transmit_data =
		_valve[0].Get_data() | 
		_valve[1].Get_data() | 
		_valve[2].Get_data() | 
		_valve[3].Get_data() ;
	
	_uart_valve.Transmit_8bit(_transmit_data);
}

//----------------------------------------------------------------------//

void Main :: Stop()
{
	_wheel.Transmit_clear();
	
	_motor_stand.Transmit_clear();
}

//----------------------------------------------------------------------//

void Main :: Display()
{
	
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
