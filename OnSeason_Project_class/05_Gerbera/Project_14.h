
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

#define PERSENT_CURVE 25	//カーブの度合い

#define TIME_MOVE_TYANPERA 200	//チャンペラを動かす時間

#define TIME_VALVE_CLOSE 10000	//電磁弁を閉じるまでの時間

#define PWM_TYANPERA 24
#define PWM_TYANPERA_STATE 2

/************************************************************************/

class Main
{
//variable
private:
	
	Controller::Bit24::WiiClassic _controller;
	
	Mechanum _wheel;
	
	/* パックマン(いわゆる四点バースト) */
	PackMan _pack_man;
	
	/* パックマンを立ち上げる際の時間計測用の変数 */
	CountValue _timer_pack_man_stand;
	
	/* ムチみたいなやつを動かすモーター */
	Motor _motor_tyanpera;
	
	Uart::ModeTransmit _uart_valve;
	
	ValveSingle _valve_rod;
	
	YesNo _is_move_front	:1;	//前に動きます?
	YesNo _is_move_back		:1;	//後ろに動きます?
	YesNo _is_move_left		:1;	//左に動きます?
	YesNo _is_move_right	:1;	//右に動きます?
	
	/* 動作はロックされていますか? */
	YesNo _is_movement_lock :1;
	
	/* マシンの初期設定中ですか? */
	YesNo _is_machine_init :1;
	
	/* パックマンからチャンペラをどけますか? */
	YesNo _is_remove_tyanpera :1;
	
	/* 通信エラーが発生しましたか? */
	YesNo _is_error_happen :1;
	
	/* LCDの表示を切り替えてもいいですか? */
	YesNo _is_enable_change_display :1;
	
	/* LCDの表示を選択するための変数 */
	uByte _count_lcd :3;
	
//function
private:
	
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
	
	/* チャンペラを動かす処理 */
	void Move_tyanpera(DirectionY _move);
	
	/* チャンペラとパックマンを一体で動かす処理 */
	void Move_tyanpera_and_pack_man();
	
	/* 電磁弁を操作する処理 */
	void Move_valve();
	
	/* ロック時のLCDの表示 */
	void Display_lock_mode();
	
	/* 動作時のLCDの表示 */
	void Display_unlock_mode();
	
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
