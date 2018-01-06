
#include <akilcd/akilcd.h>
#include <Others/BOOL.h>
#include <AVR/Timer/GeneralTimer.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Valve/ValveBase/ValveBit.h>

/************************************************************************/

namespace ClassValveBit
{

/************************************************************************/

//----------------------------------------------------------------------//

ValveBase :: ValveBase()
{
	_mem_timer = TIMER_INITAL_VALUE;
}

//----------------------------------------------------------------------//

YesNo ValveBase :: Is_timer_running()
{
	return ((_mem_timer == TIMER_INITAL_VALUE) ? NO : YES);
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
