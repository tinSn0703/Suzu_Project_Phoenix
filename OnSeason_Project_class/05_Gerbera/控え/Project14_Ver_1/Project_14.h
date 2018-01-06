
/*************************************************************************

520 万里 全国大会仕様

*************************************************************************/

#pragma once

/************************************************************************/

namespace Gerbera
{

namespace BanriFinal
{

/************************************************************************/

#define PERSENT_CURVE 25

#define LEFT_OVER	0
#define LEFT_UNDER	1
#define RIGHT_OVER	2
#define RIGHT_UNDER	3

#define MOVE_LEFT	BTN_Y
#define MOVE_RIGHT	BTN_A
#define MOVE_FRONT	BTN_X
#define MOVE_BACK	BTN_B

#define PWM_PACK_MAN_OVER	16
#define PWM_PACK_MAN_UNDER	10

/************************************************************************/

class Main
{
//variable
private:
	
	Bit24::WiiClassic _controller;
	
	Mechanum _wheel;
	
	Motor _motor_tentacles;
	
	Motor _motor_pack_man_stand;
	
	MotorRotationOnly _motor_pack_man_arm[4];
	
	Uart::ModeTransmit _uart_valve;
	
	ValveSingle _valve_rod;
	
	LimitSensor _limit_stand_over;
	LimitSensor _limit_stand_under;
	
	LimitSensor _limit_arm_stretch[4];
	LimitSensor _limit_arm_shorten[4];
	
	/* 動作はロックされていますか? */
	YesNo _is_movement_lock :1;
	
	YesNo _is_remove_tentacles :1;
	
	YesNo _is_stand_move_over  :1;
	YesNo _is_stand_move_under :1;
	
	CountValue _timer_pack_man_stand;
	
//function
private:
	
	void Set_wheel_turn();
	
	void Move_wheel_right();
	void Move_wheel_left();
	
	void Move_wheel_front();
	void Move_wheel_back();
	
	void Move_wheel();
	
	void Move_pack_man_arm(YesNo _is_stretch, YesNo _is_shorten);
	
	void Move_pack_man_arm(DirectionY _move);
	
	void Move_pack_man_stand();
	
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
