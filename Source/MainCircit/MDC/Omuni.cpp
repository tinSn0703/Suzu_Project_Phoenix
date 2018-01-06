
#include <math.h>

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/AVR.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>
#include <MainCircit/MDC/Wheel.h>
#include <MainCircit/MDC/Omuni.h>

#define PI_DIV_4 0.785398163

/************************************************************************/
/*	OmuniDiagonal														*/
/************************************************************************/

//----------------------------------------------------------------------//

OmuniDiagonal :: OmuniDiagonal(const MotorNumber _min_num, const UartNum _uart_num)

	: FourWheel(_min_num, _uart_num)
{}

//----------------------------------------------------------------------//

void OmuniDiagonal :: Move()
{
	const uByte _front	= (_mem_is_invert_x ? Reversal_DirecX(_mem_direc_x) : _mem_direc_x);
	const uByte _back	= (_mem_is_invert_x ? _mem_direc_x : Reversal_DirecX(_mem_direc_x));
	
	const uByte _right	= (_mem_is_invert_y ? _mem_direc_y : Reversal_DirecY(_mem_direc_y));
	const uByte _left	= (_mem_is_invert_y ? Reversal_DirecY(_mem_direc_y) : _mem_direc_y);
	
	_mem_md[Four::FRONT_RIGHT	]	= (To_Signal(_front	& _right));
	_mem_md[Four::BACK_RIGHT	]	= (To_Signal(_back	& _right));
	_mem_md[Four::BACK_LEFT		]	= (To_Signal(_back	& _left));
	_mem_md[Four::FRONT_LEFT	]	= (To_Signal(_front	& _left));
}

//----------------------------------------------------------------------//

void OmuniDiagonal :: Move(double _rad)
{
	_rad -= PI_DIV_4;
	
	_mem_md[Four::FRONT].Set_from_pwm(MDC::Get_pwm() * +sin(_rad));
	_mem_md[Four::RIGHT].Set_from_pwm(MDC::Get_pwm() * -cos(_rad));
	_mem_md[Four::BACK ].Set_from_pwm(MDC::Get_pwm() * -sin(_rad));
	_mem_md[Four::LEFT ].Set_from_pwm(MDC::Get_pwm() * +cos(_rad));
	
	if (_mem_md[Four::FRONT].Get_pwm() == _mem_md[Four::RIGHT].Get_pwm())
	{
		MDC::Set(MDC::Get_pwm());
	}
}

//----------------------------------------------------------------------//

void OmuniDiagonal :: Move_or_Turning()
{
	if (Wheel::Is_turn_l() | Wheel::Is_turn_r())
	{
		FourWheel::Turning();
	}
	else
	{
		OmuniDiagonal::Move();
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	OmuniOpposite														*/
/************************************************************************/

//----------------------------------------------------------------------//

OmuniOpposite :: OmuniOpposite(MotorNumber _min_num, UartNum _uart_num)

	: FourWheel(_min_num, _uart_num)
{}

//----------------------------------------------------------------------//

void OmuniOpposite :: Move()
{
	//2017 4/5
	//ちゃんと動くかわかってないのでチェックを忘れないでください
	
	_mem_md[Four::FRONT] = To_Signal(_mem_is_invert_x ? _mem_direc_x : Reversal_DirecX(_mem_direc_x));
	_mem_md[Four::RIGHT] = To_Signal(_mem_is_invert_y ? Reversal_DirecY(_mem_direc_y) : _mem_direc_y);
	_mem_md[Four::BACK]  = To_Signal(_mem_is_invert_x ? Reversal_DirecX(_mem_direc_x) : _mem_direc_x);
	_mem_md[Four::LEFT]  = To_Signal(_mem_is_invert_y ? _mem_direc_y : Reversal_DirecY(_mem_direc_y));
}

//----------------------------------------------------------------------//

void OmuniOpposite :: Move(const double _rad)
{
	_mem_md[Four::FRONT].Set_from_pwm(MDC::Get_pwm() * +sin(_rad));
	_mem_md[Four::RIGHT].Set_from_pwm(MDC::Get_pwm() * -cos(_rad));
	_mem_md[Four::BACK ].Set_from_pwm(MDC::Get_pwm() * -sin(_rad));
	_mem_md[Four::LEFT ].Set_from_pwm(MDC::Get_pwm() * +cos(_rad));
	
	if (_mem_md[Four::FRONT].Get_pwm() == _mem_md[Four::RIGHT].Get_pwm())
	{
		MDC::Set(MDC::Get_pwm());
	}
}

//----------------------------------------------------------------------//

void OmuniOpposite :: Move_or_Turning()
{
	if (Wheel::Is_turn_l() | Wheel::Is_turn_r())
	{
		FourWheel::Turning();
	}
	else
	{
		OmuniOpposite::Move();
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
