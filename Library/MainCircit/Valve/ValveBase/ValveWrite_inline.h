

#pragma once

namespace ClassValve
{

//----------------------------------------------------------------------//

inline void ValveWrite :: Can_open_0 (const BOOL _yes)	{	_mem_data._bit._0 = _yes;	}
inline void ValveWrite :: Can_open_1 (const BOOL _yes)	{	_mem_data._bit._1 = _yes;	}
inline void ValveWrite :: Can_open_2 (const BOOL _yes)	{	_mem_data._bit._2 = _yes;	}
inline void ValveWrite :: Can_open_3 (const BOOL _yes)	{	_mem_data._bit._3 = _yes;	}
inline void ValveWrite :: Can_open_4 (const BOOL _yes)	{	_mem_data._bit._4 = _yes;	}
inline void ValveWrite :: Can_open_5 (const BOOL _yes)	{	_mem_data._bit._5 = _yes;	}
inline void ValveWrite :: Can_open_6 (const BOOL _yes)	{	_mem_data._bit._6 = _yes;	}
inline void ValveWrite :: Can_open_7 (const BOOL _yes)	{	_mem_data._bit._7 = _yes;	}

//----------------------------------------------------------------------//

inline void ValveWrite :: Can_open (const ValveNum _arg_num, const BOOL _arg_yes)
{	
//	(this->*_mem_fp_Can_open[_arg_num])(_arg_yes)
	
	_mem_data._all &= ~(1 << _arg_num);
	
	_mem_data._all |= (_arg_yes << _arg_num);
}

//----------------------------------------------------------------------//

inline void ValveWrite :: Write (const ValveData _arg_data)
{
	_mem_data._all = _arg_data;	
}

//----------------------------------------------------------------------//

};
