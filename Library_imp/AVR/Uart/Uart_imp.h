
#pragma once

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

#define _UART_SOURCE_

/************************************************************************/
/*	UartReceive															*/
/************************************************************************/

//----------------------------------------------------------------------//

UartReceive :: UartReceive ()	{}

//----------------------------------------------------------------------//

UartReceive :: UartReceive (UartNum _arg_uart_adrs)
{
	UartBase :: Initialize(_arg_uart_adrs);
}

//----------------------------------------------------------------------//

UartData UartReceive :: Receive ()
{
	UartData _receive_data = 0;
	
	Enable_receive();
	
	UartOperationBase :: Wait_receive_completed();
	
	if (UartSet :: Is_8th_bit_used() & Is_true_the(_UCSRB_, RXB8))
	{
		_receive_data = 0x100;
	}
	
	_receive_data |= (_UDR_ & 0xff);
	
	return _receive_data;
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	UartTransmit														*/
/************************************************************************/

//----------------------------------------------------------------------//

UartTransmit :: UartTransmit ()	{}

//----------------------------------------------------------------------//

UartTransmit :: UartTransmit (UartNum _arg_uart_adrs)
{
	UartBase :: Initialize(_arg_uart_adrs);
}

//----------------------------------------------------------------------//

void UartTransmit :: Transmit (const UartData _arg_uart_data)
{
	Enable_transmit();
	
	UartOperationBase :: Wait_transmit_accepted();
	
	if (UartSet :: Is_8th_bit_used() & Is_true_the(_arg_uart_data, 8))
	{
		_UCSRB_ |= (1 << TXB8);
	}
	else
	{
		_UCSRB_ &= ~(1 << TXB8);
	}
	
	_UDR_ = (_arg_uart_data & 0xff);
	
	UartOperationBase :: Wait_transmit_completed();
}

//----------------------------------------------------------------------//

void UartTransmit :: Transmit (const ClassUart :: Uart &_arg_uart_data)
{
	Enable_transmit();
	
	UartOperationBase :: Wait_transmit_accepted();
	
	if (UartSet :: Is_8th_bit_used() & _arg_uart_data._bit._8)
	{
		_UCSRB_ |= (1 << TXB8);
	}
	else
	{
		_UCSRB_ &= ~(1 << TXB8);
	}
	
	_UDR_ = _arg_uart_data._all_8;
	
	UartOperationBase :: Wait_transmit_completed();
}

//----------------------------------------------------------------------//

/************************************************************************/

#undef _UART_SOURCE_

/************************************************************************/

#endif	//__cplusplus

/************************************************************************/
