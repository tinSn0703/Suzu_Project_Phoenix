

#pragma once

#include "Typedef.h"
#include "BOOL.h"
#include "Direc.h"
#include "Signal.h"
#include "Str.h"

#define PI 3.14159265359

/************************************************************************/

//----------------------------------------------------------------------//

inline BOOL Is_withen
(
	const int _value,
	const int _max,
	const int _min
)
{
	if ((_max >= _value) && (_value >= _min))
	{
		return TRUE;
	}
	
	return FALSE;
}

//----------------------------------------------------------------------//

inline int To_within
(
	const int _value,
	const int _max,
	const int _min
)
{
	return 
	(
		_value > _max ? _max : 
		_value < _min ? _min :
		_value
	);
}

//----------------------------------------------------------------------//

inline int Truncate
(
	const int _value,
	const int _basic_value,
	const int _widch
)
{
	if (Is_withen(_value, (_basic_value + _widch), (_basic_value - _widch)))
	{
		return _basic_value;
	}
	
	return _value;
}

//----------------------------------------------------------------------//

/************************************************************************/
