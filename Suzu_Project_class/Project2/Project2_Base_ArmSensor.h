
#pragma once

namespace Project2
{

/************************************************************************/

namespace Base
{

/************************************************************************/

class ArmSensor
{
//type
protected:

	enum SensorSide
	{
		RIGHT_SIDE	= 0,
		LEFT_SIDE	= 1
	};	
	
//variable
private:
	
	LimitSensor _mem_bumper_sensor[NUM_BUMPER_SENSOR];
	
	LimitSensor _mem_arm_sensor_a[NUM_ARM_SENSOR];
	
	LimitSensor _mem_arm_sensor_b[NUM_ARM_SENSOR];
	
	YesNo _mem_is_bumper_sensor_on[NUM_BUMPER_SENSOR];
	
	YesNo _mem_is_arm_sensor_on[NUM_ARM_SENSOR];
	
//function
protected:
	
	void Read();
	
	YesNo Is_bumper_sensor_on(SensorSide _side);
	
	YesNo Is_arm_sensor_on(SensorSide _side);
	
public:
	
	ArmSensor();
};
	
/************************************************************************/

//----------------------------------------------------------------------//

inline YesNo ArmSensor :: Is_arm_sensor_on(const SensorSide _side)
{
	return _mem_is_arm_sensor_on[To_within(_side, LEFT_SIDE, RIGHT_SIDE)];
}

//----------------------------------------------------------------------//

inline YesNo ArmSensor :: Is_bumper_sensor_on(const SensorSide _side)
{
	return _mem_is_bumper_sensor_on[To_within(_side, LEFT_SIDE, RIGHT_SIDE)];
}

//----------------------------------------------------------------------//

/************************************************************************/

};
	
/************************************************************************/

};

/************************************************************************/
