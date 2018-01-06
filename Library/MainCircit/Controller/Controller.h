
#pragma once

/************************************************************************/

#include "ControllerBase/ControllerBase.h"

/************************************************************************/

class Controller	: public ClassController::ControllerRewrite
					, public ClassController::ControllerLCD
{
//variable
private:
	
	UartReceive _mem_uart;
	
//function
private:
	
	void Allot(const uByte _receive_data[NUM_CONTROLLER_24BIT]);
	
public:
	
	Controller(UartNum _num_uart);
	Controller(UartNum _num_uart, YesNo _is_poss_rewrite);
	
	void Clear();
	
	void Receive();
	void Receive(UartReceive &_uart);
};

/************************************************************************/

//----------------------------------------------------------------------//

inline void Controller :: Clear()
{
	_mem_data._array[0] = 0x00;
	_mem_data._array[1] = 0xf0;
	_mem_data._array[2] = 0xff;
}

//----------------------------------------------------------------------//

inline void Controller :: Receive ()
{
	Controller::Receive(_mem_uart);
}

//----------------------------------------------------------------------//

/************************************************************************/
