
/*************************************************************************
  プロジェクトのテンプレート。 実装。
*************************************************************************/

#include <MainCircit/MainCircit.h>

#include "Project_11.h"

/************************************************************************/

namespace Dendrobium
{

namespace Master
{

/************************************************************************/

#define INIT_LED()	DDRA = 0xff; PORTA = 0x00

#define PORT_LED	PORTA

#define LED_STATE_LOCK		0x00
#define LED_STATE_UNLOCK	0x0f

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	:_controller(Uart::NUM_0)
	
	,_wheel(Uart::NUM_1, 0, 1, 2, 3)
	,_motor_gun_angle(4)
	,_motor_slave_move(5)
	
	,_uart_valve(Uart::NUM_3)
	,_valve_fire(VALVE::NUM_4)
	,_valve_rod(VALVE::NUM_0)
	,_valve_stopper(VALVE::NUM_2)
{
	LCD::Initialize();
	
	INIT_LED();
	
	_is_movement_lock = YES;
	
	_wheel.Record_pwm(PWM_WHEEL_NORMAL);
	
	_wheel[WheelPlace::FRONT_RIGHT].Want_to_reverse_signal(YES);
	_wheel[WheelPlace::FRONT_LEFT].Want_to_reverse_signal(YES);
	_wheel[WheelPlace::BACK_RIGHT].Want_to_reverse_signal(YES);
	
	_motor_gun_angle = _motor_slave_move = PWM_MOTOR;
	
	_motor_gun_angle.Set_steps(STEPS_USE);
	_motor_slave_move.Set_steps(STEPS_USE);
	
	LCD::Write(0x00, "300   Dendrobium", 75);
	LCD::Write(0x40, "          Master");
	
	LCD::Write(0x40, _wheel[WheelPlace::FRONT_RIGHT].Get_number(), 1, DECIMAL_10);
	LCD::Write(0x41, _wheel[WheelPlace::BACK_RIGHT].Get_number(), 1, DECIMAL_10);
	LCD::Write(0x42, _wheel[WheelPlace::BACK_LEFT].Get_number(), 1, DECIMAL_10);
	LCD::Write(0x43, _wheel[WheelPlace::FRONT_LEFT].Get_number(), 1, DECIMAL_10);
	
	LCD::Write(0x45, _motor_gun_angle.Get_number(), 1, DECIMAL_10);
	LCD::Write(0x46, _motor_slave_move.Get_number(), 1, DECIMAL_10);
}

//----------------------------------------------------------------------//

void Main :: Input()
{
	_controller.Read();
}

//----------------------------------------------------------------------//

void Main :: Work_wheel()
{
	_wheel.Set_move_direction(_controller.Get_L_stick_y());
	
	switch (_controller.Get_R_stick_y())
	{
		case Direction::NORTH:		_wheel.Record_pwm(PWM_WHEEL_HIGH);		break;
		case Direction::SOUTH:		_wheel.Record_pwm(PWM_WHEEL_LOW);		break;
		case Direction::yCENTER:	_wheel.Record_pwm(PWM_WHEEL_NORMAL);	break;
	}
	
	if (_wheel.Is_move())
	{
		_wheel.Curve(WHEEL_CURVE_PERSENT, _controller.Get_L1(), _controller.Get_R1());
	}
	else
	{
		if (
			(_controller.Get_L1() & _controller.Get_L2()) |
			(_controller.Get_R1() & _controller.Get_R2())
		)
		{
			_wheel.SpinTurn(_controller.Get_L1(), _controller.Get_R1());
		}
		else if (_controller.Get_L1() | _controller.Get_L2())
		{
			_wheel.PivotTurn(WheelPlace::FRONT_RIGHT, _controller.Get_L2(), _controller.Get_L1());
		}
		else if (_controller.Get_R1() | _controller.Get_R2())
		{
			_wheel.PivotTurn(WheelPlace::FRONT_LEFT , _controller.Get_R1(), _controller.Get_R2());
		}
		else
		{
			_wheel.Stop();
		}
	}
}

//----------------------------------------------------------------------//

void Main :: Work_motor()
{
	switch (_controller.Get_cross_key_y())
	{
		case Direction::NORTH:		_motor_slave_move.Set(SIGNAL_FORWARD);	break;
		case Direction::SOUTH:		_motor_slave_move.Set(SIGNAL_REVERSE);	break;
		case Direction::yCENTER:	_motor_slave_move.Set(SIGNAL_BREAK);		break;
	}
	
	switch (_controller.Get_cross_key_x())
	{
		case Direction::EAST:		_motor_gun_angle.Set(SIGNAL_FORWARD);	break;
		case Direction::WEST:		_motor_gun_angle.Set(SIGNAL_REVERSE);	break;
		case Direction::xCENTER:	_motor_gun_angle.Set(SIGNAL_BREAK);		break;
	}
}

//----------------------------------------------------------------------//

void Main :: Work_valve()
{
	_valve_rod.Open_and_Close(_controller.Get_Triangle(), TIME_ROD_OPEN);
	
	if (_valve_rod.Is_open())
	{
		if (_controller.Get_Circle())	_valve_stopper.Want_to_open(NO);
		
		_valve_stopper.Open_or_Close(_controller.Get_Circle());
	}
	
	_valve_fire.Open_or_Close(_controller.Get_Square());
}

//----------------------------------------------------------------------//

void Main :: Process()
{
	if (_controller.Get_START())	_is_movement_lock = NO;
	if (_controller.Get_SELECT())	_is_movement_lock = YES;
	
	if (_is_movement_lock == NO)
	{
		Work_wheel();
		
		Work_motor();
		
		Work_valve();
	}
}

//----------------------------------------------------------------------//

void Main :: Output()
{
	if (_is_movement_lock)
	{
		_wheel.Write_clear();
		_motor_gun_angle.Write_clear(_wheel.Get_uart_adrs());
		_motor_slave_move.Write_clear(_wheel.Get_uart_adrs());
		
		if (PORT_LED == LED_STATE_UNLOCK)
		{
			LCD::Write(0x40, "       Lock Mode");
			
			PORT_LED = LED_STATE_LOCK;
		}
	}
	else
	{
		_wheel.Write();
		_motor_gun_angle.Write(_wheel.Get_uart_adrs());
		_motor_slave_move.Write(_wheel.Get_uart_adrs());
		
		_uart_valve.Transmit_8bit(_valve_fire.Get_data() | _valve_rod.Get_data() | _valve_stopper.Get_data());
		
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
