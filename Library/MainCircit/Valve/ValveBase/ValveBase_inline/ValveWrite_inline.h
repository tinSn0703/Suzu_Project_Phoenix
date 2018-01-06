

#pragma once

namespace ClassValve
{

//----------------------------------------------------------------------//

inline void ValveSet :: Want_to_open_0 (const BOOL _yes)	{	_mem_data._bit._0 = _yes;	}
inline void ValveSet :: Want_to_open_1 (const BOOL _yes)	{	_mem_data._bit._1 = _yes;	}
inline void ValveSet :: Want_to_open_2 (const BOOL _yes)	{	_mem_data._bit._2 = _yes;	}
inline void ValveSet :: Want_to_open_3 (const BOOL _yes)	{	_mem_data._bit._3 = _yes;	}
inline void ValveSet :: Want_to_open_4 (const BOOL _yes)	{	_mem_data._bit._4 = _yes;	}
inline void ValveSet :: Want_to_open_5 (const BOOL _yes)	{	_mem_data._bit._5 = _yes;	}
inline void ValveSet :: Want_to_open_6 (const BOOL _yes)	{	_mem_data._bit._6 = _yes;	}
inline void ValveSet :: Want_to_open_7 (const BOOL _yes)	{	_mem_data._bit._7 = _yes;	}

//----------------------------------------------------------------------//

inline void ValveSet :: Want_to_open (const ValveNum _arg_num, const BOOL _arg_yes)
{
	_mem_data._all &= ~(1 << _arg_num);
	
	_mem_data._all |= (_arg_yes << _arg_num);
}

//----------------------------------------------------------------------//

inline void ValveSet :: Set (const ValveData _arg_data)
{
	_mem_data._all = _arg_data;	
}

//----------------------------------------------------------------------//

};
