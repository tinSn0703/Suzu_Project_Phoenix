/*
 * BT_def.h
 *
 * Created: 2017/02/27 17:20:34
 *  Author: Suzu
 */ 


#pragma once

/************************************************************************/

#ifndef CTS
#	define CTS PD4
#endif
#ifndef RTS
#	define RTS PD5
#endif
#ifndef RSE
#	define RSE PD6
#endif

#ifndef DDR_CTS
#	define DDR_CTS DDRD
#endif
#ifndef DDR_RTS
#	define DDR_RTS DDRD
#endif
#ifndef DDR_RSE
#	define DDR_RSE DDRD
#endif

#ifndef PIN_CTS
#	define PIN_CTS PIND
#endif
#ifndef PIN_RTS
#	define PIN_RTS PIND
#endif
#ifndef PIN_RSE
#	define PIN_RSE PIND
#endif

#ifndef PORT_CTS
#	define PORT_CTS PORTD
#endif
#ifndef PORT_RTS
#	define PORT_RTS PORTD
#endif
#ifndef PORT_RSE
#	define PORT_RSE PORTD
#endif

#define CTS_BIT (1 << CTS)
#define RTS_BIT (1 << RTS)
#define RSE_BIT (1 << RSE)

#define CTS_READ ((BOOL)((PIN_CTS >> CTS) & 1))
#define RTS_READ ((BOOL)((PIN_RTS >> RTS) & 1))
#define RSE_READ ((BOOL)((PIN_RSE >> RSE) & 1))

#define CTS_HIGH (PORT_CTS |=  CTS_BIT)
#define RTS_HIGH (PORT_RTS |=  RTS_BIT)
#define RSE_HIGH (PORT_RSE |=  RSE_BIT)

#define CTS_LOW (PORT_CTS &= ~CTS_BIT)
#define RTS_LOW (PORT_RTS &= ~RTS_BIT)
#define RSE_LOW (PORT_RSE &= ~RSE_BIT)

/************************************************************************/

#ifndef UART_ADRS_BT
#	define UART_ADRS_BT UART_ADRS_1
#endif

#define BT_UCSRA	_SFR_MEM8(UART_ADRS_BT + 0)
#define BT_UCSRB	_SFR_MEM8(UART_ADRS_BT + 1)
#define BT_UCSRC	_SFR_MEM8(UART_ADRS_BT + 2)
#define BT_UBRRL	_SFR_MEM8(UART_ADRS_BT + 4)
#define BT_UBRRH	_SFR_MEM8(UART_ADRS_BT + 5)
#define BT_UDR		_SFR_MEM8(UART_ADRS_BT + 6)

#define BT_RXCIE_ON		(BT_UCSRB |=  (1 << RXCIE))
#define BT_RXCIE_OFF	(BT_UCSRB &= ~(1 << RXCIE))

/************************************************************************/
