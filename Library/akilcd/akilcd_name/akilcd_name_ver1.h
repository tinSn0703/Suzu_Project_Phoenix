
#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

/**
 *	　LCDの表示を全て消す関数。
 */
inline void Lcd_clr_dis ()
{
	CLR_DISPLAY();	
}

//----------------------------------------------------------------------//

/**
 *	　文字をLCDに表示する関数。
 * 
 *	_adrs	: 表示する場所
 *	_char	: 表示する文字
 */
inline void Lcd_put_char (const LcdAdrs _adrs, const char _char)
{
	PUT_LCD(_adrs, _char);
}

//----------------------------------------------------------------------// 

/**
 *	　LCDに文字列を表示する関数。
 * 
 *	_adrs	: 表示の先頭の場所
 *	_str	: 表示する文字列
 */
inline void Lcd_put_str (const LcdAdrs _adrs, const char _str[])
{
	STR_LCD(_adrs, _str);
}

//----------------------------------------------------------------------//

/**
 *	　数値をLCDに表示する関数。
 * 
 *	_adrs	: 表示の先頭の場所
 *	_number	: 表示する数値
 *	_digit	: 表示したい桁数
 *	decimal	: 表示したい進数 (2 ～ 16進数まで)
 */
inline void Lcd_put_num
(
	const LcdAdrs	_adrs,
	unsigned long	_number,
	const Digit		_digit,
	const Decimal	_decimal
)
{
	PUT_NUM(_adrs, _number, _digit, _decimal);
}

//----------------------------------------------------------------------//

/************************************************************************/
