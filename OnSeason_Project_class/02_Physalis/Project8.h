
#pragma once

/************************************************************************/
/*	200 : ìÒçÜã@êeã@													*/
/************************************************************************/

namespace Physalis
{

namespace Kerberos_chan
{

/************************************************************************/

class Main
{
//variable
private:
	
	Controller::Bit24::Dualshock2AddPush _controller;
	
	ThreeOmuni _wheel;
	
	Uart::ModeTransmit _uart_valve;
	
	ValveSingle _valve_catapult_trigger;
	
	ValveSingle _valve_gun_trigger_Veni; //óàÇΩ
	ValveSingle _valve_gun_trigger_Vidi; //å©ÇΩ
	ValveSingle _valve_gun_trigger_Vici; //èüÇ¡ÇΩ
	
	YesNo _is_tirgger_release :1;
	
	YesNo _is_movement_lock :1;
	
//function
private:
	
	void Display_init();
	
	void Control_fire();
	
	void Move();
	
public:
	
	Main();
	
	void Receive_operation();
	
	YesNo Is_movement_lock();
	
	void Work();
	
	void Display();
	
	void Stop();	
	
};

/************************************************************************/

}

}

/************************************************************************/
