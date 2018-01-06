

#include <akilcd/akilcd.h>
#include <Others/BOOL.h>
#include <AVR/Timer/GeneralTimer.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Valve/Valve.h>

/************************************************************************/

//----------------------------------------------------------------------//

Valve :: Valve(const UartNum _uart_num)

	: _mem_uart(_uart_num)
{
	_mem_past_data = 0x01;
}

//----------------------------------------------------------------------//

Valve :: Valve(const UartNum _uart_num, const ValveData _init_data)

	: _mem_uart(_uart_num)
{
	Set(_init_data);
	
	_mem_past_data = _init_data + 1;
}

//----------------------------------------------------------------------//

Uart::ModeTransmit * Valve :: Get_uart()
{
	return &_mem_uart;
}

//----------------------------------------------------------------------//

void Valve :: Write(Uart::ModeTransmit &_uart)
{
	if (_mem_past_data != Get())
	{
		_uart.Disable_9bit();
		
		_uart.Transmit_8bit(Get());
		
		_mem_past_data = Get();
	}
}

//----------------------------------------------------------------------//

void Valve :: Write_clear (Uart::ModeTransmit &_uart)
{
	_uart.Disable_9bit();
	
	_uart.Transmit_8bit(0x00);
}

//----------------------------------------------------------------------//

/************************************************************************/
