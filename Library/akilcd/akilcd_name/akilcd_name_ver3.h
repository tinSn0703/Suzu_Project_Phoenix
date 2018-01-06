
#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

/**
 *	�@������LCD�ɕ\������֐��B
 * 
 *	_adrs	: �\������ꏊ
 *	_char	: �\�����镶��
 */
inline void LCD_Write_char (const LcdAdrs _adrs, const char _char)
{
	PUT_LCD(_adrs, _char);
}

//----------------------------------------------------------------------// 

/**
 *	�@LCD�ɕ������\������֐��B
 * 
 *	_adrs	: �\���̐擪�̏ꏊ
 *	_str	: �\�����镶����
 */
inline void LCD_Write_str (const LcdAdrs _adrs, const char _str[])
{
	STR_LCD(_adrs, _str);
}

//----------------------------------------------------------------------//

/**
 *	�@���l��LCD�ɕ\������֐��B
 * 
 *	_adrs	: �\���̐擪�̏ꏊ
 *	_number	: �\�����鐔�l
 *	_digit	: �\������������
 *	decimal	: �\���������i�� (2 �` 16�i���܂�)
 */
inline void LCD_Write_num
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
