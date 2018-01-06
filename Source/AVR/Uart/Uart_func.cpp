

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <Others/BOOL.h>
#include <AVR/Uart/Uart_func.h>

/************************************************************************/

namespace Uart
{

/************************************************************************/

#define UCSRA	_SFR_MEM8(_adrs  + 0)
#define UCSRB	_SFR_MEM8(_adrs  + 1)
#define UCSRC	_SFR_MEM8(_adrs  + 2)
#define UBRRL	_SFR_MEM8(_adrs  + 4)
#define UBRRH	_SFR_MEM8(_adrs  + 5)
#define UDR		_SFR_MEM8(_adrs  + 6)
#define UBRR	_SFR_MEM16(_adrs + 4)

/************************************************************************/

//----------------------------------------------------------------------//

void Initialize(const UartNum _adrs)
{
	UBRR   =  0x0004;
	UCSRA  =  (1 << U2X);
	
	UCSRB &= ~
	(
		(1 << RXEN)		| 
		(1 << TXEN)		| 
		(1 << UCSZ2)	| 
		(1 << RXCIE)	| 
		(1 << TXCIE)	| 
		(1 << UDRIE)
	);
	
	UCSRC  =  ((1 << UPM1) | (1 << UPM0) | (1 << UCSZ1) | (1 << UCSZ0));
}

//----------------------------------------------------------------------//

void Initialize_details 
(
	const UartNum		_adrs, 
	unsigned short int	_ubrr, 
	unsigned char		_parity
)
{
	UBRR = _ubrr;
	
	UCSRA = (1 << U2X);
	
	UCSRB &= ~
	(
		(1 << RXEN)		|
		(1 << TXEN)		|
		(1 << UCSZ2)	|
		(1 << RXCIE)	|
		(1 << TXCIE)	|
		(1 << UDRIE)
	);
	
	UCSRC  =  (_parity | (1 << UCSZ1) | (1 << UCSZ0));
}

//----------------------------------------------------------------------//

YesNo Is_initialize_finshe(const UartNum _adrs)
{
	return (Is_true_the(UCSRA, U2X));
}

//----------------------------------------------------------------------//

UartData8bit Receive_8bit(const UartNum _adrs)
{	
	while ( ! (UCSRA & (1 << RXC)));
	
	return UDR;
}

//----------------------------------------------------------------------//

UartData9bit Receive_9bit(const UartNum _adrs)
{
	while ( ! (UCSRA & (1 << RXC)));	//受信が完了するまで待機
	
	return ((UCSRB & (1 << RXB8)) ? (0x100 | UDR) : UDR);
}

//----------------------------------------------------------------------//

void Transmit_8bit(const UartNum _adrs, const UartData8bit _transmit_data)
{
	while ( ! (UCSRA & (1 << UDRE)));
	
	UDR = _transmit_data;
		
 	_delay_us(20);
}

//----------------------------------------------------------------------//

void Transmit_9bit(const UartNum _adrs, const UartData9bit _transmit_data)
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

void Enable_receive(const UartNum _adrs)
{
	UCSRB |= (1 << RXEN);
}

//----------------------------------------------------------------------//

void Enable_transmit(const UartNum _adrs)
{
	UCSRB |= (1 << TXEN);
}

//----------------------------------------------------------------------//

void Enable_9bit(const UartNum _adrs)
{
	UCSRB |= (1 << UCSZ2);
}

//----------------------------------------------------------------------//

void Disable_9bit(const UartNum _adrs)
{
	UCSRB &= ~(1 << UCSZ2);
}

//----------------------------------------------------------------------//

YesNo Is_enabled_9bit(const UartNum _adrs)
{
	return (YesNo)((UCSRB >> UCSZ2) & 1);
}

//----------------------------------------------------------------------//

void Enable_isr(const UartNum _adrs, const UartISR _isr)
{
	UCSRB |= (1 << _isr);
}

//----------------------------------------------------------------------//

void Disable_isr(const UartNum _adrs, const UartISR _isr)
{
	UCSRB &= ~(1 << _isr);
}

//----------------------------------------------------------------------//

YesNo Is_enabled_isr(const UartNum _adrs, const UartISR _isr)
{
	return (YesNo)((UCSRB >> _isr) & 1);
}

//----------------------------------------------------------------------//

YesNo Is_request_isr(const UartNum _adrs, const UartISR _isr)
{
	return (YesNo)((UCSRA >> _isr) & 1);
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
