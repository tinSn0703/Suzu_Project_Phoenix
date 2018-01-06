
#pragma once

#include "Uart_type.h"
#include "Uart_define.h"

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

void Initialize (UartNum _adrs);

void Initizlize_details (UartNum _adrs, unsigned short int _ubrr, unsigned char _parity);

UartData8bit Receive_8bit (UartNum _adrs);

UartData9bit Receive_9bit (UartNum _adrs);

void Transmit_8bit (UartNum _adrs, UartData9bit _data);

void Transmit_9bit (UartNum _adrs, UartData9bit _data);

/************************************************************************/

#ifndef _UART_SOURCE_
#	undef UCSRA
#	undef UCSRB
#	undef UCSRC
#	undef UBRRL
#	undef UBRRH
#	undef UDR
#	undef UBRR
#endif

/************************************************************************/

};

/************************************************************************/
