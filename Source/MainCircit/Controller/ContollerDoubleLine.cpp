
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/Uart/Uart.h>
#include <AVR/Timer/GeneralTimer.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Controller/Controller.h>
#include <MainCircit/Controller/ControllerDoubleLine.h>

/************************************************************************/

namespace Controller
{
namespace Bit24
{

/************************************************************************/

//----------------------------------------------------------------------//

ControllerBaseDoubleLine::ControllerBaseDoubleLine
(
	const UartNum	_uart_num_main, 
	const UartNum	_uart_num_sub, 
	const YesNo		_is_data_rewrite /* = NO */
)
	: ControllerBase(_uart_num_main, _is_data_rewrite)
	, _mem_uart_sub(_uart_num_sub)
{
	_mem_is_main_line_use = YES;
}

//----------------------------------------------------------------------//

void ControllerBaseDoubleLine::Read_double()
{
	if (_mem_uart.Is_receive_finished())
	{
		_mem_is_main_line_use = YES;
		
		Receive(_mem_uart);
		
		Allot();
	}
	else
	{
		if (_mem_is_main_line_use)
		{
			Start_timer(TIME_READ_ERROR_DOUBLE);
			
			if (Is_timer_finish())
			{
				Stop_timer();
				
				_mem_is_main_line_use = NO;
			}
		}
		else
		{
			if (_mem_uart_sub.Is_receive_finished())
			{
				Receive(_mem_uart);
				
				Allot();
			}
			else
			{
				Start_timer(TIME_READ_ERROR_DOUBLE);
				
				Is_timer_finish();
			}
		}
	}
}

//----------------------------------------------------------------------//

//----------------------------------------------------------------------//

/************************************************************************/

}
}

/************************************************************************/
