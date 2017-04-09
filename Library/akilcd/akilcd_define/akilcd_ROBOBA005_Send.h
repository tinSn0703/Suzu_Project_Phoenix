
/*************************************************************************

	ROBOBA005送信回路でLCDを使用する際に、このヘッダをインクルードしてください

*************************************************************************/

#ifndef _AKILCD_H_
#define _AKILCD_H_ 1

#define RS	2
#define RW	1
#define EN	0
#define DB4	0
#define DB5	1
#define DB6	2
#define DB7	3

#define DDR_RS	DDRB
#define DDR_RW	DDRB
#define DDR_EN	DDRB
#define DDR_DB4	DDRA
#define DDR_DB5	DDRA
#define DDR_DB6	DDRA
#define DDR_DB7	DDRA

#define PORT_RS		PORTB
#define PORT_RW		PORTB
#define PORT_EN		PORTB
#define PORT_DB4	PORTA
#define PORT_DB5	PORTA
#define PORT_DB6	PORTA
#define PORT_DB7	PORTA

#endif	/*	_AKILCD_H_	*/