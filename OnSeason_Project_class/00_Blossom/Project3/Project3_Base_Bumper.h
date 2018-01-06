
#pragma once

/************************************************************************/

namespace Project3
{

namespace Base
{

/************************************************************************/

class BumperSensor
{
//variable
private:
	
	LimitSensor _mem_sensor[4][2];
	
	YesNo _mem_is_sensor_high[4];
	
//function	
public:
	
	BumperSensor();
	
	void Init(Direction _direction, IoAdrs _io_adrs_a, IoBit _io_num_a, IoAdrs _io_adrs_b, IoBit _io_num_b);
	
	void Read();
	
	YesNo Is_sensor_high(Direction _direction);
	
	Direction Get_high_direction();
	
	void Display(LcdAdrs _adrs);
};

/************************************************************************/

//----------------------------------------------------------------------//

inline YesNo BumperSensor :: Is_sensor_high(const Direction _direction)
{
	return _mem_is_sensor_high[_direction];
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

/************************************************************************/
