

#pragma once

/************************************************************************/

#include "ValveBase/ValveBase.h"

/************************************************************************/

class Valve	: public ClassValve::ValveOperate
			, public ClassValve::ValveLCD
{
//variable
private:
	
	UartTransmit _mem_uart;
	
//function
public:
	
	Valve (UartNum _uart_adrs);
	Valve (UartNum _uart_adrs, ValveData _init_data);
	
	UartTransmit * Get_uart();
	
	void Transmit ();
	void Transmit (UartTransmit &_uart);
	
	void Transmit_clear ();
	void Transmit_clear (UartTransmit &_uart);
};

/************************************************************************/
