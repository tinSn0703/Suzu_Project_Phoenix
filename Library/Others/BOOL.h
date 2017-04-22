

#pragma once

/************************************************************************/

#include "Typedef.h"

/************************************************************************/

typedef enum
{
	FALSE	= 0,
	TRUE	= 1
}
BOOL;

/************************************************************************/

typedef BOOL YesNo;

#define YES TRUE
#define NO	FALSE

/************************************************************************/

//----------------------------------------------------------------------//

inline BOOL Convert_to_BOOL (const int _data)
{
	return ((_data == 0) ? FALSE : TRUE);
}

//----------------------------------------------------------------------//

inline BOOL Reversal_BOOL (const BOOL _bool)
{
	return (BOOL)(~((uchar)_bool) & 1);
}

//----------------------------------------------------------------------//

inline BOOL Compute_OR_BOOL (const BOOL _left, const BOOL _right)
{
	return (BOOL)(((uchar)_left | (uchar)_right) & 1);
}

//----------------------------------------------------------------------//

inline BOOL Compute_XOR_BOOL (const BOOL _left, const BOOL _right)
{
	return (BOOL)(((uchar)_left ^ (uchar)_right) & 1);
}

//----------------------------------------------------------------------//

inline BOOL Conpute_AND_BOOL (const BOOL _left, const BOOL _right)
{
	return (BOOL)(((uchar)_left & (uchar)_right) & 1);
}

//----------------------------------------------------------------------//

inline BOOL Is_true_the (const int _check_data, const int _bit)
{
	return (BOOL)((_check_data >> _bit) & 1);
}

//----------------------------------------------------------------------//

inline BOOL Is_false_the (const int _check_data, const int _bit)
{
	return (BOOL)(~(_check_data >> _bit) & 1);
}

//----------------------------------------------------------------------//

inline BOOL Are_true_the 
(
	const int	_check_data, 
	const int	_bit_0, 
	const int	_bit_1
)
{
	return (BOOL)
	(
		(_check_data >> _bit_0) & (_check_data >> _bit_1) & 1
	);
}

//----------------------------------------------------------------------//

inline BOOL Are_false_the 
(
	const int	_check_data, 
	const int	_bit_0, 
	const int	_bit_1
)
{
	return (BOOL)
	(
		~((_check_data >> _bit_0) & (_check_data >> _bit_1)) & 1
	);
}

//----------------------------------------------------------------------//

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

//----------------------------------------------------------------------//

inline BOOL operator ~ (const BOOL _bool)
{
	return Reversal_BOOL(_bool);
}

//----------------------------------------------------------------------//

inline BOOL operator | (const BOOL _left, const BOOL _right)
{
	return Compute_OR_BOOL(_left, _right);
}

//----------------------------------------------------------------------//

inline BOOL operator ^ (const BOOL _left, const BOOL _right)
{
	return Compute_XOR_BOOL(_left, _right);
}

//----------------------------------------------------------------------//

inline BOOL operator & (const BOOL _left, const BOOL _right)
{
	return Conpute_AND_BOOL(_left, _right);
}

//----------------------------------------------------------------------//

/************************************************************************/

#endif /*__cplusplus*/

/************************************************************************/
