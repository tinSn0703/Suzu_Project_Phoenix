
#include <MainCircit/MainCircit.h>

#include "Project3/Project3_define.h"
#include "Project3.h"

/************************************************************************/

namespace Project3
{

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	: MoveWheel(UART_NUM_1, 0)
	, BumperSensor()
	, MoveBelt(6, MoveWheel::Get_uart())
	, MoveRotation(5, MoveWheel::Get_uart(), UART_NUM_2)
	, MoveUpOrDown(4, MoveWheel::Get_uart())
	, MoveShoulder(7, MoveWheel::Get_uart())
	
	, _controller(UART_NUM_0)
{
	DDRA  = 0x0f;
	PORTA = 0x00;
	
	BumperSensor::Init(FRONT, IO_ADRS_F, 0, IO_ADRS_F, 1);
	BumperSensor::Init(RIGHT, IO_ADRS_F, 2, IO_ADRS_F, 3);
	BumperSensor::Init(LEFT , IO_ADRS_F, 4, IO_ADRS_F, 5);
	BumperSensor::Init(BACK	, IO_ADRS_F, 6, IO_ADRS_F, 7);
	
	_mem_direc = 'O';
	
	LCD_Init();
	
	LCD_Write_str(0x00, "Suzu Project3   ");
	LCD_Write_str(0x40, "Lock            ");
	
	_is_unlocked = NO;
}

//----------------------------------------------------------------------//

void Main :: Receive_operation()
{
	PORTA = 0x0f;
	
	_controller.Receive();
	
	BumperSensor::Read();
	
	MoveRotation::Read();
	
	if (_controller.Get_SELECT())
	{
		_is_unlocked = NO;
		
		LCD_Write_str(0x40, "Lock            ");
	}
	if (_controller.Get_START())
	{
		_is_unlocked = YES;
		
		LCD_Write_str(0x40, "                ");
	}
	
	PORTA = 0x00;
}

//----------------------------------------------------------------------//

void Main :: Operate()
{
	static YesNo _sta_is_enabled_auto_rot = NO;
	
	MoveWheel::Operate_move(_controller.Get_stick_Lx(), _controller.Get_stick_Ly());
	
	MoveWheel::Operate_turn(_controller.Get_L1(), _controller.Get_R1());
	
	MoveWheel::Operate_pwm(_controller.Push_Tri(), _controller.Push_Cro());
	
	MoveShoulder::Operate
	(
		((_controller.Get_stick_Rx() == Direc::WEST) ? YES : NO),
		((_controller.Get_stick_Rx() == Direc::EAST) ? YES : NO)
	);
	
	MoveBelt::Operate
	(
		((_controller.Get_cross_x() == Direc::WEST) ? YES : NO),
		((_controller.Get_cross_x() == Direc::EAST) ? YES : NO)
	);
	
	MoveUpOrDown::Operate
	(
		((_controller.Get_cross_y() == Direc::NORTH) ? YES : NO),
		((_controller.Get_cross_y() == Direc::SOUTH) ? YES : NO)
	);
	
	if (_controller.Get_L2() | _controller.Get_R2())
	{
		MoveRotation::Operate(_controller.Get_L2(), _controller.Get_R2());
		
		MoveRotation::Operate(OTHER);
	}
	else
	{
		MoveRotation::Operate(NO, NO);
		
		if (_sta_is_enabled_auto_rot)
		{
			switch (BumperSensor::Get_high_direction())
			{
				case FRONT:	MoveRotation::Operate(FRONT);	_mem_direc = 'F';	break;
				case RIGHT:	MoveRotation::Operate(RIGHT);	_mem_direc = 'R';	break;
				case BACK:	MoveRotation::Operate(BACK);	_mem_direc = 'B';	break;
				case LEFT:	MoveRotation::Operate(LEFT);	_mem_direc = 'L';	break;
				
				default:	break;
			}
			
			_sta_is_enabled_auto_rot = ~_controller.Push_L3();
		}
		else
		{
			MoveRotation::Operate(OTHER);
			
			_mem_direc = 'O';
			
			_sta_is_enabled_auto_rot = _controller.Push_L3();
		}
	}
}

//----------------------------------------------------------------------//

inline void Main :: Move()
{
	MoveWheel::Move();
	
	MoveBelt::Move();
	
	MoveRotation::Move();
	
	MoveUpOrDown::Move();
	
	MoveShoulder::Move();
}

//----------------------------------------------------------------------//

inline void Main :: Transmit()
{
	MoveWheel::Transmit();
	
	MoveBelt::Transmit();
	
	MoveRotation::Transmit();
	
	MoveUpOrDown::Transmit();
	
	MoveShoulder::Transmit();
}

//----------------------------------------------------------------------//

void Main :: Work()
{
	Main::Operate();
	
	Main::Move();
	
	Main::Transmit();
}

//----------------------------------------------------------------------//

void Main :: Stop()
{
	MoveWheel::Stop();
	
	MoveBelt::Transmit_clear();
	
	MoveRotation::Transmit_clear();
	
	MoveUpOrDown::Transmit_clear();
	
	MoveShoulder::Transmit_clear();
	
	_controller.Display_data(0x45);
}

//----------------------------------------------------------------------//

void Main :: Display()
{	
	LCD_Write_num(0x40, MoveRotation::Get_current_o(), 4, DECIMAL_10);
	LCD_Write_num(0x45, MoveRotation::Get_current_r(), 4, DECIMAL_10);
	LCD_Write_num(0x4a, MoveRotation::Get_current(), 4, DECIMAL_10);
	
	LCD_Write_char(0x4f, _mem_direc);
	
//	BumperSensor::Display(0x4c);
	
// 	LCD_Write_num(0x4a, MoveWheel::Get_direc_x(), 1, DECIMAL_16);
// 	LCD_Write_char(0x4b, ',');
// 	LCD_Write_num(0x4c, MoveWheel::Get_direc_y(), 1, DECIMAL_16);
// 	
// 	LCD_Write_num(0x4e, MoveWheel::Get_pwm(), 2, DECIMAL_10);
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
