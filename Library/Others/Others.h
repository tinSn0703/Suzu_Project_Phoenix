

#pragma once

#include "Typedef.h"
#include "BOOL.h"
#include "Direc.h"
#include "Signal.h"
#include "Str.h"

/************************************************************************/

#ifdef __cplusplus	//C++‚ÌŽž—p

	extern "C"	{

#endif /*__cplusplus*/

/************************************************************************/

inline int To_within
(
	const int _arg_value,
	const int _arg_max,
	const int _arg_min
)
{
	return 
	(
		_arg_value > _arg_max ? _arg_max : 
		_arg_value < _arg_min ? _arg_min :
		_arg_value
	);
}

/************************************************************************/

#ifdef __cplusplus	//C++‚ÌŽž—p

	}

#endif /*__cplusplus*/

/************************************************************************/
