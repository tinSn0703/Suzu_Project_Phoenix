
/*************************************************************************

	AD変換回路でLCDを使用する際に、このヘッダをインクルードしてください

*************************************************************************/

#ifndef _AKILCD_H_
#define _AKILCD_H_ 1

#define RS	0
#define RW	7
#define EN	1
#define DB4	2
#define DB5	3
#define DB6	4
#define DB7	5

#define DDR_RS	DDRB
#define DDR_RW	DDRD
#define DDR_EN	DDRB
#define DDR_DB4	DDRB
#define DDR_DB5	DDRB
#define DDR_DB6	DDRB
#define DDR_DB7	DDRB

#define PORT_RS		PORTB
#define PORT_RW		PORTD
#define PORT_EN		PORTB
#define PORT_DB4	PORTB
#define PORT_DB5	PORTB
#define PORT_DB6	PORTB
#define PORT_DB7	PORTB

#endif	/*_AKILCD_H_*/