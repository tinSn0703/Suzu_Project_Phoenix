
#pragma once

/************************************************************************/

namespace Project4
{

/************************************************************************/

class Main
{
private:
	
	Dualshock2 _controller;
	
	FourWheel _wheel;
	
	Valve _valve;
	
	CountValue _mem_timer;
	
	YesNo _mem_is_movement_enabled :1;	
	
//function
private:
	
	void Operate();
	
	void Move_valve();
	
	void Move_wheel();
	
public:
	
	Main();
	
	void Receive_operation();
	
	YesNo Is_movement_enabled();
	
	void Work();
	
	void Display();
	
	void Stop();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline YesNo Main :: Is_movement_enabled()
{
	return _mem_is_movement_enabled;
}

//----------------------------------------------------------------------//

/************************************************************************/

}

/************************************************************************/
