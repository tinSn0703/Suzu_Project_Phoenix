
#pragma once

#include "Project2/Project2_define.h"
#include "Project2/Project2_Base_MoveArm.h"
#include "Project2/Project2_Base_MoveWheel.h"

namespace Project2
{

/************************************************************************/

class Main	: public Base :: MoveArm
			, public Base :: MoveWheel
{
//variable
private:	
	
	Dualshock2 _mem_controller;
	
	YesNo _mem_is_unlocked :1;
	
//function
private:
	
	void Operate();
	
public:
	
	Main();
	
	void Receive_operate();
	
	void Transmit();
	
	void Stop();
	
	void Display();
	
	void Doing();
};

/************************************************************************/

}


