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

//----------------------------------------------------------------------//

Main::Main()

	: _wheel(Uart::NUM_1)
	, _controller(Uart::NUM_0)
{
	LCD::Initialize();
	
	_wheel.Set_wheel_unit_place(WheelPlace::FRONT_RIGHT, 4, 0, AD_NUM_0);
	_wheel.Set_wheel_unit_place(WheelPlace::BACK_RIGHT,	 7, 3, AD_NUM_3);
	_wheel.Set_wheel_unit_place(WheelPlace::BACK_LEFT,	 6, 2, AD_NUM_2);
	_wheel.Set_wheel_unit_place(WheelPlace::FRONT_LEFT,	 5, 1, AD_NUM_1);
}

//----------------------------------------------------------------------//

void Main::Input()
{
	_wheel.Read();
	
	_controller.Read();
}

//----------------------------------------------------------------------//

void Main::Process()
{
	if (_controller.Get_R_stick_y() == Direction::OVER)
	{
		_wheel.Stop();
		
		if (_controller.Get_Triangle())	_wheel.Drive_angle_motor(WheelPlace::FRONT_RIGHT,	SIGNAL_FORWARD, 8);
		if (_controller.Get_Circle())	_wheel.Drive_angle_motor(WheelPlace::FRONT_LEFT,	SIGNAL_FORWARD, 8);
		if (_controller.Get_Square())	_wheel.Drive_angle_motor(WheelPlace::BACK_RIGHT,	SIGNAL_FORWARD, 8);
		if (_controller.Get_Cross())	_wheel.Drive_angle_motor(WheelPlace::BACK_LEFT,	SIGNAL_FORWARD, 8);
	}
	else if (_controller.Get_R_stick_y() == Direction::UNDER)
	{
		_wheel.Stop();
		
		if (_controller.Get_Triangle())	_wheel.Drive_angle_motor(WheelPlace::FRONT_RIGHT,	SIGNAL_REVERSE, 8);
		if (_controller.Get_Circle())	_wheel.Drive_angle_motor(WheelPlace::FRONT_LEFT,	SIGNAL_REVERSE, 8);
		if (_controller.Get_Square())	_wheel.Drive_angle_motor(WheelPlace::BACK_RIGHT,	SIGNAL_REVERSE, 8);
		if (_controller.Get_Cross())	_wheel.Drive_angle_motor(WheelPlace::BACK_LEFT,	SIGNAL_REVERSE, 8);
	}
	else
	{
		_wheel.Set_move_direction(_controller.Get_L_stick_x(), _controller.Get_L_stick_y());
		_wheel.Set_turn_direction(_controller.Get_R1(), _controller.Get_L1());
		
		_wheel.Set(10);
		
		_wheel.Move();
	}
}

//----------------------------------------------------------------------//

void Main::Output()
{
	_wheel.Write();
	
//	_wheel.Dispaly_ad_data(0x00);
	
	_wheel.Dispaly_current_angle(0x00);
	
	_wheel.Dispaly_target_angle(0x40);
	
//	_wheel.Display_angle_motor_power(0x40);
	
//	_controller.Display(0x40);
}

//----------------------------------------------------------------------//

/************************************************************************/

}
}
}

/************************************************************************/
