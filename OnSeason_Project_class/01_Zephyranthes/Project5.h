
#pragma once

/************************************************************************/
/*	101 : ééçÏàÍçÜã@ éqã@												*/
/************************************************************************/

namespace Zephyranthes
{

namespace Warhead
{

/************************************************************************/

#define PWM_STAND_MOVE 10
#define PWM_STAND_STOP  4

#define OPEN_TIME_VALVE_0 300//[ms]
#define OPEN_TIME_VALVE_1 300//[ms]
#define OPEN_TIME_VALVE_2 300//[ms]
#define OPEN_TIME_VALVE_3 300//[ms] 

/************************************************************************/

class Main
{
//variable
private:

	Controller::Bit24::Dualshock2 _controller;

	ThreeOmuni _wheel;
	
	Motor _motor_stand;

	ValveSingle _rod[4];
	
	Uart::ModeTransmit _uart_rod;
	
	YesNo _is_movement_lock :1;
	
	CountValue _mem_timer[4];
	
	YesNo _mem_is_enabled_pwm_up;
	YesNo _mem_is_enabled_pwm_down;

	YesNo _mem_is_enabled_move_rod;

//function
private:
	
	void Count_wheel_pwm(YesNo _is_up, YesNo _is_down);
	
	void Transformation(YesNo _is_stand, YesNo _is_lie);
	
	void Stretch_rod(uByte _number, mSecond _count_time);
	
	void Stop_rod(uByte _number);
	
	void Set_rod_permission();
	
	void Attack(YesNo _is_rod_stretch);
	
	void Display();
	
public:
	
	Main();
	
	void Input();
	
	void Process();
	
	void Output();
};

/************************************************************************/

};

};

/************************************************************************/
