
#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline void Wheel :: Want_to_invert_DirecX(const YesNo _yes_no)
{
	_mem_is_invert_x = _yes_no;
}

//----------------------------------------------------------------------//

inline void Wheel :: Want_to_invert_DirecY(const YesNo _yes_no)
{
	_mem_is_invert_y = _yes_no;
}

//----------------------------------------------------------------------//

inline void Wheel :: Set_direc(const DirecX _direc)
{
	_mem_direc_x = _direc;
}

//----------------------------------------------------------------------//

inline void Wheel :: Set_direc(const DirecY _direc)
{
	_mem_direc_y = _direc;
}

//----------------------------------------------------------------------//

inline void Wheel :: Set_direc(const DirecX _direc_x, const DirecY _direc_y)
{
	_mem_direc_x = _direc_x;
	_mem_direc_y = _direc_y;
}

//----------------------------------------------------------------------//

inline void Wheel :: Set_turn(const YesNo _is_turn_l, const YesNo _is_turn_r)
{
	_mem_is_turn_l = _is_turn_l;
	_mem_is_turn_r = _is_turn_r;
}

//----------------------------------------------------------------------//

inline DirecX Wheel :: Get_direc_x()
{
	return _mem_direc_x;
}

//----------------------------------------------------------------------//

inline DirecY Wheel :: Get_direc_y()
{
	return _mem_direc_y;
}

//----------------------------------------------------------------------//

inline YesNo Wheel :: Is_turn_l()
{
	return _mem_is_turn_l;
}

//----------------------------------------------------------------------//

inline YesNo Wheel :: Is_turn_r()
{
	return _mem_is_turn_r;
}

//----------------------------------------------------------------------//

inline YesNo Wheel :: Is_moved()
{
	return
	(
		Compute_OR_BOOL(_mem_is_turn_l,	_mem_is_turn_r) |
		Is_true_the(0b0111, (Byte)Get_direc_x() & (Byte)Get_direc_y())
	);
}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

inline void FourWheel :: Set_wheel_place
(
	const Four::WheelPlace	_place,
	const MotorNumber	_motor_number
)
{
	_mem_md[_place].Reset(_motor_number);
}

//----------------------------------------------------------------------//

inline void FourWheel ::Turning(const BOOL _is_turn_l, const BOOL _is_turn_r)
{
	Wheel::Set_turn(_is_turn_l, _is_turn_r);
	
	FourWheel::Turning();
}

//----------------------------------------------------------------------//

inline void FourWheel :: Move_front_or_back(const DirecY _direc)
{
	Wheel::Set_direc(CENTER_X, _direc);
	
	FourWheel::Move_front_or_back();
}

//----------------------------------------------------------------------//

inline Motor & FourWheel :: operator [](Four::WheelPlace _place)
{
	return MDC::operator []((MotorNumber)_place);
}

//----------------------------------------------------------------------//

/************************************************************************/
