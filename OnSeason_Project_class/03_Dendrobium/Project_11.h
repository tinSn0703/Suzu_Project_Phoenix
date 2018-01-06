
/*************************************************************************
  300 3���@ �e�@
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

#define TIME_ROD_OPEN 1500	//�Ƃ̃G�A�̊J������ [ms]

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
	
	/* ����̓��b�N����Ă��܂���? */
	YesNo _is_movement_lock :1;
	
//function
private:
	
	/* �����̓��� */
	void Work_wheel();
		
	/* Motor�̓��� */
	void Work_motor();
	
	/* �d���ق̓��� */
	void Work_valve();
	
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
