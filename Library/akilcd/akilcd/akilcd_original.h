
/*************************************************************************

	旧メイン回路でLCDを使用する際に、このヘッダをインクルードしてください

*************************************************************************/

#ifdef _AKILCD_ORIGINAL_H_

#include <avr/io.h>
#include <util/delay.h>

#define RS	6
#define RW	5
#define EN	4
#define DB4	3
#define DB5	2
#define DB6	1
#define DB7	0

#define DDR_RS	DDRA
#define DDR_RW	DDRA
#define DDR_EN	DDRA
#define DDR_DB4	DDRA
#define DDR_DB5	DDRA
#define DDR_DB6	DDRA
#define DDR_DB7	DDRA

#define PORT_RS		PORTA
#define PORT_RW		PORTA
#define PORT_EN		PORTA
#define PORT_DB4	PORTA
#define PORT_DB5	PORTA
#define PORT_DB6	PORTA
#define PORT_DB7	PORTA

#endif	/*_AKILCD_H_*/