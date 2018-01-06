
#include <MainCircit/MainCircit.h>

#include "Project_12.h"

/************************************************************************/

namespace Gerbera
{

namespace Ikku
{

/************************************************************************/

#define INIT_LED()	DDRA = 0xff; PORTA = 0x00

#define PORT_LED	PORTA

#define LED_STATE_LOCK		0x00
#define LED_STATE_UNLOCK	0x0f

#define STR_PROJECT_NAME "510      Gerbera"
#define STR_MACHINE_NAME "         OnlySky"

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	: _controller(Uart::NUM_0)
	
	, _wheel(Uart::NUM_1)
	
	, _uart_valve(Uart::NUM_3)
	, _valve_trigger(VALVE::NUM_7)
	, _valve_parge(VALVE::NUM_6)
{
	LCD::Write(0x00, STR_PROJECT_NAME, 75);
	LCD::Write(0x40, STR_MACHINE_NAME);
	
	INIT_LED();
	
	_wheel.Set_wheel_place(WheelPlace::FRONT_RIGHT,	7);
	_wheel.Set_wheel_place(WheelPlace::BACK_RIGHT,	4);
	_wheel.Set_wheel_place(WheelPlace::BACK_LEFT,	5);
	_wheel.Set_wheel_place(WheelPlace::FRONT_LEFT,	6);
	
	_wheel.Record_pwm(15);
	
	_wheel.Set_steps(STEPS_USE);
	
	_memory_direc_x = Direction::xCENTER;
	_memory_direc_y = Direction::yCENTER;
	
	_memory_is_turn_l = NO;
	_memory_is_turn_r = NO;
	
	_memory_pwm = 0;
	
	_is_movement_lock = YES;
}

//----------------------------------------------------------------------//

void Main :: Input()
{
	_controller.Read();
}

//----------------------------------------------------------------------//

void Main :: Work_wheel()
{
	switch (_controller.Get_R_stick_y())
	{
		case Direction::NORTH:		_wheel.Record_pwm(20);	break;
		case Direction::SOUTH:		_wheel.Record_pwm(10);	break;
		case Direction::yCENTER:	_wheel.Record_pwm(15);	break;
	}
	
	_wheel.Set_move_direction(_controller.Get_L_stick_x(), _controller.Get_L_stick_y());
	
	_wheel.Set_turn_direction(_controller.Get_L(), _controller.Get_R());
	
	if (_wheel.Is_move())
	{
		_wheel.Curve(75);
	}
	else
	{
		_wheel.SpinTurn();
	}
	
	_wheel.Adjust(100, 100, 100, 100);
}

//----------------------------------------------------------------------//

void Main :: Process()
{
	if (_controller.Push_START())	_is_movement_lock = NO;
	if (_controller.Push_SELECT())	_is_movement_lock = YES;
	
	if (_is_movement_lock == NO)
	{
		Work_wheel();
		
		_valve_trigger.Open_and_Close(_controller.Get_A(), 200);
		
		if (_controller.Get_B())
		{
			_valve_parge.Want_to_open(YES);
		}
	}
}

//----------------------------------------------------------------------//

void Main :: Output()
{
	if (_is_movement_lock)
	{
		_wheel.Write_clear();
		
		if (PORT_LED == LED_STATE_UNLOCK)
		{
			if (_controller.Get_START())
			{
				LCD::Initialize();
				
				LCD::Write(0x00, STR_PROJECT_NAME, 75);
			}
			
			LCD::Write(0x40, "       Lock Mode");
			
			PORT_LED = LED_STATE_LOCK;
		}
	}
	else
	{
		if	(
				(_wheel.Get_move_direc_x() != _memory_direc_x) ||
				(_wheel.Get_move_direc_y() != _memory_direc_y) ||
				(_wheel.Is_turn_l() != _memory_is_turn_l) ||
				(_wheel.Is_turn_r() != _memory_is_turn_r) ||
				(_wheel.Get_pwm()	!= _memory_pwm		)
			)
		{
			_wheel.Write();
			
			_memory_direc_x		= _wheel.Get_move_direc_x();
			_memory_direc_y		= _wheel.Get_move_direc_y();
			_memory_is_turn_l	= _wheel.Is_turn_l();
			_memory_is_turn_r	= _wheel.Is_turn_r();
			_memory_pwm			= _wheel.Get_pwm();
		}
		
		_uart_valve.Transmit_8bit(_valve_trigger.Get_data() | _valve_parge.Get_data());
		
		if (PORT_LED == LED_STATE_LOCK)
		{
			LCD::Clear_under();
			
			PORT_LED = LED_STATE_UNLOCK;
		}
		
		_wheel.Display_power(0x40);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}

}

/************************************************************************/
