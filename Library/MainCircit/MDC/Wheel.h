
#pragma once

/************************************************************************/

namespace Four
{

enum WheelPlace
{
	FRONT	= 0,
	RIGHT	= 1,
	BACK	= 2,
	LEFT	= 3,
	
	FRONT_RIGHT	= 0,
	BACK_RIGHT	= 1,
	BACK_LEFT	= 2,
	FRONT_LEFT	= 3
};

};

/************************************************************************/

class Wheel : public MDC
{
protected:
	
	DirecX _mem_direc_x :2;
	DirecY _mem_direc_y :2;
	
	YesNo _mem_is_invert_x :1;
	YesNo _mem_is_invert_y :1;
	
	BOOL _mem_is_turn_l :1;
	BOOL _mem_is_turn_r :1;
	
public:
	
	Wheel(MotorNumber _min_number, UartNum _uart_num, Byte _num_wheel);
	
	void Want_to_invert_DirecX(YesNo _yes_no);
	void Want_to_invert_DirecY(YesNo _yes_no);
	
	void Set_direc(DirecX _direc);
	void Set_direc(DirecY _direc);
	void Set_direc(DirecX _direc_x, DirecY _direc_y);
	
	void Set_turn(YesNo _is_turn_l, YesNo _is_turn_r);
	
	DirecX Get_direc_x();
	DirecY Get_direc_y();
	
	YesNo Is_turn_r();
	YesNo Is_turn_l();
	
	YesNo Is_moved();
	
	void Shift_45deg();
	void Shift_90deg();
};

/************************************************************************/

class FourWheel : public Wheel
{
public:
	
	FourWheel(MotorNumber _min_number, UartNum _uart_num);
	
	void Set_wheel_place(Four::WheelPlace _place, MotorNumber _number);
	
	void Turning();
	void Turning(YesNo _is_turn_l, YesNo _is_turn_r);
	
	void Move_front_or_back();
	void Move_front_or_back(DirecY _direc);
	
	Motor & operator [] (Four::WheelPlace _place);
};

/************************************************************************/

#include "Wheel_inline.h"
