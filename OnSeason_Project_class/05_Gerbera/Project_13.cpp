
#include <MainCircit/MainCircit.h>

#include "Project_13.h"

/************************************************************************/

namespace Gerbera
{

namespace Banri
{

/************************************************************************/

#define INIT_LED()	DDRA = 0xff; PORTA = 0x00

#define PORT_LED	PORTA

#define LED_STATE_LOCK		0x00
#define LED_STATE_UNLOCK	0x0f

#define STR_PROJECT_NAME "500      Gerbera"
#define STR_MACHINE_NAME "         FarAway"

/************************************************************************/

//----------------------------------------------------------------------//

Main :: Main()

	: _controller(Uart::NUM_0)
	
	, _wheel(Uart::NUM_1)
{
	LCD::Write(0x00, STR_PROJECT_NAME, 75);
	LCD::Write(0x40, STR_MACHINE_NAME);
	
	INIT_LED();
	
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
}

//----------------------------------------------------------------------//

void Main :: Process()
{
	if (_controller.Push_START())	_is_movement_lock = NO;
	if (_controller.Push_SELECT())	_is_movement_lock = YES;
	
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
		_wheel.Write();
		
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

}

/************************************************************************/
