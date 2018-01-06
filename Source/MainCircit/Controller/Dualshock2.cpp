

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/Uart/Uart.h>
#include <AVR/Timer/GeneralTimer.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Controller/Dualshock2.h>

/************************************************************************/

namespace Controller
{
namespace Bit24
{

/************************************************************************/

//----------------------------------------------------------------------//

Dualshock2::Dualshock2(const UartNum _uart_num, const YesNo _is_data_rewrite)

	: ControllerBase(_uart_num, _is_data_rewrite)
{}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

Dualshock2DoubleLine::Dualshock2DoubleLine
(
	const UartNum	_uart_num_main, 
	const UartNum	_uart_num_sub, 
	const YesNo		_is_data_rewrite
)
	: ControllerBaseDoubleLine(_uart_num_main, _uart_num_sub, _is_data_rewrite)
{}

//----------------------------------------------------------------------//

/************************************************************************/

Dualshock2AddPush :: Dualshock2AddPush(const UartNum _uart_num, const YesNo _is_data_rewrite)

	: ControllerBase(_uart_num, _is_data_rewrite)
{}

//----------------------------------------------------------------------//

void Dualshock2AddPush :: Read()
{
	Stock();
	
	ControllerBase::Read();
	
	if (Get_error_state() == READ_SUCCESS)	Set_btn_data();
}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

Dualshock2DoubleLineAddPush::Dualshock2DoubleLineAddPush
(
	const UartNum	_uart_num_main, 
	const UartNum	_uart_num_sub, 
	const YesNo		_is_data_rewrite /* = NO */
)
	: ControllerBaseDoubleLine(_uart_num_main, _uart_num_sub, _is_data_rewrite)
{}

//----------------------------------------------------------------------//

void Dualshock2DoubleLineAddPush::Read()
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
