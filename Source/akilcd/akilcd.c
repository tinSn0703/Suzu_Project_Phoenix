
/************************************************************************/

#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>

#include <akilcd/akilcd.h>
#include <akilcd/akilcd_define/akilcd_NewMainCircit.h>

/************************************************************************/

//aaaa

#ifdef _AKILCD_H_

#define BIT_RS	(1 << RS)
#define BIT_RW	(1 << RW)
#define BIT_EN	(1 << EN)
#define BIT_DB4	(1 << DB4)
#define BIT_DB5	(1 << DB5)
#define BIT_DB6	(1 << DB6)
#define BIT_DB7	(1 << DB7)

#define LOW_RS()	(	PORT_RS  &= ~BIT_RS		)
#define LOW_RW()	(	PORT_RW  &= ~BIT_RW		)
#define LOW_EN()	(	PORT_EN  &= ~BIT_EN		)
#define LOW_DB4()	(	PORT_DB4 &= ~BIT_DB4	)
#define LOW_DB5()	(	PORT_DB5 &= ~BIT_DB5	)
#define LOW_DB6()	(	PORT_DB6 &= ~BIT_DB6	)
#define LOW_DB7()	(	PORT_DB7 &= ~BIT_DB7	)

#define HIGH_RS()	(	PORT_RS  |= BIT_RS	)
#define HIGH_RW()	(	PORT_RW  |= BIT_RW	)
#define HIGH_EN()	(	PORT_EN  |= BIT_EN	)
#define HIGH_DB4()	(	PORT_DB4 |= BIT_DB4	)
#define HIGH_DB5()	(	PORT_DB5 |= BIT_DB5	)
#define HIGH_DB6()	(	PORT_DB6 |= BIT_DB6	)
#define HIGH_DB7()	(	PORT_DB7 |= BIT_DB7	)

#endif

/************************************************************************/

#ifdef _AKILCD_H_

/************************************************************************/

//----------------------------------------------------------------------//

static void Enable_writting_LCD ()
{
	_delay_us(25);
	HIGH_EN();
	_delay_us(25);
	LOW_EN();
	_delay_us(25);
}

//----------------------------------------------------------------------//

static void Write_data_bit_7_to_4(const unsigned char data)
{
	((data & (1 << 7)) ? HIGH_DB7() : LOW_DB7());
	((data & (1 << 6)) ? HIGH_DB6() : LOW_DB6());
	((data & (1 << 5)) ? HIGH_DB5() : LOW_DB5());
	((data & (1 << 4)) ? HIGH_DB4() : LOW_DB4());
	
	Enable_writting_LCD();	
}

//----------------------------------------------------------------------//

static void Write_data_bit_3_to_0(const unsigned char data)
{
	((data & (1 << 3)) ? HIGH_DB7() : LOW_DB7());
	((data & (1 << 2)) ? HIGH_DB6() : LOW_DB6());
	((data & (1 << 1)) ? HIGH_DB5() : LOW_DB5());
	((data & (1 << 0)) ? HIGH_DB4() : LOW_DB4());
	
	Enable_writting_LCD();
}

//----------------------------------------------------------------------//

static inline void Write_LCD_0(const unsigned char data)
{
	LOW_RW();
	LOW_RS();
	
	Write_data_bit_7_to_4(data);
}

//----------------------------------------------------------------------//

static inline void Write_LCD_1(const unsigned char data)
{
	LOW_RW();
	LOW_RS();
	
	Write_data_bit_7_to_4(data);
	Write_data_bit_3_to_0(data);
}

//----------------------------------------------------------------------//

static inline void Write_LCD_2(const unsigned char data)
{
	LOW_RW();
	HIGH_RS();
	
	Write_data_bit_7_to_4(data);
	Write_data_bit_3_to_0(data);

	LOW_RS();
}

//----------------------------------------------------------------------//

static inline void Init_port_LCD()
{
	DDR_RS   |=  BIT_RS;	LOW_RS();
	DDR_RW   |=  BIT_RW;	LOW_RW();
	DDR_EN   |=  BIT_EN;	LOW_EN();
	DDR_DB4  |=  BIT_DB4;	LOW_DB4();
	DDR_DB5  |=  BIT_DB5;	LOW_DB5();
	DDR_DB6  |=  BIT_DB6;	LOW_DB6();
	DDR_DB7  |=  BIT_DB7;	LOW_DB7();
}

//----------------------------------------------------------------------//

static inline void Write_adrress(const LcdAdrs _adrs)
{
	Write_LCD_1(_adrs | 0b10000000);
}

//----------------------------------------------------------------------//

static void Wait_time(const int _ms)
{
	for (int i = 0; i < _ms; i ++)
	{
		_delay_ms(1);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

#endif

/************************************************************************/

//----------------------------------------------------------------------//

void INI_LCD()
{
	
#ifdef _AKILCD_H_
	
	Init_port_LCD();
	
	_delay_ms(50);
	
	Write_LCD_0(0b00110000);	//function set(8bit)
	_delay_ms(5);
	
	Write_LCD_0(0b00110000);	//function set(8bit)
	_delay_ms(1);
	
	Write_LCD_0(0b00110000);	//function set(8bit)
	_delay_ms(1);
	
	Write_LCD_0(0b00100000);	//function set(4bit)
	_delay_ms(4);
	
	Write_LCD_1(0b00101000);	//function set(interface str : 4bit) function set(1/16duety 5*7dot)
	_delay_ms(4);
	
	Write_LCD_1(0b00001111);
	_delay_ms(4);
	
	Write_LCD_1(0b00000110);	//entry mode set
	_delay_ms(4);
	
	Write_LCD_1(0b00000001);
	_delay_ms(6);
	
#endif
	
}

//----------------------------------------------------------------------//

int IS_LCD_INI()
{
	
#ifdef _AKILCD_H_
	
	return ((DDR_RS >> RS) & (DDR_RW >> RW) & (DDR_EN >> EN) & 1);
	
#endif
	
}

//----------------------------------------------------------------------//

void CLR_DISPLAY()
{
	
#ifdef _AKILCD_H_
	
	Write_LCD_1(0b00000001);
	_delay_ms(2);
	
#endif
	
}

//----------------------------------------------------------------------//

void PUT_LCD(const LcdAdrs _adrs, const char _char)
{
	
#ifdef _AKILCD_H_
	
	Write_adrress(_adrs);
	
	Write_LCD_2(_char);
	
#endif
	
}

//----------------------------------------------------------------------//

void STR_LCD(const LcdAdrs _adrs, const char _str[])
{
	
#ifdef _AKILCD_H_
	
	Write_adrress(_adrs);

	for (unsigned int i = 0; _str[i] != '\0'; i++)
	{
		Write_LCD_2(_str[i]);
	}
	
#endif
	
}

//----------------------------------------------------------------------//

void STR_LCD_WAVE(const LcdAdrs _adrs, const char _str[], const int _ms)
{
	
#ifdef _AKILCD_H_
	
	Write_adrress(_adrs);
	
	for (unsigned int i = 0; _str[i] != '\0'; i++)
	{
		Write_LCD_2(_str[i]);
		
		Wait_time(_ms);
	}
	
#endif
	
}

//----------------------------------------------------------------------//

void PUT_NUM
(
	const LcdAdrs	_arg_adrs,
	unsigned long	_number,
	const Digit		_digit,
	const Decimal	_decimal
)
{
	
#ifdef _AKILCD_H_
	
	static const char _temp_char[16] =
	{
		'0' , '1' , '2' , '3' ,
		'4' , '5' , '6' , '7' ,
		'8' , '9' , 'a' , 'b' ,
		'c' , 'd' , 'e' , 'f'
	};
	
	char _str[_digit + 1];
	
	for (short int i = (_digit - 1); i > -1; i--)
	{
		_str[i] = _temp_char[_number % _decimal];
		
		_number /= (unsigned long)_decimal;
	}
	
	_str[_digit] = '\0';
	
	STR_LCD(_arg_adrs, _str);
	
#endif
	
}

//----------------------------------------------------------------------//

/************************************************************************/
