

#pragma once

#if defined(__cplusplus)

#include "ValveBase/ValveBase.h"

class Valve	: public ClassValve :: ValveOperate
			, public ClassValve :: ValveLCD
{
private:
	
	UartTransmit _mem_uart;
	
public:
	
	Valve (UartNum _uart_adrs);
	Valve (UartNum _uart_adrs, ValveData _init_data);
	
	void Transmit ();
	void Transmit (UartTransmit &_uart);
	
	void Transmit_clear ();
	void Transmit_clear (UartTransmit &_uart);
};

#else

#include "ValveBase/ValveData/ValveData.h"

#endif