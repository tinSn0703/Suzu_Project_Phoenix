
#include <MainCircit/MainCircit.h>

#include "Project2_define.h"
#include "Project2_Base_ArmSensor.h"

/************************************************************************/

namespace Project2
{

/************************************************************************/

namespace Base
{

/************************************************************************/

//----------------------------------------------------------------------//

ArmSensor :: ArmSensor()
{
	_mem_bumper_sensor[RIGHT_SIDE].Reset(IO_ADRS_F, IO_NUM_BUMPER_RIGHT);
	_mem_bumper_sensor[LEFT_SIDE].Reset(IO_ADRS_F, IO_NUM_BUMPER_LEFT);
	
	_mem_arm_sensor_a[RIGHT_SIDE].Reset(IO_ADRS_F, IO_NUM_ARM_A_RIGHT);
	_mem_arm_sensor_a[LEFT_SIDE].Reset(IO_ADRS_F, IO_NUM_ARM_A_LEFT);
	
	_mem_arm_sensor_b[RIGHT_SIDE].Reset(IO_ADRS_F, IO_NUM_ARM_B_RIGHT);
	_mem_arm_sensor_b[LEFT_SIDE].Reset(IO_ADRS_F, IO_NUM_ARM_B_LEFT);
	
	_mem_is_bumper_sensor_on[RIGHT_SIDE] = NO;
	_mem_is_bumper_sensor_on[LEFT_SIDE]	 = NO;
	
	_mem_is_arm_sensor_on[RIGHT_SIDE]	= NO;
	_mem_is_arm_sensor_on[LEFT_SIDE]	= NO;
}

//----------------------------------------------------------------------//

void ArmSensor :: Read()
{
	_mem_is_bumper_sensor_on[RIGHT_SIDE] = ~(_mem_bumper_sensor[RIGHT_SIDE].In());
	_mem_is_bumper_sensor_on[LEFT_SIDE]  = ~(_mem_bumper_sensor[LEFT_SIDE].In());
	
	_mem_is_arm_sensor_on[RIGHT_SIDE] = ~
	(
		_mem_arm_sensor_a[RIGHT_SIDE].In() & _mem_arm_sensor_b[RIGHT_SIDE].In()
	);
	
	_mem_is_arm_sensor_on[LEFT_SIDE] = ~
	(
		_mem_arm_sensor_a[LEFT_SIDE].In() & _mem_arm_sensor_b[LEFT_SIDE].In()
	);
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/

};

/************************************************************************/
