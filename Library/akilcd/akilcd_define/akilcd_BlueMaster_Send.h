
/*************************************************************************

	BlueMaster送信回路でLCDを使用する際に、このヘッダをインクルードしてください

*************************************************************************/

#ifndef _AKILCD_H_
#define _AKILCD_H_ 1

#define RS	7
#define RW	0
#define EN	1
#define DB4	2
#define DB5	3
#define DB6	4
#define DB7	5

#define DDR_RS	DDRC
#define DDR_RW	DDRC
#define DDR_EN	DDRC
#define DDR_DB4	DDRC
#define DDR_DB5	DDRC
#define DDR_DB6	DDRC
#define DDR_DB7	DDRC

#define PORT_RS		PORTC
#define PORT_RW		PORTC
#define PORT_EN		PORTC
#define PORT_DB4	PORTC
#define PORT_DB5	PORTC
#define PORT_DB6	PORTC
#define PORT_DB7	PORTC

#endif	/*_AKILCD_H_*/