
/*************************************************************************
  300 3号機 親機
*************************************************************************/

#pragma once

/************************************************************************/

namespace Dendrobium
{

namespace Master
{

/************************************************************************/

#define PWM_WHEEL_HIGH		31
#define PWM_WHEEL_NORMAL	15
#define PWM_WHEEL_LOW		 5

#define PWM_MOTOR	15

#define WHEEL_CURVE_PERSENT 75

#define TIME_ROD_OPEN 1500	//竿のエアの開放時間 [ms]

/************************************************************************/

class Main
{
//variable
private:
	
	Controller::Bit24::Dualshock2 _controller;
	
	FourWheel _wheel;
	
	Motor _motor_gun_angle;
	
	Motor _motor_slave_move;
	
	Uart::ModeTransmit _uart_valve;
	
	ValveSingle _valve_fire;
	
	ValveSingle _valve_rod;
	
	ValveSingle _valve_stopper;
	
	/* 動作はロックされていますか? */
	YesNo _is_movement_lock :1;
	
//function
private:
	
	/* 足回りの動作 */
	void Work_wheel();
		
	/* Motorの動作 */
	void Work_motor();
	
	/* 電磁弁の動作 */
	void Work_valve();
	
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
