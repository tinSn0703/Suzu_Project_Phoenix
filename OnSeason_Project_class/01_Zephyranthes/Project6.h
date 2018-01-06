
#pragma once

/************************************************************************/
/*	110 : ééçÏàÍçÜã@ êeã@												*/
/************************************************************************/

namespace Zephyranthes
{

namespace Catapult
{

/************************************************************************/

class Main
{
//variable
private:
	
	Controller::Bit24::Dualshock2AddPush _controller;
	
	ThreeOmuni _wheel;
	
	ValveSingle _catapult_lock;
	
	Uart::ModeTransmit _uart_valve;
	
	YesNo _is_catapult_enable :1;
	
	YesNo _is_lcd_change :1;
	
	YesNo _is_movement_lock :1;
	
//function
private:
	
	void Move_wheel();
	
	void Move_catapult();
	
	void Display();
	
	void Stop();
	
public:
	
	Main();

	void Input();
	
	void Process();
	
	void Output();
};

/************************************************************************/

}

}

/************************************************************************/
