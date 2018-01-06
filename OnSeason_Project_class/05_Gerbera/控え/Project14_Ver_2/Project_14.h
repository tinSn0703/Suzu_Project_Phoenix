
/*************************************************************************

520 万里 全国大会仕様

*************************************************************************/

#pragma once

#include "Project14/PackMan.h"

/************************************************************************/

namespace Gerbera
{

namespace BanriFinal
{

/************************************************************************/

#define PERSENT_CURVE 25

#define MOVE_LEFT	BTN_Y
#define MOVE_RIGHT	BTN_A
#define MOVE_FRONT	BTN_X
#define MOVE_BACK	BTN_B

/************************************************************************/

class Main
{
//variable
private:
	
	Bit24::WiiClassic _controller;
	
	Mechanum _wheel;
	
	PackMan _pack_man;
	
	Motor _motor_tentacles;
	
	Uart::ModeTransmit _uart_valve;
	
	ValveSingle _valve_rod;
	
	/* 動作はロックされていますか? */
	YesNo _is_movement_lock :1;
	
	YesNo _is_remove_tentacles :1;
	
	CountValue _timer_pack_man_stand;
	
//function
private:
	
	void Set_wheel_turn();
	
	void Move_wheel_right();
	void Move_wheel_left();
	
	void Move_wheel_front();
	void Move_wheel_back();
	
	void Move_wheel();
	
	void Move_tentacles(DirectionY _move);
	
	void Move_tentacles_and_pack_man();
	
	void Move_valve();
	
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
