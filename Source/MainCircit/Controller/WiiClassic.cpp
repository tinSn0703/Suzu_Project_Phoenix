

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/Uart/Uart.h>
#include <AVR/Timer/GeneralTimer.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Controller/WiiClassic.h>

/************************************************************************/

namespace Controller
{
namespace Bit24
{

/************************************************************************/

//----------------------------------------------------------------------//

WiiClassic :: WiiClassic(const UartNum _uart_num, const BOOL _is_poss_rewrite)

	: ControllerBase(_uart_num, _is_poss_rewrite)
{}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

WiiClassicDoubleLine::WiiClassicDoubleLine
(
	const UartNum	_uart_num_main, 
	const UartNum	_uart_num_sub, 
	const YesNo		_is_data_rewrite
)
	: ControllerBaseDoubleLine(_uart_num_main, _uart_num_sub, _is_data_rewrite)
{}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

WiiClassicAddPush :: WiiClassicAddPush(const UartNum _uart_num, const BOOL _is_poss_rewrite)

	: ControllerBase(_uart_num, _is_poss_rewrite)
{}

//----------------------------------------------------------------------//

void WiiClassicAddPush :: Read()
{
	Stock();
	
	ControllerBase::Read();
	
	if (Get_error_state() == READ_SUCCESS)	Set_btn_data();
}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

WiiClassicAddPushDoubleLine::WiiClassicAddPushDoubleLine
(
	const UartNum	_uart_num_main, 
	const UartNum	_uart_num_sub, 
	const YesNo		_is_data_rewrite /* = NO */
)
	: ControllerBaseDoubleLine(_uart_num_main, _uart_num_sub, _is_data_rewrite)
{}

//----------------------------------------------------------------------//

void WiiClassicAddPushDoubleLine::Read()
{
	Stock();
	
	ControllerBaseDoubleLine::Read_double();
	
	if (Get_error_state() == READ_SUCCESS)	Set_btn_data();
}

//----------------------------------------------------------------------//

/************************************************************************/

}
}

/************************************************************************/
