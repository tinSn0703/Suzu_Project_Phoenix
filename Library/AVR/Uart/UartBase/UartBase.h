
#pragma once

#include "Uart_type.h"
#include "Uart_define.h"

/************************************************************************/

namespace ClassUart
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

class UartBase
{
private:
	
	UartNum _mem_uart_adrs :9;
	
protected:
	
	void Initialize();
	void Initialize(UartNum _adrs);
	
public:
	
	UartBase();
	UartBase(UartNum _uart_adrs);
	
	UartNum Get_uart_num();
};

/************************************************************************/

class UartSet : public UartBase
{
protected:
	
	void Enable_UCSRB(usint _bit);
	void Disable_UCSRB(usint _bit);
	BOOL Is_true_the_UCSRB(usint _bit);
	
	UartData8bit Read_UDR();
	
	void Write_UDR(UartData8bit _write);
	
public:
	
	UartSet();
	UartSet(UartNum _uart_adrs);
	
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

};

/************************************************************************/
