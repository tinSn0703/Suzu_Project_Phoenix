
#pragma once

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

#include <akilcd/akilcd.h>
#include <Others/Direc.h>
#include <AVR/AVR.h>
#include <MainCircit/Controller/Controller.h>

/************************************************************************/

//----------------------------------------------------------------------//

Controller :: Controller(UartNum _arg_adrs_uart)

	: ControllerRewrite(FALSE)
	, _mem_uart(_arg_adrs_uart)
{
	ControllerBase :: Clear();
}

//----------------------------------------------------------------------//

Controller :: Controller (UartNum _arg_adrs_uart, BOOL _arg_is_poss_rewrite)

	: ControllerRewrite(_arg_is_poss_rewrite)
	, _mem_uart(_arg_adrs_uart)
{
	ControllerBase :: Clear();
}

//----------------------------------------------------------------------//

void Controller :: Receive ()
{	
	Byte _flag = 0;
	
	Byte _receive_data[_NUM_CONTROLLER_UART_DATA_] = {0x3f, 0x7f, 0x8f, 0xc0};
	
	_mem_uart.Not_use_8th_bit();
	
	_mem_uart.Enable_receive();
	
	for (usint i = 0; i < 15; i++)
	{
		const UartData _temp = _mem_uart.Receive();
		
		const Byte _num = ((_temp >> 6) & 3);
		
		_receive_data[_num] = _temp;
		
		_flag |= (1 << _num);
		
		if (_flag == 0x0f)	break;
	}
	
	ControllerBase :: Combine(_receive_data);
}

//----------------------------------------------------------------------//

void Controller :: Receive (UartReceive _arg_uart)
{
	_arg_uart.Not_use_8th_bit();
	
	_arg_uart.Enable_receive();
	
	Byte _flag = 0;
	
	Byte _receive_data[_NUM_CONTROLLER_UART_DATA_] = {0x3f, 0x7f, 0x8f, 0xc0};
	
	for (usint i = 0; i < 15; i++)
	{
		UartData _temp = _arg_uart.Receive();
		
		Byte _num = ((_temp >> 6) & 3);
		
		_receive_data[_num] = _temp;
		
		_flag |= (1 << _num);
		
		if (_flag == 0x0f)	break;
	}
	
	ControllerBase :: Combine(_receive_data);
}

//----------------------------------------------------------------------//

/************************************************************************/

#endif	//__cplusplus

/************************************************************************/

