/*
 * ValveRead_inline.h
 *
 * Created: 2017/03/07 13:22:33
 *  Author: Suzu
 */ 


#pragma once

namespace ClassValve
{

//----------------------------------------------------------------------//

inline BOOL ValveRead :: Is_open_0 ()	{	return _mem_data._bit._0;	}
inline BOOL ValveRead :: Is_open_1 ()	{	return _mem_data._bit._1;	}
inline BOOL ValveRead :: Is_open_2 ()	{	return _mem_data._bit._2;	}
inline BOOL ValveRead :: Is_open_3 ()	{	return _mem_data._bit._3;	}
inline BOOL ValveRead :: Is_open_4 ()	{	return _mem_data._bit._4;	}
inline BOOL ValveRead :: Is_open_5 ()	{	return _mem_data._bit._5;	}
inline BOOL ValveRead :: Is_open_6 ()	{	return _mem_data._bit._6;	}
inline BOOL ValveRead :: Is_open_7 ()	{	return _mem_data._bit._7;	}

//----------------------------------------------------------------------//

inline BOOL ValveRead :: Is_open (const ValveNum _arg_num)
{
//	return (this->*_mem_fp_Is_open[_arg_num])();
	
	return Is_true_the(_mem_data._all, _arg_num);
}

//----------------------------------------------------------------------//

inline ValveData ValveRead :: Read()
{
	return _mem_data._all;
}

//----------------------------------------------------------------------//

inline BOOL ValveRead :: operator [] (const ValveNum _arg_num)
{	
	return Is_open(_arg_num);
}

//----------------------------------------------------------------------//

};
