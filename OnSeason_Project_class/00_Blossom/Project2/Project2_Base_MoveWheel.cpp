
#include <MainCircit/MainCircit.h>

#include "Project2_define.h"
#include "Project2_Base_MoveWheel.h"

/************************************************************************/

namespace Project2
{

/************************************************************************/

namespace Base
{

/************************************************************************/

//----------------------------------------------------------------------//

MoveWheel :: MoveWheel()

	: _mem_wheel(MOTOR_NUM_WHEEL, UART_NUM_WHEEL)

{
	_mem_time_to_allow_reverse = 0;
	
	_mem_is_enabled_reverse = NO;
	
	_mem_wheel.Record_pwm(WHEEL_PWM_INIT);
	
	_mem_wheel.Set_wheel_place(Four::FRONT_LEFT		,WHEEL_NUM_FR_LE);
	_mem_wheel.Set_wheel_place(Four::FRONT_RIGHT	,WHEEL_NUM_FR_RI);
	_mem_wheel.Set_wheel_place(Four::BACK_RIGHT		,WHEEL_NUM_BA_RI);
	_mem_wheel.Set_wheel_place(Four::BACK_LEFT		,WHEEL_NUM_BA_LE);
}

//----------------------------------------------------------------------//

void MoveWheel :: Operate_pwm(const Btn _is_pwm_up, const Btn _is_pwm_down)
{
	_mem_wheel.Set_record_pwm();

	if (_is_pwm_up)		_mem_wheel ++;
	if (_is_pwm_down)	_mem_wheel --;
}

//----------------------------------------------------------------------//

void MoveWheel :: Adjust_pwm_move_y() 
{
	if (_mem_wheel.Get_direc_y() != Direc::ZERO_Y)
	{
		if (_mem_wheel.Is_turn_l())
		{
//			_mem_wheel[FRONT_RIGHT].Adjust_for(-10);
			_mem_wheel[Four::BACK_RIGHT].Adjust_for(-5);
		}
		else
		{
//			_mem_wheel[FRONT_RIGHT].Adjust_for(0);
			_mem_wheel[Four::BACK_RIGHT].Adjust_for(0);
		}
		
		if (_mem_wheel.Is_turn_l())
		{
			_mem_wheel[Four::BACK_LEFT].Adjust_for(-5);
		}
		else
		{
			_mem_wheel[Four::BACK_LEFT].Adjust_for(0);
		}
	}
}

//----------------------------------------------------------------------//

void MoveWheel :: Adjust_pwm_move_x()
{
	
}

//----------------------------------------------------------------------//

void MoveWheel :: Adjust_pwm()
{
	MoveWheel::Adjust_pwm_move_x();
	MoveWheel::Adjust_pwm_move_y();
}

//----------------------------------------------------------------------//

void MoveWheel :: Stop_driving()
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
				_mem_wheel.Set(_mem_wheel.Get_pwm() / 2);
				
			 	MoveWheel::Set_stop_signal();
				
				_mem_wheel.Want_to_use_steps(NO);
			}
			
			_mem_is_enabled_reverse = FALSE;
		}
	}
}

//----------------------------------------------------------------------//

void MoveWheel :: Drive()
{	
	MoveWheel::Adjust_pwm();
	
	_mem_wheel.Want_to_use_steps(YES);
	
	_mem_wheel.Move_or_Turning();
	
	MoveWheel::Stop_driving();
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/

};

/************************************************************************/
