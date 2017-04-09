

#define _UART_SOURCE_

#include <avr/io.h>
#include <Others/BOOL.h>
#include <AVR/Uart/Uart.h>

/************************************************************************/
/*	UartReceive															*/
/************************************************************************/

//----------------------------------------------------------------------//

UartReceive :: UartReceive()	{}

//----------------------------------------------------------------------//

UartReceive :: UartReceive(const UartNum _uart_num)

	: ClassUart :: UartBase(_uart_num)

{
	Enable_receive();
}

//----------------------------------------------------------------------//

UartData9bit UartReceive :: Receive_9bit()
{
	while ( ! (_UCSRA_ & (1 << RXC)));	//��M����������܂őҋ@
	
	if (_UCSRA_ & (1 << FE))
	{
		_mem_data_b |= _UDR_ & 0x00;
		
		return _mem_data_b;
	}
	
	//��M
	const UartData9bit _receive_data = 
	(
		Is_true_the(_UCSRB_, RXB8) ? (0x100 | _UDR_) : _UDR_
	);
	
	_mem_data_b = _receive_data;
	
	return _receive_data;
}

//----------------------------------------------------------------------//

UartData8bit UartReceive :: Receive_8bit()
{
	while ( ! (_UCSRA_ & (1 << RXC)));	//��M����������܂őҋ@
	
 	if (_UCSRA_ & (1 << FE))
 	{
		_mem_data_b |= _UDR_ & 0x00;
		
		return _mem_data_b;
 	}
	
	_mem_data_b = _UDR_;	//��M
	
	return _mem_data_b;
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	UartTransmit														*/
/************************************************************************/

//----------------------------------------------------------------------//

UartTransmit :: UartTransmit()	{}

//----------------------------------------------------------------------//

UartTransmit :: UartTransmit (const UartNum _uart_num)

	: ClassUart :: UartBase(_uart_num)

{
	Enable_transmit();
}

//----------------------------------------------------------------------//

void UartTransmit :: Transmit_9bit (const UartData9bit _transmit_data)
{	
	while ( ! (_UCSRA_ & (1 << UDRE)));	//UDR����ɂȂ�܂őҋ@
	
	if (Is_true_the(_transmit_data, 8))	//8bit�ڂ𑗐M
	{
		_UCSRB_ |= (1 << TXB8);
	}
	else
	{
		_UCSRB_ &= ~(1 << TXB8);
	}
	
	_UDR_ = (_transmit_data & 0xff);	//���M
	
	while ( ! (_UCSRA_ & (1 << TXC)));	//���M����������܂őҋ@
	
	_UCSRA_ |= (1 << TXC);	//���M�����t���O���~�낷
}

//----------------------------------------------------------------------//

void UartTransmit :: Transmit_8bit (const UartData8bit _transmit_data)
{
	while ( ! (_UCSRA_ & (1 << UDRE)));	//UDR����ɂȂ�܂őҋ@
	
	_UDR_ = _transmit_data;	//���M
	
	while ( ! (_UCSRA_ & (1 << TXC)));	//���M����������܂őҋ@
	
	_UCSRA_ |= (1 << TXC);	//���M�����t���O���~�낷
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	Uart																*/
/************************************************************************/

//----------------------------------------------------------------------//

Uart :: Uart()	{}

//----------------------------------------------------------------------//

Uart :: Uart(const UartNum _uart_adrs)
{
	Initialize(_uart_adrs);
	
	Enable_receive();
	Enable_transmit();
}

//----------------------------------------------------------------------//

/************************************************************************/

#undef _UART_SOURCE_
#undef _UCSRA_
#undef _UCSRB_
#undef _UCSRC_
#undef _UBRRL_
#undef _UBRRH_
#undef _UDR_
#undef _UBRR_

/************************************************************************/
