
/*************************************************************************
  510 5号機 マシン2(一空)
*************************************************************************/

#pragma once

/************************************************************************/

namespace Gerbera
{

namespace Ikku
{

/************************************************************************/

class Main
{
//variable
private:
	
	Controller::Bit24::WiiClassicAddPush _controller;
	
	Mechanum _wheel;
	
	DirectionX _memory_direc_x :2;
	DirectionY _memory_direc_y :2;
	
	YesNo _memory_is_turn_l :1;
	YesNo _memory_is_turn_r :1;
	
	Pwm _memory_pwm :5;
	
	Uart::ModeTransmit _uart_valve;
	
	ValveSingle _valve_trigger;
	
	ValveSingle _valve_parge;
	
	/* 動作はロックされていますか? */
	YesNo _is_movement_lock :1;
	
//function
private:
	
	void Work_wheel();
	
public:
	
	Main();
	
	/* main回路への入力 */
	void Input();
	
	/* 入力の処理。出力への変換 */
	void Process();
	
	/* 他回路などへの出力 */
	void Output();
};

/************************************************************************/

}

}

/************************************************************************/
