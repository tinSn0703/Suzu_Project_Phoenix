
#pragma once

/************************************************************************/

namespace Three
{

enum WheelPlace
{
	FRONT	= 0,
	RIGHT	= 1,
	LEFT	= 2,
};

};

/************************************************************************/

class ThreeOmuni	: public Wheel
{
public:
	
	ThreeOmuni(MotorNumber _min_number, UartNum _uart_num);
	
	void Set_wheel_place(Three::WheelPlace _place, MotorNumber _number);
	
	void Turning();
	void Turning(YesNo _is_turn_l, YesNo _is_turn_r);
	
	void Move();
	void Move(DirecX _direc_x, DirecY _direc_y);
	
	Motor & operator [] (Three::WheelPlace _place);
};

/************************************************************************/

//----------------------------------------------------------------------//

inline void ThreeOmuni :: Set_wheel_place
(
	const Three::WheelPlace	_place, 
	const MotorNumber		_number
)
{
	_mem_md[_place].Reset(_number);
}

//----------------------------------------------------------------------//

inline void ThreeOmuni::Turning(const YesNo _is_turn_l, const YesNo _is_turn_r)
{
	Wheel::Set_turn(_is_turn_l, _is_turn_r);
	
	ThreeOmuni::Turning();
}

//----------------------------------------------------------------------//

inline void ThreeOmuni :: Move(const DirecX _direc_x, const DirecY _direc_y)
{
	Wheel::Set_direc(_direc_x, _direc_y);
	
	ThreeOmuni::Move();
}

//----------------------------------------------------------------------//

inline Motor & ThreeOmuni :: operator [](Three::WheelPlace _place)
{
	return MDC::operator []((MotorNumber)_place);
}

//----------------------------------------------------------------------//

/************************************************************************/

