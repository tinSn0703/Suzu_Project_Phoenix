
#pragma once

/************************************************************************/

/*
UART
	
	BT	-> UART0
	MDC -> UART1

モータの接続

	MD0 -> みぎ		まえ
	MD1 -> ひだり	まえ
	MD2 -> ひだり	うしろ
	MD3	-> みぎ		うしろ
	
	MD4 -> 上下昇降

操縦方法
	
	十字キー上下 -> 上下昇降
	
	左スティック -> マシンの移動
	L1 -> 左旋回
	R1 -> 右旋回
	
	L2 -> PWM + 1
	R2 -> PWM - 1
*/

namespace Project1
{

/************************************************************************/

class Main
{
private:
	
	Dualshock2 _mem_controller;
	
	Mechanum _mem_wheel;
	
	Motor _mem_up_down;
	
	BOOL _mem_is_enabeld_move :1;
	
	BOOL _mem_is_enabled_reverse :1;
	
	Btn _mem_is_doing_turn_r :1;
	Btn _mem_is_doing_turn_l :1;
	
	CountValue _mem_time_to_allow_reverse;
	
	BOOL _mem_is_pwm_up :1;
	BOOL _mem_is_pwm_down :1;
	
	BOOL _mem_is_turn_l :1;
	BOOL _mem_is_turn_r :1;
	
	DirecY _mem_move_up_down :2;
	
	BOOL _mem_is_bumper_sensor_on[2];
	
	BOOL _mem_is_arm_sensor_on[2];
	
	LimitSensor _mem_bumper_sensor[2];
	
	LimitSensor _mem_arm_0_sensor[2];
	LimitSensor _mem_arm_1_sensor[2];
	
	Motor _mem_arm[2];
	
	void Count_pwm();
	
	void Shift_view();
	
	void Move_up_down();
	
	void Drive();
	
	void Move_arm();
	
	
public:
	
	Main();
	
	YesNo Is_unlocked();
	
	void Receive();
	
	void Doing();
	
	void Transmit();
	
	void Transmit_clear();
	
	void Display();
};

/************************************************************************/

};

/************************************************************************/
