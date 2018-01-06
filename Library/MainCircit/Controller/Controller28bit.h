
#pragma once

/************************************************************************/

#include "ControllerBase/ControllerBase.h"

/************************************************************************/

class Controller28bit	: public ClassController::ControllerRewrite
						, public ClassController::ControllerLCD
{
//variable
private:
	
	UartReceive _mem_uart;
	
	YesNo _mem_is_stick_lx_high :1;
	YesNo _mem_is_stick_ly_high :1;
	
	YesNo _mem_is_stick_rx_high :1;
	YesNo _mem_is_stick_ry_high :1;
	
//function
private:
	
	void Allot(const UartData8bit _data[NUM_CONTROLLER_28BIT]);
	
public:
	
	Controller28bit(UartNum _num_uart);
	Controller28bit(UartNum _num_uart, YesNo _is_poss_rewrite);
	
	void Clear();
	
	YesNo Is_stick_Lx_high();
	YesNo Is_stick_Ly_high();
	
	YesNo Is_stick_Rx_high();
	YesNo Is_stick_Ry_high();
	
	void Receive();
	void Receive(UartReceive &_uart);
};

/************************************************************************/

//----------------------------------------------------------------------//

inline YesNo Controller28bit :: Is_stick_Lx_high()
{
	return _mem_is_stick_lx_high;
}

//----------------------------------------------------------------------//

inline YesNo Controller28bit :: Is_stick_Ly_high()
{
	return _mem_is_stick_ly_high;
}

//----------------------------------------------------------------------//

inline YesNo Controller28bit :: Is_stick_Rx_high()
{
	return _mem_is_stick_rx_high;
}

//----------------------------------------------------------------------//

inline YesNo Controller28bit :: Is_stick_Ry_high()
{
	return _mem_is_stick_ry_high;
}

//----------------------------------------------------------------------//

inline void Controller28bit :: Receive()
{
	Controller28bit::Receive(_mem_uart);
}

//----------------------------------------------------------------------//

/************************************************************************/
