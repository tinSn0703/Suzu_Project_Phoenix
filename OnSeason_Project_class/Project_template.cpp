
/*************************************************************************
  プロジェクトのテンプレート。 実装。
*************************************************************************/

#include <MainCircit/MainCircit.h>

#include "Project_template.h"

/************************************************************************/

namespace Template
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
{
	LCD::Initialize();
	
	INIT_LED();
	
	_is_movement_lock = YES;
	
	LCD::Write(0x00, "xxx             ");
	LCD::Write(0x40, "                ");
}

//----------------------------------------------------------------------//

void Main :: Input()
{
	_controller.Read();
}

//----------------------------------------------------------------------//

void Main :: Work_wheel()
{
	_wheel.Set_move_direction(_controller.Get_L_stick_x(), _controller.Get_L_stick_y());
	
	_wheel.Set_turn_direction(_controller.Get_L1(), _controller.Get_R1());
	
	if (_wheel.Is_move())
	{
		_wheel.Curve(75);
	}
	else
	{
		_wheel.SpinTurn();
	}
}

//----------------------------------------------------------------------//

void Main :: Process()
{
	if (_controller.Get_SELECT())	_is_movement_lock = YES;
	if (_controller.Get_START())	_is_movement_lock = NO;
	
	if (_is_movement_lock == NO)
	{
		Work_wheel();
	}
}

//----------------------------------------------------------------------//

void Main :: Output()
{
	if (_is_movement_lock)
	{
		if (PORT_LED == LED_STATE_UNLOCK)
		{
			LCD::Write(0x40, "       Lock Mode");
			
			PORT_LED = LED_STATE_LOCK;
		}
	}
	else
	{
		if (PORT_LED == LED_STATE_LOCK)
		{
			LCD::Clear_under();
			
			PORT_LED = LED_STATE_UNLOCK;
		}
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}

/************************************************************************/
