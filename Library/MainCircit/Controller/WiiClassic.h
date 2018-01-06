
#pragma once

/************************************************************************/

#include "Controller.h"
#include "ControllerBase/WiiClassicBase.h"

/************************************************************************/

class WiiClassic	: public Controller
					, public ClassController::WiiClassicGet
					, public ClassController::WiiClassicPush
{
public:
	
	WiiClassic(UartNum _adrs_uart);
	WiiClassic(UartNum _adrs_uart, BOOL _is_poss_rewrite);
};

/************************************************************************/
