/* 
* AIG.cpp
*
* Created: 2017/12/19 16:29:02
* Author: conde_000
*/


#include "AIG_No_0.h"

/************************************************************************/

namespace Off2017
{

namespace Teruduki
{
	
namespace AIG_No_0
{

/************************************************************************/

#define INIT_LED()	DDRA = 0xff; PORTA = 0x00

#define PORT_LED	PORTA

#define LED_STATE_LOCK		0x00
#define LED_STATE_UNLOCK	0x0f

/************************************************************************/

//----------------------------------------------------------------------//

Main::Main()
	
	: _controller(Uart::NUM_0)
	
	, _wheel(Uart::NUM_1)
	
	, _limit_nock(IO::NUM_F, IO::BIT_0)
	
	, _uart_valve_1(Uart::NUM_3)
	, _valve_fall_feed_fall_zone(VALVE::NUM_3, VALVE::NUM_6)
	, _valve_fall_feed_wait_zone(VALVE::NUM_4, VALVE::NUM_5)
	
	, _uart_valve_2(Uart::NUM_2)
	, _valve_gun_trigger(VALVE::NUM_4, VALVE::NUM_3)
	, _valve_fall_support(VALVE::NUM_1, VALVE::NUM_2)
	, _valve_fall_stretch(VALVE::NUM_0)
{
	_timer_gun = TIMER_INITAL_VALUE;
	
	_is_movement_lock = YES;
	
	_valve_fall_feed_fall_zone.Set(NO, YES);
	_valve_fall_feed_wait_zone.Set(NO, YES);
	
	_wheel.Set_wheel_place(WheelPlace::FRONT_RIGHT,	1);
	_wheel.Set_wheel_place(WheelPlace::BACK_RIGHT,	0);
	_wheel.Set_wheel_place(WheelPlace::BACK_LEFT,	3);
	_wheel.Set_wheel_place(WheelPlace::FRONT_LEFT,	2);
	
	_wheel.Set(7);
	_wheel.Set_steps(STEPS_USE);
	
//	LCD::Initialize();
	
	INIT_LED();
	
//	LCD::Write(0x00, "Teruduki AIG 000");
//	LCD::Write(0x40, "Push Start      ");
}

//----------------------------------------------------------------------//

void Main::Input()
{
	_controller.Read();
	
	_limit_nock.Read();
	
	if (_controller.Get_SELECT())	_is_movement_lock = YES;
	if (_controller.Get_START())	_is_movement_lock = NO;
}

//----------------------------------------------------------------------//

void Main::Fire()
{
	_valve_gun_trigger.Open_and_Close(_controller.Get_A(), 1000);
	
	if (_valve_gun_trigger.Get_state_valveNO())
	{
		if (_timer_gun == TIMER_INITAL_VALUE)
		{
			_timer_gun = Timer::General::Set_counter(200);
		}
		
		if (Timer::General::Is_current_bigger_than(_timer_gun))
		{
			_timer_gun = TIMER_INITAL_VALUE;
			
			_valve_gun_trigger.Set_NO(NO);
		}
	}
}

//----------------------------------------------------------------------//

void Main::Fall()
{
	_valve_fall_support.Open_or_Close(_controller.Get_X(), (_valve_fall_stretch.Is_open() ? 0 : 200));
	
	_valve_fall_stretch.Open_or_Close(_controller.Get_Y());
	
	if (_controller.Get_HOME())
	{
		_valve_fall_feed_fall_zone.Open_and_Close(YES, 5000);
	}
	
	_valve_fall_feed_wait_zone.Open_and_Close(_controller.Get_B(),  50, 650);
	
	_valve_fall_feed_fall_zone.Open_and_Close(_controller.Get_B(), 100, 600);
}

//----------------------------------------------------------------------//

void Main::Move_right()
{
	switch (_wheel.Get_move_direc_y())
	{
		case Direction::NORTH:
		{
			_wheel.Move(DEG_MOVE_FRONT_RIGHT);
			
			break;
		}
		case Direction::SOUTH:
		{
			_wheel.Move(DEG_MOVE_BACK_RIGHT);
			
			break;
		}
		case Direction::yCENTER:
		{
			_wheel.Move(DEG_MOVE_RIGHT);
			
			break;
		}
	}
}

//----------------------------------------------------------------------//

void Main::Move_left()
{
	switch (_wheel.Get_move_direc_y())
	{
		case Direction::NORTH:
		{
			_wheel.Move(DEG_MOVE_FRONT_LEFT);
			
			break;
		}
		case Direction::SOUTH:
		{
			_wheel.Move(DEG_MOVE_BACK_LEFT);
			
			break;
		}
		case Direction::yCENTER:
		{
			_wheel.Move(DEG_MOVE_LEFT);
			
			break;
		}
	}
}

//----------------------------------------------------------------------//

void Main::Move_lenghways()
{
	switch (_wheel.Get_move_direc_y())
	{
		case Direction::NORTH:
		{
			_wheel.Move(DEG_MOVE_FRONT);
			
			break;
		}
		case Direction::SOUTH:
		{
			_wheel.Move(DEG_MOVE_BACK);
			
			break;
		}
		case Direction::yCENTER:
		{
			_wheel.Stop();
			
			break;
		}
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel()
{
	_wheel.Set_move_direction(_controller.Get_cross_key_x(), _controller.Get_cross_key_y());
	
	_wheel.Set_turn_direction(_controller.Get_R(), _controller.Get_L());
	
	if (_wheel.Get_turn_direc() == NON_TURN)
	{
		switch (_wheel.Get_move_direc_x())
		{
			case Direction::EAST:
			{
				Move_right();
				
				break;
			}
			case Direction::WEST:
			{
				Move_left();
				
				break;
			}
			case Direction::xCENTER:
			{
				Move_lenghways();
				
				break;
			}
		}
	}
	else
	{
		_wheel.SpinTurn();
	}
	
	_wheel.Adjust(120, 90, 150, 100);
}

//----------------------------------------------------------------------//

void Main::Process()
{
	if (_is_movement_lock == NO)
	{
		Fall();
		
		Fire();
		
		if (_controller.Get_ZL() | _controller.Get_ZR())
		{
			_wheel.Set(15);
		}
		else
		{
			_wheel.Set(7);
		}
		
		Move_wheel();
	}
}

//----------------------------------------------------------------------//

void Main::Output()
{
	if (_is_movement_lock)
	{
		if (PORT_LED == LED_STATE_UNLOCK)
		{
//			LCD::Write(0x40, "       Lock Mode");
			
			PORT_LED = LED_STATE_LOCK;
		}
		
		_wheel.Write_clear();
	}
	else
	{
		if (PORT_LED == LED_STATE_LOCK)
		{
//			LCD::Clear_under();
			
			PORT_LED = LED_STATE_UNLOCK;
		}
		
		_wheel.Write();
		
		const UartData8bit _data_uart_valve_1 =
		(
			_valve_fall_feed_fall_zone.Get_data() |
			_valve_fall_feed_wait_zone.Get_data()
		);
		
		const UartData8bit _data_uart_valve_2 =
		(
			_valve_fall_support.Get_data() |
			_valve_fall_stretch.Get_data() |
			_valve_gun_trigger.Get_data()
		);
		
		_uart_valve_1.Transmit_8bit(_data_uart_valve_1);
		_uart_valve_2.Transmit_8bit(_data_uart_valve_2);
		
//		LCD::Write(0x40, _data_uart_valve_1, 8, DECIMAL_02);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}
}
}
