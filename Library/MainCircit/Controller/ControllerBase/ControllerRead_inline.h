

#pragma once

/************************************************************************/

inline int ControllerRead :: Get_base (usint _arg_bit, usint _arg_and)
{	return ((_mem_data._all >> _arg_bit) & _arg_and);	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_btn_North()
{	return _mem_data._sub._btn_north;	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_btn_South()
{	return _mem_data._sub._btn_south;	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_btn_East()
{	return _mem_data._sub._btn_east;	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_btn_West()
{	return _mem_data._sub._btn_west;	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_right_0 ()
{	return _mem_data._sub._btn_right_0;	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_right_1 ()
{	return _mem_data._sub._btn_right_1;	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_left_0 ()
{	return _mem_data._sub._btn_left_0;	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_left_1 ()
{	return _mem_data._sub._btn_left_1;	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_other_0 ()
{	return _mem_data._sub._btn_other_0;	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_other_1 ()
{	return _mem_data._sub._btn_other_1;	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_SELECT ()
{	return _mem_data._sub._btn_select;	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get_START ()
{	return _mem_data._sub._btn_start;	}

//----------------------------------------------------------------------//

inline DirecX ControllerRead :: Get_stick_Rx ()
{	return _mem_data._sub._stick_right_x;	}

//----------------------------------------------------------------------//

inline DirecY ControllerRead :: Get_stick_Ry ()
{	return _mem_data._sub._stick_right_y;	}

//----------------------------------------------------------------------//

inline DirecX ControllerRead :: Get_stick_Lx ()
{	return _mem_data._sub._stick_left_x;	}

//----------------------------------------------------------------------//

inline DirecY ControllerRead :: Get_stick_Ly ()
{	return _mem_data._sub._stick_left_y;	}

//----------------------------------------------------------------------//

inline DirecX ControllerRead :: Get_cross_x ()
{	return _mem_data._sub._btn_cross_x;	}

//----------------------------------------------------------------------//

inline DirecY ControllerRead :: Get_cross_y ()
{	return _mem_data._sub._btn_cross_y;	}

//----------------------------------------------------------------------//

inline ControllerData ControllerRead :: Get_data (usint _arg_num)
{	return (_arg_num > 2 ? _mem_data._arr_all[2] : _mem_data._arr_all[_arg_num]);	}

//----------------------------------------------------------------------//

inline ullint ControllerRead :: Get_data()
{
	return _mem_data._all;
}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: Get (ControllerBtn _arg_bit)
{	return (BOOL)Get_base(_arg_bit, 1);	}

//----------------------------------------------------------------------//
inline DirecX ControllerRead :: Get (ControllerDirecX _arg_bit)
{	return (DirecX)Get_base(_arg_bit, 3);	}

//----------------------------------------------------------------------//
	
inline DirecY ControllerRead :: Get (ControllerDirecY _arg_bit)
{	return (DirecY)Get_base(_arg_bit, 3);	}

//----------------------------------------------------------------------//

inline BOOL ControllerRead :: operator [] (ControllerBtn _arg_bit)
{	return Get(_arg_bit);	}

//----------------------------------------------------------------------//
inline DirecX ControllerRead :: operator [] (ControllerDirecX _arg_bit)
{	return Get(_arg_bit);	}

//----------------------------------------------------------------------//

inline DirecY ControllerRead :: operator [] (ControllerDirecY _arg_bit)
{	return Get(_arg_bit);	}

//----------------------------------------------------------------------//

inline ControllerData ControllerRead :: operator [] (usint _arg_num)
{	return Get_data(_arg_num);	}

//----------------------------------------------------------------------//

/************************************************************************/
