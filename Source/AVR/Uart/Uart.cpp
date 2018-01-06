
#include <avr/io.h>
#include <util/delay.h>
#include <Others/BOOL.h>
#include <AVR/Uart/Uart.h>

/************************************************************************/

namespace Uart
{

/************************************************************************/

#define UCSRA	_SFR_MEM8(UartBase::Get_uart_num()	+ 0)
#define UCSRB	_SFR_MEM8(UartBase::Get_uart_num()	+ 1)
#define UCSRC	_SFR_MEM8(UartBase::Get_uart_num()	+ 2)
#define UBRRL	_SFR_MEM8(UartBase::Get_uart_num()	+ 4)
#define UBRRH	_SFR_MEM8(UartBase::Get_uart_num()	+ 5)
#define UDR		_SFR_MEM8(UartBase::Get_uart_num()	+ 6)
#define UBRR	_SFR_MEM16(UartBase::Get_uart_num()	+ 4)

/************************************************************************/
/*	UartReceive															*/
/************************************************************************/

//----------------------------------------------------------------------//

ModeReceive :: ModeReceive(const UartNum _uart_num)

	: UartBase(_uart_num)
{
	_mem_is_error_happen = NO;
	
	Enable_receive();
}

//----------------------------------------------------------------------//

void ModeReceive :: Check_error()
{
	if (UCSRA & ((1 << FE) | (1 << DOR) | (1 << UPE))) //エラーチェック
	{
		_mem_is_error_happen = YES;	//エラー
	}
	else
	{
		_mem_is_error_happen = NO;	//問題なし
	}
}

//----------------------------------------------------------------------//

YesNo ModeReceive :: Is_receive_finished()
{
	return Is_true_the(UCSRA, RXC);
}

//----------------------------------------------------------------------//

void ModeReceive :: Enable_receive()
{
	UCSRB |= (1 << RXEN);
}

//----------------------------------------------------------------------//

void ModeReceive :: Disable_receive()
{
	UCSRB &= ~(1 << RXEN);
}

//----------------------------------------------------------------------//

UartData8bit ModeReceive :: Get_UDR_8bit()
{
	Check_error();
	
	return UDR;	//受信
}

//----------------------------------------------------------------------//

UartData9bit ModeReceive :: Get_UDR_9bit()
{
	Check_error();
	
	return Is_true_the(UCSRB, RXB8) ? (0x100 | UDR) : UDR;	//受信
}

//----------------------------------------------------------------------//

UartData8bit ModeReceive :: Receive_8bit()
{
	while ( ! (UCSRA & (1 << RXC)));	//受信が完了するまで待機
	
	Check_error();
	
	return UDR;
}

//----------------------------------------------------------------------//

UartData9bit ModeReceive :: Receive_9bit()
{
	while ( ! (UCSRA & (1 << RXC)));	//受信が完了するまで待機
	
	Check_error();
	
	return ((UCSRB & (1 << RXB8)) ? (0x100 | UDR) : UDR);
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	UartTransmit														*/
/************************************************************************/

//----------------------------------------------------------------------//

ModeTransmit :: ModeTransmit (const UartNum _uart_num)

	: UartBase(_uart_num)
{
	Enable_transmit();
}

//----------------------------------------------------------------------//

void ModeTransmit :: Transmit_8bit (const UartData8bit _transmit_data)
{
	while ( ! (UCSRA & (1 << UDRE))); //送信可能になるまで待機
	
	UDR = _transmit_data;
	
	_delay_us(20);
}

//----------------------------------------------------------------------//

void ModeTransmit :: Transmit_9bit (const UartData9bit _transmit_data)
{
	while ( ! (UCSRA & (1 << UDRE))); //送信可能になるまで待機
	
	if (_transmit_data & (1 << 8))	//8bit目を送信
	{
		UCSRB |= (1 << TXB8);
	}
	else
	{
		UCSRB &= ~(1 << TXB8);
	}
	
	UDR = (_transmit_data & 0xff);	//送信
	
	_delay_us(20);
}

//----------------------------------------------------------------------//

YesNo ModeTransmit :: Is_transmit_possible()
{
	return Are_true_the(UCSRA, UDRE, TXC);
}

//----------------------------------------------------------------------//

void ModeTransmit :: Enable_transmit()
{
	UCSRB |= (1 << TXEN);
}

//----------------------------------------------------------------------//

void ModeTransmit :: Disable_transmit()
{
	UCSRB &= ~(1 << TXEN);
}

//----------------------------------------------------------------------//

/************************************************************************/

}

/************************************************************************/
