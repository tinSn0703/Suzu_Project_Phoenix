
#pragma once

namespace ClassValve
{

//----------------------------------------------------------------------//

inline BOOL ValveRead :: Is_open_for_0 ()	{	return _mem_data._bit._0;	}
inline BOOL ValveRead :: Is_open_for_1 ()	{	return _mem_data._bit._1;	}
inline BOOL ValveRead :: Is_open_for_2 ()	{	return _mem_data._bit._2;	}
inline BOOL ValveRead :: Is_open_for_3 ()	{	return _mem_data._bit._3;	}
inline BOOL ValveRead :: Is_open_for_4 ()	{	return _mem_data._bit._4;	}
inline BOOL ValveRead :: Is_open_for_5 ()	{	return _mem_data._bit._5;	}
inline BOOL ValveRead :: Is_open_for_6 ()	{	return _mem_data._bit._6;	}
inline BOOL ValveRead :: Is_open_for_7 ()	{	return _mem_data._bit._7;	}

//----------------------------------------------------------------------//

inline BOOL ValveRead :: Is_open_for (const ValveNum _arg_num)
{
	return Is_true_the(_mem_data._all, _arg_num);
}

//----------------------------------------------------------------------//

inline ValveData ValveRead :: Get()
{
	return _mem_data._all;
}

//----------------------------------------------------------------------//

inline BOOL ValveRead :: operator [] (const ValveNum _arg_num)
{	
	return Is_open_for(_arg_num);
}

//----------------------------------------------------------------------//

};
