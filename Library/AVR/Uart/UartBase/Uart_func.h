
#pragma once

#include "Uart_type.h"
#include "Uart_define.h"

/************************************************************************/

#define _UCSRA_	_SFR_MEM8(_adrs  + 0)
#define _UCSRB_	_SFR_MEM8(_adrs  + 1)
#define _UCSRC_	_SFR_MEM8(_adrs  + 2)
#define _UBRRL_	_SFR_MEM8(_adrs  + 4)
#define _UBRRH_	_SFR_MEM8(_adrs  + 5)
#define _UDR_	_SFR_MEM8(_adrs  + 6)
#define _UBRR_	_SFR_MEM16(_adrs + 4)

/************************************************************************/

void UART_Init (UartNum _adrs);

void UART_Init_details (UartNum _adrs, unsigned short int _ubrr, unsigned char _parity);

UartData8bit UART_Receive_8bit (UartNum _adrs);

UartData9bit UART_Receive_9bit (UartNum _adrs);

void UART_Transmit_8bit (UartNum _adrs, UartData9bit _data);

void UART_Transmit_9bit (UartNum _adrs, UartData9bit _data);

/************************************************************************/

#include "Uart_func_inline.h"

#ifndef _UART_SOURCE_
#	undef _UCSRA_
#	undef _UCSRB_
#	undef _UCSRC_
#	undef _UBRRL_
#	undef _UBRRH_
#	undef _UDR_
#	undef _UBRR_
#endif
