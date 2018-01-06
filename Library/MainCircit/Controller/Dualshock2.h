
#pragma once

/************************************************************************/

#include "Controller.h"
#include "ControllerBase/Dualshock2Base.h"

/************************************************************************/

class Dualshock2	: public Controller
					, public ClassController::Dualshock2Get
					, public ClassController::Dualshock2Push
{
public:
	
	Dualshock2(UartNum _adrs_uart);
	Dualshock2(UartNum _adrs_uart, BOOL _is_poss_rewrite);	
};

/************************************************************************/
