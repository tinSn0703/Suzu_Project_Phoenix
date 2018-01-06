

#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline int ControllerGet :: Get_base (const uByte _bit, const uByte _and)
{
	return ((_mem_data._all >> _bit) & _and);
}

//----------------------------------------------------------------------//

inline DirecX ControllerGet :: Get_stick_Rx()
{
	return _mem_data._sub._stick_right_x;
}

//----------------------------------------------------------------------//

inline DirecY ControllerGet :: Get_stick_Ry()
{
	return _mem_data._sub._stick_right_y;
}

//----------------------------------------------------------------------//

inline DirecX ControllerGet :: Get_stick_Lx()
{
	return _mem_data._sub._stick_left_x;
}

//----------------------------------------------------------------------//

inline DirecY ControllerGet :: Get_stick_Ly()
{
	return _mem_data._sub._stick_left_y;
}

//----------------------------------------------------------------------//

inline DirecX ControllerGet :: Get_cross_x()
{
	return _mem_data._sub._cross_x;
}

//----------------------------------------------------------------------//

inline DirecY ControllerGet :: Get_cross_y()
{
	return _mem_data._sub._cross_y;
}

//----------------------------------------------------------------------//

inline ullint ControllerGet :: Get_data()
{
	return _mem_data._all;
}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: operator [] (const ControllerBtn _arg_bit)
{
	return (BOOL)Get_base((uByte)_arg_bit, 1);
}

//----------------------------------------------------------------------//
inline DirecX ControllerGet :: operator [] (const ControllerDirecX _arg_bit)
{
	return (DirecX)Get_base((uByte)_arg_bit, 3);
}

//----------------------------------------------------------------------//

inline DirecY ControllerGet :: operator [] (const ControllerDirecY _arg_bit)
{
	return (DirecY)Get_base((uByte)_arg_bit, 3);
}

//----------------------------------------------------------------------//

/************************************************************************/
