
/************************************************************************/

#include <avr/io.h>
#include <util/delay.h>

#include <akilcd/akilcd.h>
#include <akilcd/akilcd_define/akilcd_NewMainCircit.h>

/************************************************************************/

#define _BIT_RS_	(1 << RS)
#define _BIT_RW_	(1 << RW)
#define _BIT_EN_	(1 << EN)
#define _BIT_DB4_	(1 << DB4)
#define _BIT_DB5_	(1 << DB5)
#define _BIT_DB6_	(1 << DB6)
#define _BIT_DB7_	(1 << DB7)

#define _LOW_RS_	(	PORT_RS  &= ~_BIT_RS_	)
#define _LOW_RW_	(	PORT_RW  &= ~_BIT_RW_	)
#define _LOW_EN_	(	PORT_EN  &= ~_BIT_EN_	)
#define _LOW_DB4_	(	PORT_DB4 &= ~_BIT_DB4_	)
#define _LOW_DB5_	(	PORT_DB5 &= ~_BIT_DB5_	)
#define _LOW_DB6_	(	PORT_DB6 &= ~_BIT_DB6_	)
#define _LOW_DB7_	(	PORT_DB7 &= ~_BIT_DB7_	)

#define _HIGH_RS_	(	PORT_RS  |= _BIT_RS_	)
#define _HIGH_RW_	(	PORT_RW  |= _BIT_RW_	)
#define _HIGH_EN_	(	PORT_EN  |= _BIT_EN_	)
#define _HIGH_DB4_	(	PORT_DB4 |= _BIT_DB4_	)
#define _HIGH_DB5_	(	PORT_DB5 |= _BIT_DB5_	)
#define _HIGH_DB6_	(	PORT_DB6 |= _BIT_DB6_	)
#define _HIGH_DB7_	(	PORT_DB7 |= _BIT_DB7_	)

/************************************************************************/

static void Enable_writting_LCD ()
{
	_delay_us(25);
	_HIGH_EN_;
	_delay_us(25);
	_LOW_EN_;
	_delay_us(25);
}

//----------------------------------------------------------------------//

static inline void Write_LCD_0 (const unsigned char data)
{
	_LOW_RW_;
	_LOW_RS_;

	if (data & (1<<7))	_HIGH_DB7_;
	else				_LOW_DB7_;
	
	if (data & (1<<6))	_HIGH_DB6_;
	else				_LOW_DB6_;
	
	if (data & (1<<5))	_HIGH_DB5_;
	else				_LOW_DB5_;
	
	if (data & (1<<4))	_HIGH_DB4_;
	else				_LOW_DB4_;

	Enable_writting_LCD();
}

//----------------------------------------------------------------------//

static inline void Write_LCD_1 (const unsigned char data)
{
	_LOW_RW_;
	_LOW_RS_;

	if (data & (1<<7))	_HIGH_DB7_;	
	else				_LOW_DB7_;
		
	if (data & (1<<6))	_HIGH_DB6_;
	else				_LOW_DB6_;
	
	if (data & (1<<5))	_HIGH_DB5_;
	else				_LOW_DB5_;
	
	if (data & (1<<4))	_HIGH_DB4_;
	else				_LOW_DB4_;
	
	Enable_writting_LCD();

	if (data & (1<<3))	_HIGH_DB7_;
	else				_LOW_DB7_;
	
	if (data & (1<<2))	_HIGH_DB6_;
	else				_LOW_DB6_;
	
	if (data & (1<<1))	_HIGH_DB5_;
	else				_LOW_DB5_;
	
	if (data & (1<<0))	_HIGH_DB4_;
	else				_LOW_DB4_;
	
	Enable_writting_LCD();
}

//----------------------------------------------------------------------//

static inline void Write_LCD_2 (const unsigned char data)
{
	_LOW_RW_;
	_HIGH_RS_;

	if (data & (1<<7))	_HIGH_DB7_;
	else				_LOW_DB7_;
	
	if (data & (1<<6))	_HIGH_DB6_;
	else				_LOW_DB6_;
	
	if (data & (1<<5))	_HIGH_DB5_;
	else				_LOW_DB5_;
	
	if (data & (1<<4))	_HIGH_DB4_;
	else				_LOW_DB4_;
	
	Enable_writting_LCD();

	if (data & (1<<3))	_HIGH_DB7_;
	else				_LOW_DB7_;
	
	if (data & (1<<2))	_HIGH_DB6_;
	else				_LOW_DB6_;
	
	if (data & (1<<1))	_HIGH_DB5_;
	else				_LOW_DB5_;
	
	if (data & (1<<0))	_HIGH_DB4_;
	else				_LOW_DB4_;
	
	Enable_writting_LCD();

	_LOW_RS_;
}

//----------------------------------------------------------------------//

static inline void Init_port_LCD ()
{
	DDR_RS   |=  _BIT_RS_;	_LOW_RS_;
	DDR_RW   |=  _BIT_RW_;	_LOW_RW_;
	DDR_EN   |=  _BIT_EN_;	_LOW_EN_;
	DDR_DB4  |=  _BIT_DB4_;	_LOW_DB4_;
	DDR_DB5  |=  _BIT_DB5_;	_LOW_DB5_;
	DDR_DB6  |=  _BIT_DB6_;	_LOW_DB6_;
	DDR_DB7  |=  _BIT_DB7_;	_LOW_DB7_;
}

//----------------------------------------------------------------------//

static inline void Write_adrress (LcdAdrs _arg_adrs)
{
	_arg_adrs |= 0b10000000;
	Write_LCD_1(_arg_adrs);
}

//----------------------------------------------------------------------//

void INI_LCD ()
{
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
}

//----------------------------------------------------------------------//

void CLR_DISPLAY ()
{
	Write_LCD_1(0b00000001);
	_delay_ms(2);
}

//----------------------------------------------------------------------//

void PUT_LCD 
(
	const LcdAdrs	_arg_adrs, 
	const char		_arg_char
)
{
	Write_adrress(_arg_adrs);
	
	Write_LCD_2(_arg_char);
}

//----------------------------------------------------------------------//

void STR_LCD
(
	const LcdAdrs	_arg_adrs,
	const char		_arg_str[]
)
{
	Write_adrress(_arg_adrs);

	for (unsigned int i = 0; _arg_str[i] != '\0'; i++)
	{
		Write_LCD_2(_arg_str[i]);
	}
}

//----------------------------------------------------------------------//

void PUT_NUM
(
	const LcdAdrs	_arg_adrs,
	unsigned long	_arg_put_num,
	const Digit		_arg_digit,
	const Decimal	_arg_decimal
)
{
	static const char _temp_str[16] =
	{
		'0' , '1' , '2' , '3' ,
		'4' , '5' , '6' , '7' ,
		'8' , '9' , 'a' , 'b' ,
		'c' , 'd' , 'e' , 'f'
	};
	
	char _str[_arg_digit + 1];
	
	for (short int i = (_arg_digit - 1); i > -1; i--)
	{
		_str[i] = _temp_str[_arg_put_num % _arg_decimal];
		
		_arg_put_num /= (unsigned long)_arg_decimal;
	}
	
	_str[_arg_digit] = '\0';
	
	STR_LCD(_arg_adrs,_str);
}

//----------------------------------------------------------------------//

/************************************************************************/

#undef RS
#undef RW
#undef EN
#undef DB4
#undef DB5
#undef DB6
#undef DB7

#undef DDR_RS
#undef DDR_RW
#undef DDR_EN
#undef DDR_DB4
#undef DDR_DB5
#undef DDR_DB6
#undef DDR_DB7

#undef PORT_RS
#undef PORT_RW
#undef PORT_EN
#undef PORT_DB4
#undef PORT_DB5
#undef PORT_DB6
#undef PORT_DB7

#undef _BIT_RS_
#undef _BIT_RW_
#undef _BIT_EN_
#undef _BIT_DB4_
#undef _BIT_DB5_
#undef _BIT_DB6_
#undef _BIT_DB7_

#undef _LOW_RS_
#undef _LOW_RW_
#undef _LOW_EN_
#undef _LOW_DB4_
#undef _LOW_DB5_
#undef _LOW_DB6_
#undef _LOW_DB7_

#undef _HIGH_RS_
#undef _HIGH_RW_
#undef _HIGH_EN_
#undef _HIGH_DB4_
#undef _HIGH_DB5_
#undef _HIGH_DB6_
#undef _HIGH_DB7_

/************************************************************************/
