/*
 * TecnicSteer.cpp
 *
 * Created: 2017/12/21 12:27:52
 *  Author: conde_000
 */ 

#include "TecnicSteer.h"

/************************************************************************/

namespace Off2017
{
namespace Akiduki
{
namespace TecnicSteer
{

/************************************************************************/

#define INIT_LED()	DDRA = 0xff; PORTA = 0x00

#define PORT_LED	PORTA

#define LED_STATE_LOCK		0x00
#define LED_STATE_UNLOCK	0x0f

/************************************************************************/

//----------------------------------------------------------------------//

Main::Main()

	: _wheel(Uart::NUM_1)
	, _controller(Uart::NUM_0)
{
	INIT_LED();
	
	LCD::Initialize();
	
	_wheel.Set_wheel_unit_place(WheelPlace::FRONT_RIGHT, 4, 0, AD_NUM_0);
	_wheel.Set_wheel_unit_place(WheelPlace::BACK_RIGHT,	 7, 3, AD_NUM_3);
	_wheel.Set_wheel_unit_place(WheelPlace::BACK_LEFT,	 6, 2, AD_NUM_2);
	_wheel.Set_wheel_unit_place(WheelPlace::FRONT_LEFT,	 5, 1, AD_NUM_1);
	
	_wheel.Set(5);
	
	_is_unlock = NO;
}

//----------------------------------------------------------------------//

void Main::Input()
{
	_wheel.Read();
	
	_controller.Read();
	
	if (_controller.Get_SELECT())
	{
		_is_unlock = NO;
	}
	
	if (_controller.Get_START())
	{
		LCD::Initialize();
		
		_is_unlock = YES;
	}
	
	_wheel.Set_move_direction(_controller.Get_L_stick_x(), _controller.Get_L_stick_y());
	
	_wheel.Set_turn_direction(_controller.Get_R1(), _controller.Get_L1());
}

//----------------------------------------------------------------------//

void Main::Process()
{
	if (_is_unlock)
	{
		if (_wheel.Is_move())
		{
			_wheel.Curve(_controller.Get_R2(), _controller.Get_L2(), 25);
		}
		else
		{
			_wheel.SpinTurn();
		}
	}
}

//----------------------------------------------------------------------//

void Main::Output()
{
	if (_is_unlock)
	{
		if (PORT_LED == LED_STATE_LOCK)
		{
			PORT_LED = LED_STATE_UNLOCK;
		}
		
		_wheel.Write();
	}
	else
	{
		if (PORT_LED == LED_STATE_UNLOCK)
		{
			PORT_LED = LED_STATE_LOCK;
		}
		
		_wheel.Write_clear();
	}
	
	_wheel.Dispaly_current_angle(0x00);
	
	_wheel.Dispaly_target_angle(0x40);
}

//----------------------------------------------------------------------//

/************************************************************************/

}
}
}

/************************************************************************/
