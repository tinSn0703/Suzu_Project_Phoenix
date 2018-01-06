#pragma once

/************************************************************************/
/*	210 : 二号機子機(ショットガン搭載)									*/
/************************************************************************/

namespace Physalis
{

namespace OneWayTicket
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
	
	ValveSingle _valve_stopper;
	
	ValveSingle _valve_trigger;
	
	PhotoSensor _check_enemy_line;
	
	YesNo _is_movement_lock :1;
	
	YesNo _is_lcd_change :1;
	
	UartData8bit _past_valve_data :8;
	
//function
private:
	
	void Display_init();
	
	void Move_glide_mode();
	
	void Move_bombard_mode();
	
public:
	
	Main();
	
	void Receive_operation();
	
	YesNo Is_movement_enable();
	
	void Work();
	
	void Display();
	
	void Stop();
};

/************************************************************************/

}

}

/************************************************************************/