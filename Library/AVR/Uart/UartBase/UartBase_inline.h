
#pragma once

/************************************************************************/
/*	UartBase															*/
/************************************************************************/

inline UartNum UartBase :: Get_uart_num ()
{
	return _mem_uart_adrs;
}

/************************************************************************/
/*	UartSet																*/
/************************************************************************/

//----------------------------------------------------------------------//

inline void UartSet :: Enable_UCSRB (usint _bit)
{
	UCSRB |= (1 << _bit);
}

//----------------------------------------------------------------------//

inline void UartSet :: Disable_UCSRB (usint _bit)
{
	UCSRB &= ~(1 << _bit);
}

//----------------------------------------------------------------------//

inline BOOL UartSet :: Is_true_the_UCSRB (usint _bit)
{
	return Is_true_the(UCSRB, _bit);
}

//----------------------------------------------------------------------//

inline BOOL UartSet :: Is_it_receive()
{
	return Is_true_the(UCSRA, RXC);
}

//----------------------------------------------------------------------//

inline UartData8bit UartSet :: Read_UDR()
{
	return UDR;
}

//----------------------------------------------------------------------//

inline void UartSet :: Write_UDR(const UartData8bit _write)
{
	UDR = _write;
}

//----------------------------------------------------------------------//

inline void UartSet :: Enable_9bit()
{
	Enable_UCSRB(UCSZ2);
}

//----------------------------------------------------------------------//

inline void UartSet :: Disable_9bit()
{
	Disable_UCSRB(UCSZ2);
}

//----------------------------------------------------------------------//

inline YesNo UartSet :: Is_enabled_9bit()
{
	return Is_true_the_UCSRB(UCSZ2);
}

//----------------------------------------------------------------------//

inline void UartSet :: Enable_isr(const UartISR _isr)
{
	Enable_UCSRB(_isr);
}

//----------------------------------------------------------------------//

inline void UartSet :: Disable_isr(const UartISR _isr)
{
	Disable_UCSRB(_isr);
}

//----------------------------------------------------------------------//

inline YesNo UartSet :: Is_enabled_isr(const UartISR _isr)
{
	return Is_true_the_UCSRB(_isr);
}

//----------------------------------------------------------------------//
