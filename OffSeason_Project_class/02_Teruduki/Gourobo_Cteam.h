/*
 * Gourobo_Cteam.h
 *
 * Created: 2018/01/13 12:35:00
 *  Author: FUJITSU
 */ 

#pragma once

#include <MainCircit/MainCircit.h>

/************************************************************************/

namespace Off2017
{
namespace Teruduki
{
namespace Gourobo_Cteam
{

#define PERSENT_CURVE 25	//カーブの度合い

/************************************************************************/

class Main
{
//variables
private:
	
	Controller::Bit24::WiiClassic _controller;
	
	Mechanum _wheel;
	
	Motor _motor_arm_raise;
	
	Motor _motor_arm_thrust;
	
	Uart::ModeTransmit _uart_valve;
	
	ValveDouble _valve_thrust;
	
	YesNo _is_move_front	:1;	//前に動きます?
	YesNo _is_move_back		:1;	//後ろに動きます?
	YesNo _is_move_left		:1;	//左に動きます?
	YesNo _is_move_right	:1;	//右に動きます?
	
	/* マシンの初期設定中ですか? */
	YesNo _is_machine_init :1;
	
	/* 通信エラーが発生しましたか? */
	YesNo _is_error_happen :1;
	
	YesNo _is_movement_lock :1;
	
//functions
public:
	
	Main();
	
	void Input();
	
	void Process();
	
	void Output();
	
private:
	
	void Dispaly_init();
	
	/* 受信の異常、もしくはコントローラからの操作でマシンの動作をロックする処理 */
	void Lock();
	
	/* マシンのロックを解除する処理 */
	void Unlock();
	
	/* マシンの旋回方向を設定する処理 */
	void Set_wheel_turn();
	
	/* 右側に移動するための処理 */
	void Move_wheel_right();
	
	/* 左側に移動するための処理 */
	void Move_wheel_left();
	
	/* 前方に移動するための処理 */
	void Move_wheel_front();
	
	/* 後方に移動するための処理 */
	void Move_wheel_back();
	
	/* 旋回するための処理 */
	void Move_wheel_turn();
	
	/* 移動するための処理 */
	void Move_wheel();
};

/************************************************************************/

};
};
};

/************************************************************************/