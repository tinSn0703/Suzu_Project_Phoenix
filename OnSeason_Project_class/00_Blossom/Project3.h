
#pragma once

/************************************************************************/

#include "Project3/Project3_define.h"

#include "Project3/Project3_Base_Bumper.h"
#include "Project3/Project3_Base_MoveWheel.h"
#include "Project3/Project3_Base_MoveArm.h"

/************************************************************************/

namespace Project3
{

/************************************************************************/

class Main	: private	Base::MoveWheel
			, private	Base::BumperSensor
			, private	Base::MoveArm::MoveBelt
			, private	Base::MoveArm::MoveRotation
			, private	Base::MoveArm::MoveUpOrDown
			, private	Base::MoveArm::MoveShoulder
{
//variable
private:
	
	Dualshock2 _controller;
	
	char _mem_direc;
	
	YesNo _is_unlocked :1;
	
//function
private:
	
	void Operate();
	
	void Move();
	
	void Transmit();
	
public:
	
	Main();
	
	YesNo Is_movement_enabled();
	
	void Receive_operation();
	
	void Work();
	
	void Stop();
	
	void Display();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline YesNo Main :: Is_movement_enabled()
{
	return _is_unlocked;
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
