
#pragma once

/************************************************************************/

//UARTのデータを表す型
typedef DataBit8	UartData8bit;
typedef DataBit16	UartData9bit;

/************************************************************************/

//----------------------------------------------------------------------//

//UARTの番号を表す型
typedef enum
{
	UART_NUM_N = 0x00,
	
	UART_NUM_0 = 0xc0,
	UART_NUM_1 = 0xc8,
	UART_NUM_2 = 0xd0,
	UART_NUM_3 = 0x130,
}
UartNum;

//----------------------------------------------------------------------//

//UARTの割り込みを表す型
typedef enum
{
	RECEIVE_COMPLETE	= 7,	//RXCIE
	TRANSMIT_COMPLETE	= 6,	//TXCIE
	UDR_EMPATY			= 5,	//UDRIE
}
UartISR;

//----------------------------------------------------------------------//

/************************************************************************/
