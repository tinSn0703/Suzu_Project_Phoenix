
#pragma once

#include "Uart_type.h"
#include "Uart_define.h"

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

namespace ClassUart
{

/************************************************************************/

#define _UCSRA_	_SFR_MEM8(UartBase :: Get_uart_num()  + 0)
#define _UCSRB_	_SFR_MEM8(UartBase :: Get_uart_num()  + 1)
#define _UCSRC_	_SFR_MEM8(UartBase :: Get_uart_num()  + 2)
#define _UBRRL_	_SFR_MEM8(UartBase :: Get_uart_num()  + 4)
#define _UBRRH_	_SFR_MEM8(UartBase :: Get_uart_num()  + 5)
#define _UDR_	_SFR_MEM8(UartBase :: Get_uart_num()  + 6)
#define _UBRR_	_SFR_MEM16(UartBase :: Get_uart_num() + 4)

/************************************************************************/

class UartBase
{
private:
	
	UartNum _mem_uart_adrs :9;
	
protected:
	
	void Initialize ();
	void Initialize (UartNum _adrs);
	
public:
	
	UartBase ();
	UartBase (UartNum _uart_adrs);
	
	UartNum Get_uart_num();
};

/************************************************************************/

class UartSet : virtual protected UartBase
{
protected:
	
	void Enable_UCSRB(usint _bit);
	void Disable_UCSRB(usint _bit);
	BOOL Is_true_the_UCSRB(usint _bit);
	
public:
	
	UartSet ();
	UartSet (UartNum _uart_adrs);
	
	BOOL Is_it_receive();
	
	void Want_to_enable_9bit(YesNo _yes_or_no);
	void Enable_9bit();
	void Disable_9bit();
	YesNo Is_enabled_9bit();
	
	void Want_to_enable_isr(UartISR _isr, YesNo _yes_or_no);
	void Enable_isr(UartISR _isr);
	void Disable_isr(UartISR _isr);
	YesNo Is_enabled_isr(UartISR _isr);
};

/************************************************************************/

#include "UartBase_inline.h"

/************************************************************************/

#ifndef _UART_SOURCE_
#undef _UCSRA_
#undef _UCSRB_
#undef _UCSRC_
#undef _UBRRL_
#undef _UBRRH_
#undef _UDR_
#undef _UBRR_
#endif

/************************************************************************/

};

/************************************************************************/

#endif
