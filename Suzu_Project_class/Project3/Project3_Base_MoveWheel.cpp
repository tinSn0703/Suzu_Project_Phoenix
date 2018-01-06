
#include <MainCircit/MainCircit.h>

#include "Project3_define.h"
#include "Project3_Base_MoveWheel.h"

/************************************************************************/

namespace Project3
{

namespace Base
{

/************************************************************************/

//----------------------------------------------------------------------//

MoveWheel :: MoveWheel(const UartNum _uart_num_wheel, const MotorNumber _motor_min_num)

	: _mem_wheel(_motor_min_num, _uart_num_wheel)

{	
	_mem_time_to_allow_reverse = 0;
	
	_mem_is_enabled_reverse = NO;
	
	_mem_wheel.Set(WHEEL_PWM_INIT);
	
	_mem_wheel.Set_wheel_place(Four::FRONT_LEFT	,WHEEL_NUM_FR_LE);
	_mem_wheel.Set_wheel_place(Four::FRONT_RIGHT	,WHEEL_NUM_FR_RI);
	_mem_wheel.Set_wheel_place(Four::BACK_RIGHT	,WHEEL_NUM_BA_RI);
	_mem_wheel.Set_wheel_place(Four::BACK_LEFT	,WHEEL_NUM_BA_LE);
}

//----------------------------------------------------------------------//

void MoveWheel :: Operate_pwm(const Btn _is_pwm_up, const Btn _is_pwm_down)
{
	_mem_wheel.Set(_mem_wheel.Get_pwm());
	
	if (_is_pwm_up)		_mem_wheel ++;
	if (_is_pwm_down)	_mem_wheel --;
}

//----------------------------------------------------------------------//

void MoveWheel :: Adjust_pwm_move_y() 
{
	if (_mem_wheel.Get_direc_y() != CENTER_Y)
	{
		_mem_wheel[Four::BACK_RIGHT].Adjust_for
		(
			_mem_wheel.Is_turn_l() ? -5 : 0
		);
		
		_mem_wheel[Four::BACK_LEFT].Adjust_for
		(
			_mem_wheel.Is_turn_r() ? -5 : 0
		);
	}
}

//----------------------------------------------------------------------//

void MoveWheel :: Adjust_pwm_move_x()
{
// 	if (_mem_wheel.Get_direc_x() != CENTER_X)
// 	{
// 		_mem_wheel[BACK_RIGHT].Adjust_for
// 		(
// 			_mem_is_turn_l ? -5 : 0
// 		);
// 		
// 		_mem_wheel[BACK_LEFT].Adjust_for
// 		(
// 			_mem_is_turn_r ? -5 : 0
// 		);
// 	}
}

//----------------------------------------------------------------------//

void MoveWheel :: Adjust_pwm()
{
	MoveWheel::Adjust_pwm_move_x();
	MoveWheel::Adjust_pwm_move_y();
}

//----------------------------------------------------------------------//

void MoveWheel :: Memory_signal()
{
	for (usint i = 0; i < 4; i++)
	{
		_mem_memory_signal[(Four::WheelPlace)i] = _mem_wheel[(Four::WheelPlace)i].Get_sig();
	}
}

//----------------------------------------------------------------------//

void MoveWheel :: Set_stop_signal()
{
	for (usint i = 0; i < 4; i++)
	{
		_mem_wheel[(Four::WheelPlace)i] = Reversal_Signal(_mem_memory_signal[(Four::WheelPlace)i]);
	}
}

//----------------------------------------------------------------------//

void MoveWheel :: Move_Counter()
{
	if (_mem_wheel.Is_moved())
	{
		MoveWheel::Memory_signal();
		
		if (_mem_is_enabled_reverse == FALSE)
		{
			_mem_time_to_allow_reverse = GeneralTimer::Set_counter(120);
			
			_mem_is_enabled_reverse = TRUE;
		}
	}
	else
	{
		if (_mem_is_enabled_reverse)
		{
			if (_mem_time_to_allow_reverse > GeneralTimer::Read())
			{
				_mem_wheel.Set_non_memory(_mem_wheel.Get_pwm() / 2);
				
			 	MoveWheel::Set_stop_signal();
				
				_mem_wheel.Want_to_use_steps(NO);
			}
			
			_mem_is_enabled_reverse = FALSE;
		}
	}
}

//----------------------------------------------------------------------//

void MoveWheel :: Move()
{	
	MoveWheel::Adjust_pwm();
	
	_mem_wheel.Want_to_use_steps(YES);
	
	_mem_wheel.Move_or_Turning();
	
	MoveWheel::Move_Counter();
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

/************************************************************************/
