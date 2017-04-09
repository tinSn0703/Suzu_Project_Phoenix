

#include <akilcd/akilcd.h>
#include <Others/Direc.h>
#include <AVR/AVR.h>
#include <MainCircit/Controller/Controller.h>

/************************************************************************/

//----------------------------------------------------------------------//

Controller :: Controller(const UartNum _arg_adrs_uart)

	: ControllerRewrite(FALSE)
	, _mem_uart(_arg_adrs_uart)
{
	ControllerBase :: Clear();
}

//----------------------------------------------------------------------//

Controller :: Controller 
(
	const UartNum	_arg_adrs_uart, 
	const BOOL		_arg_is_poss_rewrite
)

	: ControllerRewrite(_arg_is_poss_rewrite)
	, _mem_uart(_arg_adrs_uart)
{
	ControllerBase :: Clear();
}

//----------------------------------------------------------------------//

void Controller :: Receive ()
{
	Byte _receive_data[_NUM_CONTROLLER_UART_DATA_] = {0x3f, 0x7f, 0x8f, 0xc0};
	
	Byte _flag = 0;
	
	_mem_uart.Disable_9bit();
	
	for (Byte i = 0; i < 10; i++)
	{
		const UartData8bit _temp = _mem_uart.Receive_8bit();
		
		const Byte _num = ((_temp >> 6) & 3);
		
		_receive_data[_num] = _temp;
		
		_flag |= (1 << _num);
		
		if (_flag == 0xf)	break;
		
		_delay_us(10);
	}
	
	ControllerBase :: Combine(_receive_data);
}

//----------------------------------------------------------------------//

void Controller :: Receive (UartReceive _arg_uart)
{	
	Byte _flag = 0;
	
	Byte _receive_data[_NUM_CONTROLLER_UART_DATA_] = {0x3f, 0x7f, 0x8f, 0xc0};
	
	_arg_uart.Disable_9bit();
	
	for (Byte i = 0; i < 10; i++)
	{
		const UartData8bit _temp = _arg_uart.Receive_8bit();
		
		const Byte _num = ((_temp >> 6) & 3);
		
		_receive_data[_num] = _temp;
		
		_flag |= (1 << _num);
		
		if (_flag == 0xf)	break;
	}
	
	ControllerBase :: Combine(_receive_data);
}

//----------------------------------------------------------------------//

/************************************************************************/
