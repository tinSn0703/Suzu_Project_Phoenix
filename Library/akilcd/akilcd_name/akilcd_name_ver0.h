
#pragma once

/************************************************************************/

#ifdef __cplusplus	//C++の時用

	extern "C"	{

#endif /*__cplusplus*/

/************************************************************************/

/**
 *	　プログラムによってはこの関数を使っているので。
 *	　中身は特にない。
 */
inline void INI_LCD_PORT()	{}

/**
 *	　LCDを使用可能な状態にする関数。
 *	　この関数を呼び出せば、LCDを使ことができます。
 */
void INI_LCD();

/**
 *	　LCDの表示を全て消す関数。
 */
void CLR_DISPLAY();

/**
 *	　文字をLCDに表示する関数。
 * 
 *	_adrs	: 表示する場所
 *	_char	: 表示する文字
 */
void PUT_LCD(LcdAdrs _adrs, const char _char);

/**
 *	　LCDに文字列を表示する関数。
 * 
 *	_adrs	: 表示の先頭の場所
 *	_str	: 表示する文字列
 */
void STR_LCD(LcdAdrs _adrs, const char _str[]);

/**
 *	　数値をLCDに表示する関数。
 * 
 *	_adrs		: 表示の先頭の場所
 *	_number		: 表示する数値
 *	_digit		: 表示したい桁数
 *	decimal		: 表示したい進数 (2 ～ 16進数まで)
 */
void PUT_NUM(LcdAdrs _adrs, unsigned long _number, Digit _digit, Decimal _decimal);

/************************************************************************/

#ifdef __cplusplus	//C++の時用

	}

#endif /*__cplusplus*/

/************************************************************************/
