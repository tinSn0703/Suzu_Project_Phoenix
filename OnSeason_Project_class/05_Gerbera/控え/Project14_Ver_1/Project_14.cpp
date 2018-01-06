
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
	, _motor_tentacles(5, _wheel.Get_uart_num())
	, _motor_pack_man_stand(4, _wheel.Get_uart_num())
	
	, _uart_valve(Uart::NUM_3)
	, _valve_rod(VALVE::NUM_0)
	
	, _limit_stand_over(IO::NUM_F, IO::BIT_3)
	, _limit_stand_under(IO::NUM_F, IO::BIT_2)
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
	
	_motor_pack_man_arm[LEFT_OVER	].Reset(IO::NUM_E, IO::BIT_3, IO::BIT_2);
	_motor_pack_man_arm[LEFT_UNDER	].Reset(IO::NUM_E, IO::BIT_5, IO::BIT_4);
	_motor_pack_man_arm[RIGHT_OVER	].Reset(IO::NUM_E, IO::BIT_7, IO::BIT_6);
	_motor_pack_man_arm[RIGHT_UNDER	].Reset(IO::NUM_F, IO::BIT_1, IO::BIT_0);
	
	_limit_arm_stretch[LEFT_OVER	].Reset(IO::NUM_F, IO::BIT_4);
	_limit_arm_stretch[LEFT_UNDER	].Reset(IO::NUM_F, IO::BIT_5);
	_limit_arm_stretch[RIGHT_OVER	].Reset(IO::NUM_F, IO::BIT_6);
	_limit_arm_stretch[RIGHT_UNDER	].Reset(IO::NUM_F, IO::BIT_7);

	_limit_arm_shorten[LEFT_OVER	].Reset(IO::NUM_E, IO::BIT_0);
	_limit_arm_shorten[LEFT_UNDER	].Reset(IO::NUM_E, IO::BIT_1);
	_limit_arm_shorten[RIGHT_OVER	].Reset(IO::NUM_E, IO::BIT_2);
	_limit_arm_shorten[RIGHT_UNDER	].Reset(IO::NUM_E, IO::BIT_3);
	
	_motor_tentacles.Want_to_use_steps(YES);
	_motor_pack_man_stand.Want_to_use_steps(YES);
	
	_motor_tentacles.Set(24);
	
	_timer_pack_man_stand = TIMER_INITAL_VALUE;
	
	_is_movement_lock = YES;
	
	_is_stand_move_over  = NO;
	_is_stand_move_under = NO;
	
	_is_remove_tentacles = NO;
	
	LCD::Write(0x00, "520 Banri Final ");
	LCD::Write(0x40, "Take it easy    ");
}

//----------------------------------------------------------------------//

void Main :: Input()
{
	_controller.Read();
	
	_limit_stand_over.Read();
	_limit_stand_under.Read();
	
	for (uByte i = 0; i < 4; i++)
	{
		_limit_arm_stretch[i].Read();
		_limit_arm_shorten[i].Read();
	}
	
	if (_controller.Get_SELECT() || (_controller.Get_error_state() == READ_FAILURE))
	{
		_is_remove_tentacles = NO;
		
		_timer_pack_man_stand = TIMER_INITAL_VALUE;
		
		_is_stand_move_over		= NO;
		_is_stand_move_under	= NO;
		
		_motor_pack_man_stand.Set(SIGNAL_BREAK);
		
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

void Main :: Move_pack_man_arm(const YesNo _is_stretch, const YesNo _is_shorten)
{
	if (_is_stretch)
	{
		for (uByte i = 0; i < 4; i++)
		{
			_motor_pack_man_arm[i].Set(SIGNAL_FORWARD);
		}
	}
	else if (_is_shorten)
	{
		for (uByte i = 0; i < 4; i++)
		{
			_motor_pack_man_arm[i].Set(SIGNAL_REVERSE);
		}
	}
	else
	{
		for (uByte i = 0; i < 4; i++)	_motor_pack_man_arm[i].Set(SIGNAL_FREE);
	}
}

//----------------------------------------------------------------------//

void Main :: Move_pack_man_arm(const DirectionY _move)
{
	switch (_move)
	{
		case Direction::OVER:
		{
			for (uByte i = 0; i < 4; i++)
			{
				if (_limit_arm_stretch[i].Get())
				{
					_motor_pack_man_arm[i].Set(SIGNAL_FORWARD);
				}
				else
				{
					_motor_pack_man_arm[i].Set(SIGNAL_FREE);
				}
			}
			
			break;
		}
		case Direction::UNDER:
		{
			for (uByte i = 0; i < 4; i++)
			{
				if (_limit_arm_shorten[i].Get())
				{
					_motor_pack_man_arm[i].Set(SIGNAL_REVERSE);
				}
				else
				{
					_motor_pack_man_arm[i].Set(SIGNAL_FREE);
				}
			}
			
			break;
		}
		case Direction::xCENTER:
		{
			for (uByte i = 0; i < 4; i++)	_motor_pack_man_arm[i].Set(SIGNAL_FREE);
			
			break;
		}
	}
}

//----------------------------------------------------------------------//

void Main::Move_pack_man_stand()
{
	if (_is_stand_move_over)
	{
		if (_limit_stand_over.Get())
		{
			_motor_pack_man_stand.Set(SIGNAL_FORWARD, PWM_PACK_MAN_OVER);
		}
		else
		{
			_motor_pack_man_stand.Set(SIGNAL_BREAK);
			
			_is_stand_move_over = NO;
		}
	}
	else if (_is_stand_move_under)
	{
		if (_limit_stand_under.Get())
		{
			_motor_pack_man_stand.Set(SIGNAL_REVERSE, PWM_PACK_MAN_UNDER);
		}
		else
		{
			_motor_pack_man_stand.Set(SIGNAL_BREAK);
			
			_is_stand_move_under = NO;
		}
	}
	else
	{
		_motor_pack_man_stand.Set(SIGNAL_BREAK);
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
			if (_controller.Get_ZL() & ~_is_stand_move_over)
			{
				_is_stand_move_over		= YES;
				_is_stand_move_under	= NO;
			}
			
			if (_controller.Get_ZR() & ~_is_stand_move_under)
			{
				_is_stand_move_over		= NO;
				_is_stand_move_under	= YES;
			}
			
			Move_pack_man_arm(_controller.Get_L_stick_y());
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
				
				_is_stand_move_over = YES;
				
				_is_remove_tentacles = YES;
				
				_timer_pack_man_stand = TIMER_INITAL_VALUE;
			}
		}
	}
	
	Move_pack_man_stand();
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
			LCD::Write(0x40, "Lock Mode       ");
			
			PORT_LED = LED_STATE_LOCK;
		}
		
		_wheel.Write_clear();
		
		_motor_tentacles.Write_clear();
		
		_motor_pack_man_stand.Write_clear();
		
		for (uByte i = 0; i < 4; i++)
		{
			_motor_pack_man_arm[i].Write_clear();
		}
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
		
		_motor_pack_man_stand.Write();
		
		for (uByte i = 0; i < 4; i++)
		{
			_motor_pack_man_arm[i].Write();
		}
		
		_wheel.Display_power(0x40);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}
}

/************************************************************************/
