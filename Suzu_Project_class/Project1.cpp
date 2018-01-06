
#include <MainCircit/MainCircit.h>

#include "Project1.h"

/************************************************************************/

namespace Project1
{

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	: _mem_controller(UART_NUM_0)
	, _mem_wheel(0, UART_NUM_1)
	, _mem_up_down(4)
	, _mem_is_enabeld_move(FALSE)
	, _mem_is_doing_turn_r(FALSE)
	, _mem_is_doing_turn_l(FALSE)
	, _mem_time_to_allow_reverse(0)
	, _mem_is_pwm_up(FALSE)
	, _mem_is_pwm_down(FALSE)
	, _mem_is_turn_l(FALSE)
	, _mem_is_turn_r(FALSE)
	, _mem_move_up_down(CENTER_Y)
{
	_mem_bumper_sensor[0].Reset(IO_ADRS_F, IO_BIT_0);
	_mem_bumper_sensor[1].Reset(IO_ADRS_F, IO_BIT_1);
	
	_mem_arm_0_sensor[0].Reset(IO_ADRS_F, IO_BIT_2);
	_mem_arm_0_sensor[1].Reset(IO_ADRS_F, IO_BIT_3);
	
	_mem_arm_1_sensor[0].Reset(IO_ADRS_F, IO_BIT_4);
	_mem_arm_1_sensor[1].Reset(IO_ADRS_F, IO_BIT_5);
	
	_mem_arm[0].Reset(5);
	_mem_arm[1].Reset(6);
	
	_mem_arm[0].Set_uart(_mem_wheel.Get_uart());
	_mem_arm[1].Set_uart(_mem_wheel.Get_uart());
	
	_mem_arm[0].Set(15);
	_mem_arm[1].Set(5);
	
	_mem_arm[0].Want_to_use_steps(YES);
	_mem_arm[1].Want_to_use_steps(YES);
	
	_mem_up_down.Set_uart(_mem_wheel.Get_uart());
	
	_mem_up_down.Set(15);
	
	_mem_up_down.Want_to_use_steps(YES);
	
	_mem_wheel.Set(31);
	
	_mem_wheel.Set_wheel_place(Four::BACK_LEFT	,0);
	_mem_wheel.Set_wheel_place(Four::BACK_RIGHT	,1);
	_mem_wheel.Set_wheel_place(Four::FRONT_RIGHT	,2);
	_mem_wheel.Set_wheel_place(Four::FRONT_LEFT	,3);
	
	LCD_Write_str(0x00, "Suzu Project");
	
	GeneralTimer::Initialize();
}

//----------------------------------------------------------------------//

YesNo Main :: Is_unlocked()
{
	return _mem_is_enabeld_move;
}

//----------------------------------------------------------------------//

void Main :: Doing()
{
	Main::Count_pwm();
	
	Main::Shift_view();
	
	Main::Move_arm();
	
	Main::Move_up_down();
	
	Main::Drive();
}

//----------------------------------------------------------------------//

void Main :: Receive()
{
	_mem_controller.Receive();
	
	if (_mem_controller.Push_SELECT())
	{
		LCD_Clear_un();
		LCD_Write_str(0x40, "LOCK");
		
		_mem_is_enabeld_move = FALSE;
	}
	
	if (_mem_controller.Push_START())
	{
		LCD_Clear_un();
		
		_mem_is_enabeld_move = TRUE;
	}
	
	_mem_is_bumper_sensor_on[0] = Reversal_BOOL(_mem_bumper_sensor[0].In());
	_mem_is_bumper_sensor_on[1] = Reversal_BOOL(_mem_bumper_sensor[1].In());
	
	_mem_is_arm_sensor_on[0] = Reversal_BOOL(_mem_arm_0_sensor[0].In() & _mem_arm_1_sensor[0].In());
	_mem_is_arm_sensor_on[1] = Reversal_BOOL(_mem_arm_0_sensor[1].In() & _mem_arm_1_sensor[1].In());
	
	_mem_is_pwm_up	 = _mem_controller.Push_Cir();
	_mem_is_pwm_down = _mem_controller.Push_Squ();
	
	_mem_is_doing_turn_r = _mem_is_turn_r;
	_mem_is_doing_turn_l = _mem_is_turn_l;
	
	_mem_is_turn_l = _mem_controller.Get_R1();
	_mem_is_turn_r = _mem_controller.Get_L1();
	
	_mem_wheel.Set_direc(_mem_controller.Get_stick_Lx());
	_mem_wheel.Set_direc(_mem_controller.Get_stick_Ly());
	
	_mem_move_up_down = _mem_controller.Get_cross_y();
}

//----------------------------------------------------------------------//

void Main :: Count_pwm()
{
	_mem_wheel.Set(_mem_wheel.Get_pwm());
	
	if (_mem_is_pwm_up)		_mem_wheel ++;
	if (_mem_is_pwm_down)	_mem_wheel --;
}

//----------------------------------------------------------------------//

void Main :: Shift_view()
{
	static uByte _num_shift = 0;
	static BOOL _is_enubled_change_num = TRUE;
	
	switch (_mem_controller.Get_cross_x())
	{
		case EAST:
		{
			if (_is_enubled_change_num) _num_shift ++;
			
			_is_enubled_change_num = FALSE;
			
			break;
		}
		case WEST:
		{
			if (_is_enubled_change_num) _num_shift --;
			
			_is_enubled_change_num = FALSE;
			
			break;
		}
		default:
		{
			_is_enubled_change_num = TRUE;
			
			break;
		}
	}
	
	if (_mem_controller.Get_Cro())
	{
		_num_shift = 0;
	}
	
	for (uByte i = 0; i < _num_shift; i ++)
	{
		_mem_wheel.Shift_90deg();
	}
}

//----------------------------------------------------------------------//

void Main :: Move_up_down()
{
	switch (_mem_move_up_down)
	{
		case NORTH:		_mem_up_down = SIGNAL_FORWARD;	break;
		case SOUTH:		_mem_up_down = SIGNAL_REVERSE;	break;
		case CENTER_Y:	_mem_up_down = SIGNAL_BREAK;	break;
	}
}

//----------------------------------------------------------------------//

void Main :: Move_arm()
{
	static CountValue _timer = 0;
	static BOOL _is_moved_arm = FALSE;
	static BOOL _is_enabled_auto = TRUE;
	static Direc::Direc _sensor_place = Direc::CENTER;
	
	if (_mem_controller.Get_L2())
	{
		_mem_arm[1] = SIGNAL_FORWARD;
		
		_is_moved_arm = FALSE;
		_timer = 0;
	}
	else
	{
		if (_mem_controller.Get_R2())
		{
			_mem_arm[1] = SIGNAL_REVERSE;
			
			_is_moved_arm = FALSE;
			_timer = 0;
		}
		else
		{
			if (_is_moved_arm == FALSE)	_mem_arm[1] = SIGNAL_BREAK;
		}
	}
	
	switch (_mem_controller.Get_stick_Ry())
	{
		case NORTH:
		{
			_mem_arm[0] = SIGNAL_FORWARD;
			
			_is_moved_arm = FALSE;
			_timer = 0;
			
			break;
		}
		case SOUTH:
		{
			_mem_arm[0] = SIGNAL_REVERSE;
			
			_is_moved_arm = FALSE;
			_timer = 0;
			
			break;
		}
		case CENTER_Y:
		{
			if (_is_moved_arm == FALSE)	_mem_arm[0] = SIGNAL_BREAK;
			
			break;
		}
	}
	
	if (_mem_controller.Push_Tri())	_is_enabled_auto = Reversal_BOOL(_is_enabled_auto);
	
	if (Reversal_BOOL(_is_moved_arm) & _is_enabled_auto)
	{
		if (_mem_is_bumper_sensor_on[0])
		{
			_is_moved_arm = TRUE;
			
			_sensor_place = Direc::EAST;
		}
		
		if (_mem_is_bumper_sensor_on[1])
		{
			_is_moved_arm = TRUE;
			
			_sensor_place = Direc::NORTH;
		}
	}
	
	if (_is_moved_arm)
	{
		if (_sensor_place == Direc::EAST)
		{
			if (_timer == 0)
			{
				if (_mem_arm[0] == SIGNAL_BREAK)
				{
					_mem_arm[0] = SIGNAL_FORWARD;
					_mem_arm[1] = SIGNAL_BREAK;
				}
				
				if (_mem_is_arm_sensor_on[0] == TRUE)
				{
					_mem_arm[0] = SIGNAL_BREAK;
					_mem_arm[1] = SIGNAL_FORWARD;
					
					_timer = GeneralTimer::Read() + GeneralTimer::Change_count_value(450);
				}
			}
			else if (GeneralTimer::Read() > _timer)
			{
				_mem_arm[1] = SIGNAL_BREAK;
				
				if (FALSE == (_mem_is_bumper_sensor_on[0] | _mem_is_bumper_sensor_on[1]))
				{
					_is_moved_arm = FALSE;
					
					_timer = 0;
					
					_sensor_place = Direc::CENTER;
				}
			}
		}
		else if (_sensor_place == Direc::NORTH)
		{
			if (_timer == 0)
			{
				if (_mem_arm[1] == SIGNAL_BREAK)
				{
					_mem_arm[0] = SIGNAL_REVERSE;
					_mem_arm[1] = SIGNAL_BREAK;
				}
				
				if (_mem_is_arm_sensor_on[1] == TRUE)
				{
					_mem_arm[0] = SIGNAL_BREAK;
					_mem_arm[1] = SIGNAL_REVERSE;
					
					_timer = GeneralTimer::Read() + GeneralTimer::Change_count_value(500);
				}
			}
			else if (GeneralTimer::Read() > _timer)
			{
				_mem_arm[1] = SIGNAL_BREAK;
				
				if (FALSE == (_mem_is_bumper_sensor_on[0] | _mem_is_bumper_sensor_on[1]))
				{
					_is_moved_arm = FALSE;
					
					_timer = 0;
					
					_sensor_place = Direc::CENTER;
				}
			}
		}
	}
}

//----------------------------------------------------------------------//

void Main :: Drive()
{	
	_mem_wheel.Want_to_use_steps(YES);
	
	if (_mem_is_turn_l | _mem_is_turn_r)
	{		
		_mem_wheel.Turning(_mem_is_doing_turn_r, _mem_is_doing_turn_l);
		
		if (_mem_is_enabled_reverse == FALSE)
		{
			_mem_time_to_allow_reverse = GeneralTimer::Read() + GeneralTimer::Change_count_value(120);
			
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
				
				_mem_wheel.Turning(_mem_is_doing_turn_l, _mem_is_doing_turn_r);
				
				_mem_wheel.Want_to_use_steps(NO);
			}
			
			_mem_is_enabled_reverse = FALSE;
		}
		else
		{
			_mem_wheel.Move();
		}
	}
}

//----------------------------------------------------------------------//

void Main :: Transmit()
{
	_mem_wheel.Transmit();
	
	_mem_up_down.Transmit();
	
	_mem_arm[0].Transmit();
	_mem_arm[1].Transmit();
}

//----------------------------------------------------------------------//

void Main :: Transmit_clear()
{
	_mem_wheel.Transmit_clear();
	
	_mem_up_down.Transmit_clear();
	
	_mem_arm[0].Transmit_clear();
	_mem_arm[1].Transmit_clear();
}

//----------------------------------------------------------------------//

void Main :: Display()
{
	if (_mem_is_turn_l)
	{
		LCD::Write(0x40, "Left  turn");
	}
	else if (_mem_is_turn_r)
	{
		LCD::Write(0x40, "Right turn");
	}
	else
	{
		switch (_mem_wheel.Get_direc_y())
		{
			case NORTH:		LCD::Write(0x40, "North ");	break;
			case SOUTH:		LCD::Write(0x40, "South ");	break;
			case CENTER_Y:	LCD::Write(0x40, "Cent  ");	break;
		}
		
		switch (_mem_wheel.Get_direc_x())
		{
			case EAST:		LCD::Write(0x46, "East");	break;
			case WEST:		LCD::Write(0x46, "West");	break;
			case CENTER_X:	LCD::Write(0x46, "Cent");	break;
		}
	}
	
	LCD::Write(0x4b, "PWM");
	LCD::Write(0x4e, _mem_wheel.Get_pwm(), 2, DECIMAL_10);
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
