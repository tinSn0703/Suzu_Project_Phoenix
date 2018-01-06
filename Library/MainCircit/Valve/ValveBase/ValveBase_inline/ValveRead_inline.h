
#pragma once

/************************************************************************/

namespace ClassValve
{

/************************************************************************/

//----------------------------------------------------------------------//

inline BOOL ValveGet :: Is_open_for_0 ()	{	return _mem_data._bit._0;	}
inline BOOL ValveGet :: Is_open_for_1 ()	{	return _mem_data._bit._1;	}
inline BOOL ValveGet :: Is_open_for_2 ()	{	return _mem_data._bit._2;	}
inline BOOL ValveGet :: Is_open_for_3 ()	{	return _mem_data._bit._3;	}
inline BOOL ValveGet :: Is_open_for_4 ()	{	return _mem_data._bit._4;	}
inline BOOL ValveGet :: Is_open_for_5 ()	{	return _mem_data._bit._5;	}
inline BOOL ValveGet :: Is_open_for_6 ()	{	return _mem_data._bit._6;	}
inline BOOL ValveGet :: Is_open_for_7 ()	{	return _mem_data._bit._7;	}

//----------------------------------------------------------------------//

inline BOOL ValveGet :: Is_open_for (const ValveNum _arg_num)
{
	return Is_true_the(_mem_data._all, _arg_num);
}

//----------------------------------------------------------------------//

inline ValveData ValveGet :: Get()
{
	return _mem_data._all;
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
