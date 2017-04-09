
#pragma once

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/AVR.h>
#include <MainCircit/Motor/Motor.h>

/************************************************************************/

//----------------------------------------------------------------------//

Motor :: Motor ()	{}

//----------------------------------------------------------------------//

Motor :: Motor 
(
	const NumMDC	_arg_num_mdc, 
	const NumMD		_arg_num_md
)
{
	Initialize(_arg_num_mdc, _arg_num_md);
}

//----------------------------------------------------------------------//

void Motor :: Transmit ()
{
	_mem_uart->Use_8th_bit();
	
	_mem_uart->Transmit(Get_data_0());
	_mem_uart->Transmit(Get_data_1());
	
	_delay_us(100);
}

//----------------------------------------------------------------------//

void Motor :: Transmit (UartTransmit &_arg_uart)
{
	_arg_uart.Use_8th_bit();
	
	_arg_uart.Transmit(Get_data_0());
	_arg_uart.Transmit(Get_data_1());
	
	_delay_us(100);
}

//----------------------------------------------------------------------//

void Motor :: Transmit_clear ()
{	
	_mem_uart->Use_8th_bit();
	
	_mem_uart->Transmit(Get_data_0() & 0x1e0);
	_mem_uart->Transmit(Get_data_1() & 0x1e0);
	
	_delay_us(100);
}

//----------------------------------------------------------------------//

void Motor :: Transmit_clear (UartTransmit &_arg_uart)
{
	_arg_uart.Use_8th_bit();
	
	_arg_uart.Transmit(Get_data_0() & 0x1e0);
	_arg_uart.Transmit(Get_data_1() & 0x1e0);
	
	_delay_us(100);
}

//----------------------------------------------------------------------//

/************************************************************************/

#endif	//__cplusplus

/************************************************************************/

