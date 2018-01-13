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

#define PERSENT_CURVE 25	//�J�[�u�̓x����

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
	
	YesNo _is_move_front	:1;	//�O�ɓ����܂�?
	YesNo _is_move_back		:1;	//���ɓ����܂�?
	YesNo _is_move_left		:1;	//���ɓ����܂�?
	YesNo _is_move_right	:1;	//�E�ɓ����܂�?
	
	/* �}�V���̏����ݒ蒆�ł���? */
	YesNo _is_machine_init :1;
	
	/* �ʐM�G���[���������܂�����? */
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
	
	/* ��M�ُ̈�A�������̓R���g���[������̑���Ń}�V���̓�������b�N���鏈�� */
	void Lock();
	
	/* �}�V���̃��b�N���������鏈�� */
	void Unlock();
	
	/* �}�V���̐��������ݒ肷�鏈�� */
	void Set_wheel_turn();
	
	/* �E���Ɉړ����邽�߂̏��� */
	void Move_wheel_right();
	
	/* �����Ɉړ����邽�߂̏��� */
	void Move_wheel_left();
	
	/* �O���Ɉړ����邽�߂̏��� */
	void Move_wheel_front();
	
	/* ����Ɉړ����邽�߂̏��� */
	void Move_wheel_back();
	
	/* ���񂷂邽�߂̏��� */
	void Move_wheel_turn();
	
	/* �ړ����邽�߂̏��� */
	void Move_wheel();
};

/************************************************************************/

};
};
};

/************************************************************************/