

#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline int ControllerGet :: Get_base (const Byte _bit, const Byte _and)
{	return ((_mem_data._all >> _bit) & _and);	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_btn_North()
{	return _mem_data._sub._btn_north;	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_btn_South()
{	return _mem_data._sub._btn_south;	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_btn_East()
{	return _mem_data._sub._btn_east;	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_btn_West()
{	return _mem_data._sub._btn_west;	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_right_0()
{	return _mem_data._sub._btn_right_0;	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_right_1()
{	return _mem_data._sub._btn_right_1;	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_left_0()
{	return _mem_data._sub._btn_left_0;	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_left_1()
{	return _mem_data._sub._btn_left_1;	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_other_0()
{	return _mem_data._sub._btn_other_0;	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_other_1()
{	return _mem_data._sub._btn_other_1;	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_SELECT()
{	return _mem_data._sub._btn_select;	}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get_START()
{	return _mem_data._sub._btn_start;	}

//----------------------------------------------------------------------//

inline DirecX ControllerGet :: Get_stick_Rx()
{	return _mem_data._sub._stick_right_x;	}

//----------------------------------------------------------------------//

inline DirecY ControllerGet :: Get_stick_Ry()
{	return _mem_data._sub._stick_right_y;	}

//----------------------------------------------------------------------//

inline DirecX ControllerGet :: Get_stick_Lx()
{	return _mem_data._sub._stick_left_x;	}

//----------------------------------------------------------------------//

inline DirecY ControllerGet :: Get_stick_Ly()
{	return _mem_data._sub._stick_left_y;	}

//----------------------------------------------------------------------//

inline DirecX ControllerGet :: Get_cross_x()
{	return _mem_data._sub._btn_cross_x;	}

//----------------------------------------------------------------------//

inline DirecY ControllerGet :: Get_cross_y()
{	return _mem_data._sub._btn_cross_y;	}

//----------------------------------------------------------------------//

inline ControllerData ControllerGet :: Get_data(const sint _num)
{
	return 
	(
		_num > 2 ? _mem_data._array[2] :
		_num < 0 ? _mem_data._array[0] : 
		_mem_data._array[_num]
	);
}

//----------------------------------------------------------------------//

inline ullint ControllerGet :: Get_data()
{
	return _mem_data._all;
}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: Get(const ControllerBtn _arg_bit)
{
	return (BOOL)Get_base((Byte)_arg_bit, 1);
}

//----------------------------------------------------------------------//
inline DirecX ControllerGet :: Get(const ControllerDirecX _arg_bit)
{
	return (DirecX)Get_base((Byte)_arg_bit, 3);
}

//----------------------------------------------------------------------//
	
inline DirecY ControllerGet :: Get(const ControllerDirecY _arg_bit)
{
	return (DirecY)Get_base((Byte)_arg_bit, 3);
}

//----------------------------------------------------------------------//

inline BOOL ControllerGet :: operator [] (ControllerBtn _arg_bit)
{
	return Get(_arg_bit);
}

//----------------------------------------------------------------------//
inline DirecX ControllerGet :: operator [] (ControllerDirecX _arg_bit)
{
	return Get(_arg_bit);
}

//----------------------------------------------------------------------//

inline DirecY ControllerGet :: operator [] (ControllerDirecY _arg_bit)
{
	return Get(_arg_bit);
}

//----------------------------------------------------------------------//

/************************************************************************/
