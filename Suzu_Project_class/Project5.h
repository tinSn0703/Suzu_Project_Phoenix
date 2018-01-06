
#pragma once

/*
必要な要素

三輪オムニ
コントローラ

角度調節用モータ * 1
直動用モータ * 1

*/

/************************************************************************/

namespace Project5
{

/************************************************************************/

class Main
{
//variable
private:
	
	Dualshock2 _controller;
	ThreeOmuni _wheel;
	
	ValveSingle _valve[4];
	
	Motor _motor_stand;
	
	UartTransmit _uart_valve;
	
	YesNo _mem_is_movement_enabled :1;
	
	CountValue _mem_timer;
	
//function
public:
	
	Main();
	
	void Receive_operation();
	
	YesNo Is_movement_enabled();
	
	void Work();
	
	void Display();
	
	void Stop();
};

/************************************************************************/

};

/************************************************************************/
