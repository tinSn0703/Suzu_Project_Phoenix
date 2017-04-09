
#pragma once

//----------------------------------------------------------------------//

inline void Wheel :: Swap_wheel_place
(
	const WheelPlace _place_0, 
	const WheelPlace _place_1
)
{
	const MdNum _swap = _mem_md[_place_0].Get_md_num();
	
	_mem_md[_place_0].Reset(_mem_md[_place_1].Get_md_num());
	
	_mem_md[_place_1].Reset(_swap);
}

//----------------------------------------------------------------------//

inline void Wheel :: Want_invert_Xoperate(const YesNo _yes_no)
{
	_is_invert_x = _yes_no;
}

//----------------------------------------------------------------------//

inline void Wheel :: Want_invert_Yoperate(const YesNo _yes_no)
{
	_is_invert_y = _yes_no;
}

//----------------------------------------------------------------------//

inline void Wheel :: Set(const DirecX _direc)
{
	_mem_direc_x = _direc;
}

//----------------------------------------------------------------------//

inline void Wheel :: Set(const DirecY _direc)
{
	_mem_direc_y = _direc;
}

//----------------------------------------------------------------------//

inline void Wheel :: Set(const DirecX _direc_x, const DirecY _direc_y)
{
	_mem_direc_x = _direc_x;
	_mem_direc_y = _direc_y;
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

inline void Wheel :: Shift_45deg()
{
	DirecX _temp_x = _mem_direc_x;
	DirecY _temp_y = _mem_direc_y;
	
	Shift_DirecXY_by_45deg(&_temp_x, &_temp_y);
	
	_mem_direc_x = _temp_x;
	_mem_direc_y = _temp_y;
}

//----------------------------------------------------------------------//

inline void Wheel :: Shift_90deg()
{
	DirecX _temp_x = _mem_direc_x;
	DirecY _temp_y = _mem_direc_y;
	
	Shift_DirecXY_by_90deg(&_temp_x, &_temp_y);
	
	_mem_direc_x = _temp_x;
	_mem_direc_y = _temp_y;
}

//----------------------------------------------------------------------//

inline void Wheel :: Set_pwm(const Pwm _pwm)
{
	MDC :: Set(_pwm);
}

//----------------------------------------------------------------------//

inline void Wheel :: Transmit()
{
	MDC :: Transmit();
}

//----------------------------------------------------------------------//

inline void Wheel :: Transmit(UartTransmit &_uart)
{
	MDC :: Transmit(_uart);
}

//----------------------------------------------------------------------//

inline void Wheel :: Drive_front_or_back(const DirecY _direc)
{
	Wheel :: Set(_direc);
	
	Wheel :: Drive_front_or_back();
}

//----------------------------------------------------------------------//

inline Motor & Wheel :: operator [] (const WheelPlace _place)
{
	return MDC :: operator[]((MdNum)_place);
}

//----------------------------------------------------------------------//
