
#include <MainCircit/MainCircit.h>

#include "Project3_define.h"
#include "Project3_Base_Bumper.h"

/************************************************************************/

namespace Project3
{

namespace Base
{

/************************************************************************/

//----------------------------------------------------------------------//

BumperSensor :: BumperSensor()	{}

//----------------------------------------------------------------------//

void BumperSensor :: Init
(
	const Direction _direction, 
	const IoAdrs	_io_adrs_a, 
	const IoBit		_io_num_a, 
	const IoAdrs	_io_adrs_b, 
	const IoBit		_io_num_b
)
{
	_mem_sensor[_direction][0].Reset(_io_adrs_a, _io_num_a);
	_mem_sensor[_direction][1].Reset(_io_adrs_b, _io_num_b);
	
	_mem_is_sensor_high[_direction] = NO;
}

//----------------------------------------------------------------------//

void BumperSensor :: Read()
{
	for (usint i = 0; i < 4; i ++)
	{
		_mem_is_sensor_high[i] = (_mem_sensor[i][0].In() | _mem_sensor[i][1].In());
	}
}

//----------------------------------------------------------------------//

Direction BumperSensor :: Get_high_direction()
{
	for (usint i = 0; i < 4; i ++)
	{
		if (_mem_is_sensor_high[i])	return (Direction)i;
	}
	
	return OTHER;
}

//----------------------------------------------------------------------//

void BumperSensor :: Display(LcdAdrs _adrs)
{
	for (uByte i = 0; i < 4; i++)
	{
		LCD_Write_num(_adrs + i, _mem_is_sensor_high[i], 1, DECIMAL_02);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

/************************************************************************/

