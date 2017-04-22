

#pragma once

#if defined(__cplusplus)

/************************************************************************/

#include "ControllerBase/ControllerBase.h"

/************************************************************************/

class Controller	: public ClassController :: ControllerRewrite
					, public ClassController :: ControllerPush
					, public ClassController :: ControllerLCD
{
private:
	
	UartReceive _mem_uart;
	
public:
	
	Controller (UartNum _adrs_uart);
	Controller (UartNum _adrs_uart, BOOL _is_poss_rewrite);
	
	void Receive ();
	void Receive (UartReceive _uart);
};

/************************************************************************/

#else

#include "ControllerBase/ControllerData/ControllerData.h"

#endif
