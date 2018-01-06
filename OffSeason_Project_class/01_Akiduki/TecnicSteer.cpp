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
	
	_wheel.Set_angle_unit_place(WheelPlace::FRONT_RIGHT,	0, AD_NUM_0);
	_wheel.Set_angle_unit_place(WheelPlace::BACK_RIGHT,	1, AD_NUM_1);
	_wheel.Set_angle_unit_place(WheelPlace::BACK_LEFT,	2, AD_NUM_2);
	_wheel.Set_angle_unit_place(WheelPlace::FRONT_LEFT,	3, AD_NUM_3);
	
	_wheel.Set_wheel_place(WheelPlace::FRONT_RIGHT,	4);
	_wheel.Set_wheel_place(WheelPlace::BACK_RIGHT,	5);
	_wheel.Set_wheel_place(WheelPlace::BACK_LEFT,	6);
	_wheel.Set_wheel_place(WheelPlace::FRONT_LEFT,	7);
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
		if (_controller.Get_Triangle())	_wheel.Move_angle_motor(WheelPlace::FRONT_RIGHT, SIGNAL_FORWARD, 8);
		if (_controller.Get_Circle())	_wheel.Move_angle_motor(WheelPlace::FRONT_LEFT,	 SIGNAL_FORWARD, 8);
		if (_controller.Get_Square())	_wheel.Move_angle_motor(WheelPlace::BACK_RIGHT,	 SIGNAL_FORWARD, 8);
		if (_controller.Get_Cross())	_wheel.Move_angle_motor(WheelPlace::BACK_LEFT,	 SIGNAL_FORWARD, 8);
	}
	else if (_controller.Get_R_stick_y() == Direction::UNDER)
	{
		if (_controller.Get_Triangle())	_wheel.Move_angle_motor(WheelPlace::FRONT_RIGHT, SIGNAL_REVERSE, 8);
		if (_controller.Get_Circle())	_wheel.Move_angle_motor(WheelPlace::FRONT_LEFT,	 SIGNAL_REVERSE, 8);
		if (_controller.Get_Square())	_wheel.Move_angle_motor(WheelPlace::BACK_RIGHT,	 SIGNAL_REVERSE, 8);
		if (_controller.Get_Cross())	_wheel.Move_angle_motor(WheelPlace::BACK_LEFT,	 SIGNAL_REVERSE, 8);
	}
	else
	{
		_wheel.Record_pwm(8);
		
		switch (_controller.Get_L_stick_y())
		{
			case Direction::OVER:
			{
				switch (_controller.Get_L_stick_x())
				{
					case Direction::RIGHT:		_wheel.Move(+45);	break;
					case Direction::LEFT:		_wheel.Move(-45);	break;
					case Direction::xCENTER:	_wheel.Move(  0);	break;
				}
				
				break;
			}
			case Direction::UNDER:
			{
				switch (_controller.Get_L_stick_x())
				{
					case Direction::RIGHT:		_wheel.Move(+135);	break;
					case Direction::LEFT:		_wheel.Move(-135);	break;
					case Direction::xCENTER:	_wheel.Move( 180);	break;
				}
				
				break;
			}
			case Direction::yCENTER:
			{
				switch (_controller.Get_L_stick_x())
				{
					case Direction::RIGHT:		_wheel.Move(+90);	break;
					case Direction::LEFT:		_wheel.Move(-90);	break;
					case Direction::xCENTER:	_wheel.Stop();		break;
				}
				
				break;
			}
		}
	}
}

//----------------------------------------------------------------------//

void Main::Output()
{
	_wheel.Write();
	
	_wheel.Dispaly_ad_data(0x00);
	
	_wheel.Dispaly_current_angle(0x40);
	
//	_wheel.Dispaly_target_angle(0x40);
	
//	_wheel.Display_angle_motor_power(0x40);
	
//	_controller.Display(0x40);
}

//----------------------------------------------------------------------//

/************************************************************************/

}
}
}

/************************************************************************/
