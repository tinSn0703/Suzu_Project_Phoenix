
/*************************************************************************
  510 5���@ �}�V��2(���)
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
	
	/* ����̓��b�N����Ă��܂���? */
	YesNo _is_movement_lock :1;
	
//function
private:
	
	void Work_wheel();
	
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
