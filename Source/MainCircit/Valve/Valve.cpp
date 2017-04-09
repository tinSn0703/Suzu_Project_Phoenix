

#include <akilcd/akilcd.h>
#include <Others/BOOL.h>
#include <AVR/AVR.h>
#include <MainCircit/Valve/Valve.h>

/************************************************************************/

//----------------------------------------------------------------------//

Valve :: Valve (UartNum _arg_uart_adrs)

	: _mem_uart(_arg_uart_adrs)
{}

//----------------------------------------------------------------------//

Valve :: Valve (UartNum _arg_uart_adrs, ValveData _arg_init_data)

	: _mem_uart(_arg_uart_adrs)
{
	Write(_arg_init_data);
}

//----------------------------------------------------------------------//

void Valve :: Transmit ()
{
	_mem_uart.Disable_9bit();
	
	_mem_uart.Transmit_8bit(Read());
}

//----------------------------------------------------------------------//

void Valve :: Transmit (UartTransmit &_arg_uart)
{
	_arg_uart.Disable_9bit();
	
	_arg_uart.Transmit_8bit(Read());
}

//----------------------------------------------------------------------//

void Valve :: Transmit_clear ()
{
	_mem_uart.Disable_9bit();
	
	_mem_uart.Transmit_8bit(0x00);
}

//----------------------------------------------------------------------//

void Valve :: Transmit_clear (UartTransmit &_arg_uart)
{
	_arg_uart.Disable_9bit();
	
	_arg_uart.Transmit_8bit(0x00);
}

//----------------------------------------------------------------------//
