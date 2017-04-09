
#pragma once

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

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
	_mem_uart.Not_use_8th_bit();
	
	_mem_uart.Enable_transmit();
	
	_mem_uart.Transmit(Read());
}

//----------------------------------------------------------------------//

void Valve :: Transmit (UartTransmit &_arg_uart)
{
	_arg_uart.Not_use_8th_bit();
	
	_arg_uart.Enable_transmit();
	
	_arg_uart.Transmit(Read());
}

//----------------------------------------------------------------------//

void Valve :: Transmit_clear ()
{
	_mem_uart.Not_use_8th_bit();
	
	_mem_uart.Enable_transmit();
	
	_mem_uart.Transmit(0x00);
}

//----------------------------------------------------------------------//

void Valve :: Transmit_clear (UartTransmit &_arg_uart)
{
	_arg_uart.Not_use_8th_bit();
	
	_arg_uart.Enable_transmit();
	
	_arg_uart.Transmit(0x00);
}

//----------------------------------------------------------------------//

/************************************************************************/

#endif	//__cplusplus

/************************************************************************/

