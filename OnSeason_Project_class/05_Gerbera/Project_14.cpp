
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

Main::Main()

	: _controller(Uart::NUM_0)
	
	, _wheel(Uart::NUM_1)
	
	, _pack_man(4, Uart::NUM_1)
	
	, _motor_tyanpera(5)
	
	, _uart_valve(Uart::NUM_3)
	, _valve_rod(VALVE::NUM_0)
{
	if (LCD::Is_initialize())	LCD::Initialize();
	
	INIT_LED();
	
	_wheel.Set_wheel_place(WheelPlace::FRONT_RIGHT,	1);
	_wheel.Set_wheel_place(WheelPlace::BACK_RIGHT,	3);
	_wheel.Set_wheel_place(WheelPlace::BACK_LEFT,	2);
	_wheel.Set_wheel_place(WheelPlace::FRONT_LEFT,	0);
	
	_wheel.Set_front(90);
	
	_wheel.Record_pwm(31);
	
	_timer_pack_man_stand = TIMER_INITAL_VALUE;
	
	_is_movement_lock = YES;
	
	_is_remove_tyanpera = NO;
	
	_is_error_happen = NO;
	
	_is_machine_init = YES;
	
	_is_enable_change_display = YES;
	
	_count_lcd = 0;
	
	LCD::Write(0x00, " Nothing to worry");
	LCD::Write(0x40, "You're unbeatable");
	
	_delay_ms(100);
	
	LCD::Write(0x00, " 520 Banri Final");
	LCD::Write(0x40, "                ");
}

//----------------------------------------------------------------------//

void Main::Lock()
{
	if	(
			(_controller.Get_error_state() == READ_INCOMPLETE)	||
			(_controller.Get_error_state() == READ_FAILURE)
		)
	{
		if (_is_movement_lock == NO)
		{
			_is_error_happen = YES;
		}
		
		_is_movement_lock = YES;
		
		_is_remove_tyanpera = NO;
		
		_timer_pack_man_stand = TIMER_INITAL_VALUE;
		
		_pack_man.Clear();
	}
	
	if (_controller.Get_SELECT())
	{
		_is_movement_lock = YES;
		
		_is_remove_tyanpera = NO;
		
		_timer_pack_man_stand = TIMER_INITAL_VALUE;
		
		_pack_man.Clear();
	}
}

//----------------------------------------------------------------------//

void Main::Unlock()
{
	if (_controller.Get_error_state() == READ_SUCCESS)
	{
		if (_controller.Get_START())
		{
			_is_machine_init = NO;
			
			_is_movement_lock = NO;
			
			_is_error_happen = NO;
		}
		
		if (_is_error_happen & _controller.Is_commnad_push())
		{
			_is_movement_lock = NO;
			
			_is_error_happen = NO;
		}
	}
}

//----------------------------------------------------------------------//

void Main :: Input()
{
	_controller.Read();
	
	_pack_man.Read();
	
	Unlock();
	
	Lock();
	
	_is_move_front	= _controller.Get_X();
	_is_move_back	= _controller.Get_B();
	_is_move_right	= _controller.Get_A();
	_is_move_left	= _controller.Get_Y();
}

//----------------------------------------------------------------------//

void Main::Set_wheel_turn()
{
	if (_controller.Get_L() & _controller.Get_R())
	{
		_wheel.Set_turn_direction(NON_TURN);
		
		_wheel.Record_pwm(15);
	}
	else if (_controller.Get_L())
	{
		_wheel.Set_turn_direction(LEFT_TURN);
		
		_wheel.Record_pwm(31);
	}
	else if (_controller.Get_R())
	{
		_wheel.Set_turn_direction(RIGHT_TURN);
		
		_wheel.Record_pwm(31);
	}
	else
	{
		_wheel.Set_turn_direction(NON_TURN);
		
		_wheel.Record_pwm(31);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_right()
{
	if (_is_move_front)
	{
		_wheel.Set_steps(STEPS_04MS);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK_LEFT);
	}
	else if (_is_move_back)
	{
		_wheel.Set_steps(STEPS_04MS);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK_RIGHT);
	}
	else
	{
		_wheel.Set_steps(STEPS_MIN);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_RIGHT);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_left()
{
	if (_is_move_front)
	{
		_wheel.Set_steps(STEPS_04MS);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_FRONT_LEFT);
	}
	else if (_is_move_back)
	{
		_wheel.Set_steps(STEPS_04MS);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK_LEFT);
	}
	else
	{
		_wheel.Set_steps(STEPS_MIN);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_LEFT);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_front()
{
	if (_is_move_right)
	{
		_wheel.Set_steps(STEPS_04MS);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_FRONT_RIGHT);
	}
	else if (_is_move_left)
	{
		_wheel.Set_steps(STEPS_04MS);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_FRONT_LEFT);
	}
	else
	{
		if (_pack_man.Is_stnad_over() || (_pack_man.Get_stand_direction() == Direction::OVER))
		{
			_wheel.Set_steps(STEPS_16MS);
		}
		else if (_pack_man.Is_stnad_under())
		{
			_wheel.Set_steps(STEPS_08MS);
		}
		else
		{
			_wheel.Set_steps(STEPS_04MS);
		}
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_FRONT);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_back()
{
	if (_is_move_right)
	{
		_wheel.Set_steps(STEPS_04MS);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK_RIGHT);
	}
	else if (_is_move_left)
	{
		_wheel.Set_steps(STEPS_04MS);
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK_LEFT);
	}
	else
	{
		if (_pack_man.Is_stnad_under())
		{
			_wheel.Set_steps(STEPS_08MS);
		}
		else
		{
			_wheel.Set_steps(STEPS_04MS);
		}
		
		_wheel.Curve(PERSENT_CURVE, DEG_MOVE_BACK);
	}
}

//----------------------------------------------------------------------//

void Main::Move_wheel_turn()
{
	_wheel.Set_steps(STEPS_MIN);
	
	_wheel.SpinTurn();
}

//----------------------------------------------------------------------//

void Main::Move_wheel()
{
	Set_wheel_turn();
	
	if (_is_move_front)
	{
		Move_wheel_front();
	}
	else if (_is_move_back)
	{
		Move_wheel_back();
	}
	else if (_is_move_right)
	{
		Move_wheel_right();
	}
	else if (_is_move_left)
	{
		Move_wheel_left();
	}
	else if (_wheel.Is_turn_l() | _wheel.Is_turn_r())
	{
		Move_wheel_turn();
	}
	else
	{
		_wheel.Stop();
	}
}

//----------------------------------------------------------------------//

void Main::Move_tyanpera(const DirectionY _move)
{
	switch (_move)
	{
		case Direction::OVER:
		{
			_motor_tyanpera.Set(SIGNAL_FORWARD, PWM_TYANPERA);
			
			break;
		}
		case Direction::UNDER:
		{
			_motor_tyanpera.Set(SIGNAL_REVERSE, PWM_TYANPERA);
			
			break;
		}
		case Direction::yCENTER:
		{
			if (_motor_tyanpera.Get_sig() == SIGNAL_FORWARD)
			{
				_motor_tyanpera.Set(PWM_TYANPERA_STATE);
			}
			else
			{
				_motor_tyanpera.Set(SIGNAL_BREAK);
			}
			
			break;
		}
	}
}

//----------------------------------------------------------------------//

void Main::Move_tyanpera_and_pack_man()
{
	if (_timer_pack_man_stand == TIMER_INITAL_VALUE)
	{
		Move_tyanpera(_controller.Get_cross_key_y());
		
		if (_is_remove_tyanpera)
		{
			_pack_man.Set_stand_over(_controller.Get_ZL());
			_pack_man.Set_stand_under(_controller.Get_ZR());
			
			_pack_man.Move_pack_man_arm(_controller.Get_L_stick_y());
		}
		else
		{
			if (_controller.Get_ZL())
			//パックマンからどけるためにちょっと動かす
			{
				_timer_pack_man_stand = Timer::General::Set_counter(TIME_MOVE_TYANPERA);
				
				Move_tyanpera(Direction::UNDER);
			}
		}
	}
	else
	{
		if (Timer::General::Is_current_bigger_than(_timer_pack_man_stand))
		{
			if (_is_remove_tyanpera == NO)
			{
				Move_tyanpera(Direction::yCENTER);
				
				_pack_man.Set_stand_over(YES);
				
				_is_remove_tyanpera = YES;
				
				_timer_pack_man_stand = TIMER_INITAL_VALUE;
			}
		}
	}
	
	_pack_man.Move_stand();
}

//----------------------------------------------------------------------//

void Main::Move_valve()
{
	_valve_rod.Open_and_Close(_controller.Get_cross_key(Direction::RIGHT), TIME_VALVE_CLOSE);
}

//----------------------------------------------------------------------//

void Main::Process()
{
	if (_is_movement_lock == NO)
	{
		Move_wheel();
		
		Move_tyanpera_and_pack_man();
		
		Move_valve();
		
		if (_controller.Get_HOME())
		{
			if (_is_enable_change_display)
			{
				_is_enable_change_display = NO;
				
				_count_lcd ++;
				
				if (_count_lcd == 4)	_count_lcd = 0;
				
				PORT_LED = LED_STATE_LOCK;
			}
		}
		else
		{
			_is_enable_change_display = YES;
		}
	}
}

//----------------------------------------------------------------------//

void Main::Display_lock_mode()
{
	if (PORT_LED == LED_STATE_UNLOCK)
	{
		if (_is_machine_init == NO)
		{
			if (_controller.Get_error_state() == READ_FAILURE)
			{
				LCD::Write(0x00, "      Read Error");
				LCD::Write(0x00, "         Failure");
			}
			else if (_controller.Get_error_state() == READ_INCOMPLETE)
			{
				LCD::Write(0x00, "      Read Error");
				LCD::Write(0x40, "      Incomplete");
			}
			else
			{
				LCD::Write(0x00, "       Lock Mode");
				LCD::Clear_under();
			}
		}
		
		PORT_LED = LED_STATE_LOCK;
	}
	
	if (_is_error_happen == NO)
	{
		_pack_man.Display_sensor_stand(0x40);
		_pack_man.Display_sensor_arm_shorten(0x43);
		_pack_man.Display_sensor_arm_stretch(0x48);
	}
}

//----------------------------------------------------------------------//

void Main::Display_unlock_mode()
{
	if (PORT_LED == LED_STATE_LOCK)
	{
		LCD::Write(0x00, " 520 Banri Final");
		LCD::Clear_under();
		
		LCD::Write(0x40, _count_lcd, 1, DECIMAL_10);
		
		PORT_LED = LED_STATE_UNLOCK;
	}
	
	switch (_count_lcd)
	{
		case 0:
		{
			_controller.Display(0x42);
			
			break;
		}
		case 1:
		{
			_wheel.Display_power(0x42);
			
			LCD::Write(0x4f, _valve_rod.Is_open(), 1, DECIMAL_02);
			
			break;
		}
		case 2:
		{
			_motor_tyanpera.Display_power(0x42);
			
			_pack_man.Display_sensor_stand(0x46);
			_pack_man.Display_motor_stand(0x49);
			
			break;
		}
		default:
		{
			_pack_man.Display_sensor_arm_shorten(0x42);
			_pack_man.Display_sensor_arm_stretch(0x47);
			_pack_man.Display_motor_arm(0x4c);
			
			break;
		}
	}
}

//----------------------------------------------------------------------//

void Main :: Output()
{
	if (_is_movement_lock)
	{
		_wheel.Write_clear();
		
		_motor_tyanpera.Write_clear(_wheel.Get_uart_adrs());
		
		_pack_man.Write_clear();
		
		Display_lock_mode();
	}
	else
	{
		_uart_valve.Transmit_8bit(_valve_rod.Get_data());
		
		_wheel.Write();
		
		_motor_tyanpera.Write(_wheel.Get_uart_adrs());
		
		_pack_man.Write();
		
		Display_unlock_mode();
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}
}

/************************************************************************/
