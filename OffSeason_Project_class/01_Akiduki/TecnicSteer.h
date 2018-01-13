/*
 * TecnicSteer.h
 *
 * Created: 2017/12/21 12:27:36
 *  Author: ��
 *
 * �Z�p�J�� �l�փX�e�A
 */ 

#pragma once

#include <MainCircit/MainCircit.h>

/************************************************************************/

namespace Off2017
{
namespace Akiduki
{
namespace TecnicSteer
{

/************************************************************************/

class Main
{
//function
public:
	
	Main();
	
	void Input();
	
	void Process();
	
	void Output();
	
//variable
private:
	
	FourSteer _wheel;
	
	Controller::Bit24::Dualshock2 _controller;
	
	YesNo _is_unlock :1;
};

/************************************************************************/

}
}
}

/************************************************************************/
