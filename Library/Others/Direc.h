

#pragma once

/************************************************************************/

#include "BOOL.h"

/************************************************************************/

//----------------------------------------------------------------------//

typedef enum
{
	EAST = 0b01,
	WEST = 0b10,
	
	CENTER_X = 0b11
}
DirecX;

//----------------------------------------------------------------------//

typedef enum
{
	NORTH = 0b01,
	SOUTH = 0b10,
	
	CENTER_Y = 0b11
}
DirecY;

//----------------------------------------------------------------------//

typedef enum
{
	DIREC_C_N = 0b1101,
	DIREC_E_N = 0b0101,
	DIREC_E_C = 0b0111,
	DIREC_E_S = 0b0110,
	DIREC_C_S = 0b1110,
	DIREC_W_S = 0b1010,
	DIREC_W_C = 0b1011,
	DIREC_W_N = 0b1001,
	DIREC_C_C = 0b1111
}
DataDirec;

//----------------------------------------------------------------------//

/************************************************************************/

typedef union
{
	struct SubUnionDirec
	{
		DirecX _x :2;
		DirecY _y :2;
	}
	_sub;
	
	DataDirec _all :4;
}
Direc;

/************************************************************************/

//----------------------------------------------------------------------//

inline DirecY Reversal_DirecY (const DirecY _direc)
{
	return 
	(
		_direc == NORTH ? SOUTH :
		_direc == SOUTH ? NORTH :
		CENTER_Y
	);
}

//----------------------------------------------------------------------//

inline DirecY Convert_to_DirecY (const int _data)
{
	return ((_data & 3) ? (DirecY)(_data & 3) : CENTER_Y);
}

//----------------------------------------------------------------------//

inline DirecX Reversal_DirecX (const DirecX _direc)
{
	return
	(
		_direc == EAST ? WEST :
		_direc == WEST ? EAST :
		CENTER_X
	);
}

//----------------------------------------------------------------------//

inline DirecX Convert_to_DirecX (const int _data)
{
	return ((_data & 3) ? (DirecX)(_data & 3) : CENTER_X);
}

//----------------------------------------------------------------------//

inline Direc Combine_with_Direc (const DirecX _x, const DirecY _y)
{
	Direc _temp;
	
	_temp._sub._x = _x; 
	_temp._sub._y = _y;
	
	return _temp;
}

//----------------------------------------------------------------------//

inline void Shift_Direc_by_45deg (Direc *_direc)
{
	const DirecX _temp_x = 
	Convert_to_DirecX
	(
		(_direc->_sub._x) &
		(_direc->_sub._y)
	);
	
	const DirecY _temp_y = 
	Convert_to_DirecY
	(
		(_direc->_sub._y) & 
		Reversal_DirecX(_direc->_sub._x)
	);

	_direc->_sub._x = _temp_x;
	_direc->_sub._y = _temp_y;
}

//----------------------------------------------------------------------//

inline void Shift_Direc_by_90deg (Direc *_direc)
{
	const DirecX _temp_x = (DirecX)					(_direc->_sub._y);
	const DirecY _temp_y = (DirecY)Reversal_DirecX	(_direc->_sub._x);

	_direc->_sub._x = _temp_x;
	_direc->_sub._y = _temp_y;
}

//----------------------------------------------------------------------//

inline void Shift_DirecXY_by_45deg (DirecX *_x, DirecY *_y)
{
	const DirecX _temp_x = Convert_to_DirecX((*_x) &				(*_y));
	const DirecY _temp_y = Convert_to_DirecY((*_y) & Reversal_DirecX(*_x));

	*_x = _temp_x;
	*_y = _temp_y;
}

//----------------------------------------------------------------------//

inline void Shift_DirecXY_by_90deg (DirecX *_x, DirecY *_y)
{
	const DirecX _temp_x = (DirecX)					(*_y);
	const DirecY _temp_y = (DirecY)Reversal_DirecX	(*_x);

	*_x = _temp_x;
	*_y = _temp_y;
}

//----------------------------------------------------------------------//

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

//----------------------------------------------------------------------//

inline DirecY operator ~ (const DirecY _direc)
{
	return Reversal_DirecY(_direc);
}

//----------------------------------------------------------------------//

inline DirecX operator ~ (const DirecX _direc)
{
	return Reversal_DirecX(_direc);
}

//----------------------------------------------------------------------//

inline Direc operator + (const DirecX _x, const DirecY _y)
{
	return Combine_with_Direc(_x, _y);
}

//----------------------------------------------------------------------//

/************************************************************************/

#endif /*__cplusplus*/

