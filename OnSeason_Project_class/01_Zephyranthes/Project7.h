
#pragma once

/************************************************************************/
/*	102 : ééçÏàÍçÜã@ éqã@(éUíeèeìãç⁄)									*/
/************************************************************************/

namespace Zephyranthes
{

namespace Shotgun
{

/************************************************************************/

class Main
{
//variable
private:
	
	Controller::Bit24::Dualshock2 _controller;
	
	Uart::ModeTransmit _uart_motor;
	
	Motor _motor_widch;
	
	Motor _motor_turn;
	
	Uart::ModeTransmit _uart_valve;
	
	ValveSingle _valve_transform;
	
	ValveSingle _valve_stopper;
	
	ValveSingle _valve_trigger;
	
	PhotoSensor _check_enemy_line;
	
	CountValue _timer_transform;
	
	YesNo _is_movement_lock :1;
	
	YesNo _is_transform_enable :1;
	
	YesNo _is_lcd_change :1;
	
	UartData8bit _before_valve_data :8;
	
//function
private:
	
	void Move_glide_mode();
	
	void Move_bombard_mode();
	
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
