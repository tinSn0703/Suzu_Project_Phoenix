
#include <MainCircit/MainCircit.h>

#include "Project_14.h"

/************************************************************************/

namespace Gerbera
{

namespace BanriFinal
{

/************************************************************************/

#define INIT_LED()	DDRA = 0xff; PORTA = 0x00

#define PORT_LED	PORTA

#define LED_STATE_LOCK		0x00
#define LED_STATE_UNLOCK	0x0f

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	: _controller(Uart::NUM_0)
	
	, _wheel(Uart::NUM_1)
	
	, _pack_man(4, Uart::NUM_1)
	
	, _motor_tentacles(5, _wheel.Get_uart_num())
	
	, _uart_valve(Uart::NUM_3)
	, _valve_rod(VALVE::NUM_0)
{
	LCD::Initialize();
	
	INIT_LED();
	
	_wheel.Want_to_use_steps(YES);
	
	_wheel.Set_wheel_place(FourOmuni::FRONT_RIGHT,	1);
	_wheel.Set_wheel_place(FourOmuni::BACK_RIGHT,	3);
	_wheel.Set_wheel_place(FourOmuni::BACK_LEFT,	2);
	_wheel.Set_wheel_place(FourOmuni::FRONT_LEFT,	0);
	
	_wheel.Move_front(90);
	
	_wheel.Record_pwm(31);
	
	_motor_tentacles.Want_to_use_steps(YES);
	
	_motor_tentacles.Set(24);
	
	_timer_pack_man_stand = TIMER_INITAL_VALUE;
	
	_is_movement_lock = YES;
	
	_is_remove_tentacles = NO;
	
	LCD::Write(0x00, " 520 Banri Final");
	LCD::Write(0x40, " Machine Booting");
}

//----------------------------------------------------------------------//

void Main :: Input()
{
	_controller.Read();
	
	_pack_man.Read();
	
	if (_controller.Get_SELECT() || (_controller.Get_error_state() == READ_FAILURE))
	{
		_is_remove_tentacles = NO;
		
		_timer_pack_man_stand = TIMER_INITAL_VALUE;
		
		_pack_man.Clear();
		
		_is_movement_lock = YES;
	}
	
	if (_controller.Get_START())
	{
		_is_movement_lock = NO;
	}
}

//----------------------------------------------------------------------//

void Main::Set_wheel_turn()
{
	if (_controller.Get_L())
	{
		_wheel.Want_to_turn_left(YES);
	}
	else
	{
		_wheel.Want_to_turn_left(NO);
	}
	
	if (_controller.Get_R())
	{
		_wheel.Want_to_turn_right(YES);
	}
	else
	{
		_wheel.Want_to_turn_right(NO);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_right()
{
	if (_controller[MOVE_FRONT])
	{
		_wheel.Curve(PERSENT_CURVE, 45);
	}
	else if (_controller[MOVE_BACK])
	{
		_wheel.Curve(PERSENT_CURVE, 135);
	}
	else
	{
		_wheel.Curve(PERSENT_CURVE, 90);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_left()
{
	if (_controller[MOVE_FRONT])
	{
		_wheel.Curve(PERSENT_CURVE, 315);
	}
	else if (_controller[MOVE_BACK])
	{
		_wheel.Curve(PERSENT_CURVE, 225);
	}
	else
	{
		_wheel.Curve(PERSENT_CURVE, 270);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_front()
{
	if (_controller[MOVE_RIGHT])
	{
		_wheel.Curve(PERSENT_CURVE, 45);
	}
	else if (_controller[MOVE_LEFT])
	{
		_wheel.Curve(PERSENT_CURVE, 315);
	}
	else
	{
		_wheel.Curve(PERSENT_CURVE, 0);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_back()
{
	if (_controller[MOVE_RIGHT])
	{
		_wheel.Curve(PERSENT_CURVE, 135);
	}
	else if (_controller[MOVE_LEFT])
	{
		_wheel.Curve(PERSENT_CURVE, 225);
	}
	else
	{
		_wheel.Curve(PERSENT_CURVE, 180);
	}
}

//----------------------------------------------------------------------//

void Main :: Move_wheel()
{
	Set_wheel_turn();
	
	if (_controller[MOVE_FRONT])
	{
		Move_wheel_front();
	}
	else if (_controller[MOVE_BACK])
	{
		Move_wheel_back();
	}
	else if (_controller[MOVE_RIGHT])
	{
		Move_wheel_right();
	}
	else if (_controller[MOVE_LEFT])
	{
		Move_wheel_left();
	}
	else
	{
		_wheel.SpinTurn();
	}
}

//----------------------------------------------------------------------//

void Main::Move_tentacles(const DirectionY _move)
{
	switch (_move)
	{
		case Direction::OVER:		_motor_tentacles.Set(SIGNAL_FORWARD);	break;
		case Direction::UNDER:		_motor_tentacles.Set(SIGNAL_REVERSE);	break;
		case Direction::yCENTER:	_motor_tentacles.Set(SIGNAL_BREAK);		break;
	}
}

//----------------------------------------------------------------------//

void Main::Move_tentacles_and_pack_man()
{
	if (_timer_pack_man_stand == TIMER_INITAL_VALUE)
	{
		Move_tentacles(_controller.Get_cross_key_y());
		
		if (_is_remove_tentacles)
		{
			_pack_man.Set_stand_over(_controller.Get_ZL());
			_pack_man.Set_stand_under(_controller.Get_ZR());
			
			_pack_man.Move_pack_man_arm(_controller.Get_L_stick_y());
		}
		else
		{
			if (_controller.Get_ZL())
			{
				_timer_pack_man_stand = Timer::General::Set_counter(200);
				
				Move_tentacles(Direction::UNDER);
			}
		}
	}
	else
	{
		if (Timer::General::Is_current_bigger_than(_timer_pack_man_stand))
		{
			if (_is_remove_tentacles == NO)
			{
				Move_tentacles(Direction::yCENTER);
				
				_pack_man.Set_stand_over(YES);
				
				_is_remove_tentacles = YES;
				
				_timer_pack_man_stand = TIMER_INITAL_VALUE;
			}
		}
	}
	
	_pack_man.Move_stand();
}

//----------------------------------------------------------------------//

void Main::Move_valve()
{
	_valve_rod.Open_and_Close(_controller.Get_cross_key(Direction::RIGHT), 1000);
}

//----------------------------------------------------------------------//

void Main :: Process()
{
	if (_is_movement_lock == NO)
	{
		Move_wheel();
		
		Move_tentacles_and_pack_man();
		
		Move_valve();
	}
}

//----------------------------------------------------------------------//

void Main :: Output()
{
	if (_is_movement_lock)
	{
		if (PORT_LED == LED_STATE_UNLOCK)
		{
			LCD::Write(0x40, "       Lock Mode");
			
			PORT_LED = LED_STATE_LOCK;
		}
		
		_wheel.Write_clear();
		
		_motor_tentacles.Write_clear();
		
		_pack_man.Write_clear();
	}
	else
	{
		if (PORT_LED == LED_STATE_LOCK)
		{
			LCD::Clear_under();
			
			PORT_LED = LED_STATE_UNLOCK;
		}
		
		_uart_valve.Transmit_8bit(_valve_rod.Get_data());
		
		_wheel.Write();
		
		_motor_tentacles.Write();
		
		_pack_man.Write();
		
		_pack_man.Display_sensor_arm_stretch(0x40);
		
		_pack_man.Display_sensor_arm_shorten(0x45);
		
		_pack_man.Display_motor_arm(0x4a);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}
}

/************************************************************************/
