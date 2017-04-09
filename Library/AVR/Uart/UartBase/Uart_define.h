
#pragma once

//bit UCSRA
#define RXC  7		//受信完了フラグ
#define TXC	 6		//送信完了フラグ
#define UDRE 5		//送信データ空きレジスタフラグ
#define FE	 4		//フレーミング異常フラグ
#define DOR  3		//データオーバーランフラグ
#define UPE  2		//パリティ誤りフラグ
#define U2X  1		//倍速許可
#define MPCM 0		//複数プロセッサ通信動作

//bit UCSRB
#define RXCIE 7		//受信完了割り込み許可
#define TXCIE 6		//送信完了割り込み許可
#define UDRIE 5		//送信データレジスタ空き割り込み許可
#define RXEN  4		//受信許可
#define TXEN  3		//送信許可
#define UCSZ2 2		//データビット長選択2
#define RXB8  1		//受信データビット8
#define TXB8  0		//送信データビット8

//bit UCSRC
#define UMSEL1 7	//USART動作選択1
#define UMSEL0 6	//USART動作選択0
#define UPM1   5	//パリティ選択1
#define UPM0   4	//パリティ選択0
#define USBS   3	//停止ビット選択
#define UCSZ1  2	//データビット長選択1
#define UCSZ0  1	//データビット長選択0
#define UCPOL  0	//クロック極性選択

