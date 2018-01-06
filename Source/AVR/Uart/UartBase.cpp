
/************************************************************************/

#include <avr/io.h>
#include <Others/BOOL.h>
#include <AVR/Uart/UartBase/UartBase.h>

/************************************************************************/

namespace Uart
{

namespace BaseClass
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
/*	UartBase															*/
/************************************************************************/

//----------------------------------------------------------------------//

UartBase :: UartBase(const UartNum _uart_num)
{
	_mem_uart_num = _uart_num;
	
	UBRR  = 0x0004;
	UCSRA = (1 << U2X);
	UCSRB &= ~((1 << RXEN) | (1 << TXEN) | (1 << UCSZ2) | (1 << RXCIE) | (1 << TXCIE) | (1 << UDRIE));
	UCSRC = ((1 << UPM1) | (1 << UPM0) | (1 << UCSZ1) | (1 << UCSZ0));
}

//----------------------------------------------------------------------//

void UartBase :: Enable_9bit()
{
	UCSRB |= (1 << UCSZ2);
}

//----------------------------------------------------------------------//

void UartBase :: Disable_9bit()
{
	UCSRB &= ~(1 << UCSZ2);
}

//----------------------------------------------------------------------//

YesNo UartBase :: Is_enabled_9bit()
{
	return Is_true_the(UCSRB, UCSZ2);
}

//----------------------------------------------------------------------//

void UartBase :: Enable_isr(const UartISR _isr)
{
	UCSRB |= (1 << _isr);
}

//----------------------------------------------------------------------//

void UartBase :: Disable_isr(const UartISR _isr)
{
	UCSRB &= ~(1 << _isr);
}

//----------------------------------------------------------------------//

YesNo UartBase :: Is_enabled_isr(const UartISR _isr)
{
	return Is_true_the(UCSRB, _isr);
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

/************************************************************************/
