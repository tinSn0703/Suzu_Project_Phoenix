

#pragma once

/************************************************************************/

#include "BOOL.h"

/************************************************************************/

namespace Direc
{

enum Direc
{
	NORTH = 1,
	SOUTH = 2,
	
	EAST = 3,
	WEST = 4,
	
	CENTER = 0
};

};

namespace Test
{

class Direc
{
public:
	
	enum _Direc
	{
		CENTER	= 0,
		
		NORTH = 1,
		SOUTH = 2,
		
		EAST = 3,
		WEST = 4,
	}
	_data :3;
	
	Direc()	{	_data = CENTER;	}
		
	int operator = (int i)
	{
		_data = (_Direc)i;
		
		return i;
	} 
};

}

//----------------------------------------------------------------------//

typedef enum
{
	EAST = 1,
	WEST = 2,
	
	CENTER_X = 3
}
DirecX;

//----------------------------------------------------------------------//

typedef enum
{
	NORTH = 1,
	SOUTH = 2,
	
	CENTER_Y = 3
}
DirecY;

//----------------------------------------------------------------------//

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

inline DirecY To_DirecY (const int _data)
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

inline DirecX To_DirecX (const int _data)
{
	return ((_data & 3) ? (DirecX)(_data & 3) : CENTER_X);
}

//----------------------------------------------------------------------//

inline void Shift_DirecXY_by_45deg (DirecX *_x, DirecY *_y)
{
	const DirecX _temp_x = To_DirecX((*_x) &				(*_y));
	const DirecY _temp_y = To_DirecY((*_y) & Reversal_DirecX(*_x));

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

/************************************************************************/

