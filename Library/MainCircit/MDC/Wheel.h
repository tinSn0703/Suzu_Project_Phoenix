

#pragma once

typedef enum
{
	FRONT_WHEEL = 0,
	RIGHT_WHEEL = 0,
	LEFT_WHEEL	= 0,
	BACK_WHEEL	= 0,
	
	FRONT_RIGHT	= 0, 
	BACK_RIGHT	= 1,
	BACK_LEFT	= 2,
	FRONT_LEFT	= 3
}
WheelPlace;

class Wheel : protected MDC
{
protected:
	
	DirecX _mem_direc_x :2;
	DirecY _mem_direc_y :2;
	
	BOOL _is_invert_x :1;
	BOOL _is_invert_y :1;
	
public:
	
	Wheel(MdcNum _mdc_num, UartNum _uart_num);
	
	void Swap_wheel_place(WheelPlace _place_0, WheelPlace _place_1);
	
	void Want_invert_Xoperate(YesNo _yes_no);
	void Want_invert_Yoperate(YesNo _yes_no);
	
	void Set(DirecX _direc);
	void Set(DirecY _direc);
	void Set(DirecX _direc_x, DirecY _direc_y);
	
	DirecX Get_direc_x();
	DirecY Get_direc_y();
	
	void Shift_45deg();
	void Shift_90deg();
	
	void Set_pwm(Pwm _pwm);
	
	void Turning(BOOL _is_right, BOOL _is_left);
	
	void Drive_front_or_back();
	void Drive_front_or_back(DirecY _direc);
	
	void Transmit();
	void Transmit(UartTransmit &_uart);
	
	Motor & operator [] (WheelPlace _place);
};

#include "Wheel_inline.h"
