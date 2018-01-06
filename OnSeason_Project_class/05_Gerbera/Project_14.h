
/*************************************************************************

520 ���� �S�����d�l

*************************************************************************/

#pragma once

#include "Project14/PackMan.h"

/************************************************************************/

namespace Gerbera
{

namespace BanriFinal
{

/************************************************************************/

#define PERSENT_CURVE 25	//�J�[�u�̓x����

#define TIME_MOVE_TYANPERA 200	//�`�����y���𓮂�������

#define TIME_VALVE_CLOSE 10000	//�d���ق����܂ł̎���

#define PWM_TYANPERA 24
#define PWM_TYANPERA_STATE 2

/************************************************************************/

class Main
{
//variable
private:
	
	Controller::Bit24::WiiClassic _controller;
	
	Mechanum _wheel;
	
	/* �p�b�N�}��(������l�_�o�[�X�g) */
	PackMan _pack_man;
	
	/* �p�b�N�}���𗧂��グ��ۂ̎��Ԍv���p�̕ϐ� */
	CountValue _timer_pack_man_stand;
	
	/* ���`�݂����Ȃ�𓮂������[�^�[ */
	Motor _motor_tyanpera;
	
	Uart::ModeTransmit _uart_valve;
	
	ValveSingle _valve_rod;
	
	YesNo _is_move_front	:1;	//�O�ɓ����܂�?
	YesNo _is_move_back		:1;	//���ɓ����܂�?
	YesNo _is_move_left		:1;	//���ɓ����܂�?
	YesNo _is_move_right	:1;	//�E�ɓ����܂�?
	
	/* ����̓��b�N����Ă��܂���? */
	YesNo _is_movement_lock :1;
	
	/* �}�V���̏����ݒ蒆�ł���? */
	YesNo _is_machine_init :1;
	
	/* �p�b�N�}������`�����y�����ǂ��܂���? */
	YesNo _is_remove_tyanpera :1;
	
	/* �ʐM�G���[���������܂�����? */
	YesNo _is_error_happen :1;
	
	/* LCD�̕\����؂�ւ��Ă������ł���? */
	YesNo _is_enable_change_display :1;
	
	/* LCD�̕\����I�����邽�߂̕ϐ� */
	uByte _count_lcd :3;
	
//function
private:
	
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
	
	/* �`�����y���𓮂������� */
	void Move_tyanpera(DirectionY _move);
	
	/* �`�����y���ƃp�b�N�}������̂œ��������� */
	void Move_tyanpera_and_pack_man();
	
	/* �d���ق𑀍삷�鏈�� */
	void Move_valve();
	
	/* ���b�N����LCD�̕\�� */
	void Display_lock_mode();
	
	/* ���쎞��LCD�̕\�� */
	void Display_unlock_mode();
	
public:
	
	Main();
	
	/* main��H�ւ̓��� */
	void Input();
	
	/* ���͂̏����B�o�͂ւ̕ϊ� */
	void Process();
	
	/* ����H�Ȃǂւ̏o�� */
	void Output();
};

/************************************************************************/

}
}

/************************************************************************/
