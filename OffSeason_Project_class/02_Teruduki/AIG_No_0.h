/* 
* AIG.h
*
* Created: 2017/12/19 16:29:02
* Author: conde_000
*
* ïîì‡ÉçÉ{ÉRÉì íÜí√î« AIG 0çÜ
*/


#pragma once

#include <MainCircit/MainCircit.h>

/************************************************************************/

namespace Off2017
{
namespace Teruduki
{
namespace AIG_No_0
{

/************************************************************************/

class Main
{
//variables
private:
	
	Controller::Bit24::WiiClassic _controller;
	
	FourOmuni _wheel;
	
	LimitSensor _limit_nock;
	
	Uart::ModeTransmit _uart_valve_1;
	
	ValveDouble _valve_fall_feed_fall_zone;
	
	ValveDouble _valve_fall_feed_wait_zone;
	
	Uart::ModeTransmit _uart_valve_2;
	
	ValveDouble _valve_gun_trigger;
	
	ValveDouble _valve_fall_support;
	
	ValveSingle _valve_fall_stretch;
	
	CountValue _timer_gun;
	
	YesNo _is_movement_lock :1;
	
//functions
public:
	
	Main();
	
	void Input();
	
	void Process();
	
	void Output();
	
private:
	
	void Fall();
	
	void Fire();
	
	void Move_right();
	
	void Move_left();
	
	void Move_lenghways();
	
	void Move_wheel();
};

/************************************************************************/

};
};
};

/************************************************************************/
