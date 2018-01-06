
#include <math.h>

#include <MainCircit/MainCircit.h>

#include "Project5.h"

/************************************************************************/

namespace Zephyranthes
{

namespace Warhead
{

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	: _controller(Uart::NUM_0)
	, _wheel(Uart::NUM_1)
	, _motor_stand(3)
	, _uart_rod(Uart::NUM_2)
{
	_motor_stand.Set_steps(STEPS_USE);
	
	_wheel.Set_wheel_place(WheelPlace::FRONT, 1);
	_wheel.Set_wheel_place(WheelPlace::LEFT , 0);
	_wheel.Set_wheel_place(WheelPlace::RIGHT, 2);
	
	_wheel.Set_steps(STEPS_USE);
	_wheel.Record_pwm(15);
	
	_rod[0].Reset(VALVE::NUM_0);
	_rod[1].Reset(VALVE::NUM_1);
	_rod[2].Reset(VALVE::NUM_2);
	_rod[3].Reset(VALVE::NUM_3);

	_mem_timer[0] = 0;
	_mem_timer[1] = 0;
	_mem_timer[2] = 0;
	_mem_timer[3] = 0;

	_is_movement_lock = YES;
	
	_mem_is_enabled_pwm_up		= YES;
	_mem_is_enabled_pwm_down	= YES;
	_mem_is_enabled_move_rod	= YES;
	
	LCD::Write(0x00, "101 Zephyranthes", 75);
	LCD::Write(0x40, "Name     Warhead");
}

//----------------------------------------------------------------------//

void Main :: Input()
{
	_controller.Read();
	
	if (_controller.Get_SELECT())
	{
		LCD::Write(0x40, "Lock Mode       ");

		_is_movement_lock = YES;
	}
	if (_controller.Get_START())
	{
		LCD::Clear_under();
		
		_is_movement_lock = NO;
	}
}

//----------------------------------------------------------------------//

void Main :: Process()
{
	_wheel.Set_move_direction(_controller.Get_L_stick_x(), _controller.Get_L_stick_y());
	
	_wheel.Set_turn_direction
	(
		_controller.Get_L1() | _controller.Get_L2(),
		_controller.Get_R1() | _controller.Get_R2()
	);
	
	Main::Count_wheel_pwm
	(
		_controller.Get_R3(),
		_controller.Get_L3()
	);
	
	if (_wheel.Is_move())
	{
		_wheel.Curve(75);
	}
	else
	{
		if (
			(_controller.Get_L1() & _controller.Get_L2()) |
			(_controller.Get_R1() & _controller.Get_R2())
		)
		{
			_wheel.SpinTurn();
		}
		else if (_controller.Get_L1() | _controller.Get_L2())
		{
			_wheel.PivotTurn(WheelPlace::LEFT , _controller.Get_L1(), _controller.Get_L2());
		}
		else if (_controller.Get_R1() | _controller.Get_R2())
		{
			_wheel.PivotTurn(WheelPlace::RIGHT, _controller.Get_R1(), _controller.Get_R2());
		}
		else
		{
			_wheel.Stop();
		}
	}
	
	Main::Transformation
	(
		Is_Direction_north(_controller.Get_cross_key_y()),
		Is_Direction_south(_controller.Get_cross_key_y())
	);
	
	Main::Attack(_controller.Get_Circle());
}

//----------------------------------------------------------------------//

void Main :: Output()
{
	if (_is_movement_lock)
	{
		_wheel.Write_clear();
		
		_motor_stand.Write_clear(_wheel.Get_uart_adrs());
	}
	else
	{
		_wheel.Write();
		
		_motor_stand.Write(_wheel.Get_uart_adrs());
		
		_uart_rod.Transmit_8bit
		(
			_rod[0].Get_data() |
			_rod[1].Get_data() |
			_rod[2].Get_data() |
			_rod[3].Get_data()
		);
		
		Display();
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}

};

/************************************************************************/
