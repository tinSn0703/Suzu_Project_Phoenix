
/************************************************************************/

#include <avr/io.h>
#include <util/delay.h>

#include <akilcd/akilcd.h>
#include <akilcd/akilcd_define/akilcd_NewMainCircit.h>

/************************************************************************/

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

/************************************************************************/

static void Enable_writting_LCD ()
{
	_delay_us(25);
	HIGH_EN();
	_delay_us(25);
	LOW_EN();
	_delay_us(25);
}

//----------------------------------------------------------------------//

static inline void Write_LCD_0 (const unsigned char data)
{
	LOW_RW();
	LOW_RS();

	if (data & (1<<7))	HIGH_DB7();
	else				LOW_DB7();
	
	if (data & (1<<6))	HIGH_DB6();
	else				LOW_DB6();
	
	if (data & (1<<5))	HIGH_DB5();
	else				LOW_DB5();
	
	if (data & (1<<4))	HIGH_DB4();
	else				LOW_DB4();

	Enable_writting_LCD();
}

//----------------------------------------------------------------------//

static inline void Write_LCD_1 (const unsigned char data)
{
	LOW_RW();
	LOW_RS();

	if (data & (1<<7))	HIGH_DB7();	
	else				LOW_DB7();
		
	if (data & (1<<6))	HIGH_DB6();
	else				LOW_DB6();
	
	if (data & (1<<5))	HIGH_DB5();
	else				LOW_DB5();
	
	if (data & (1<<4))	HIGH_DB4();
	else				LOW_DB4();
	
	Enable_writting_LCD();

	if (data & (1<<3))	HIGH_DB7();
	else				LOW_DB7();
	
	if (data & (1<<2))	HIGH_DB6();
	else				LOW_DB6();
	
	if (data & (1<<1))	HIGH_DB5();
	else				LOW_DB5();
	
	if (data & (1<<0))	HIGH_DB4();
	else				LOW_DB4();
	
	Enable_writting_LCD();
}

//----------------------------------------------------------------------//

static inline void Write_LCD_2 (const unsigned char data)
{
	LOW_RW();
	HIGH_RS();

	if (data & (1<<7))	HIGH_DB7();
	else				LOW_DB7();
	
	if (data & (1<<6))	HIGH_DB6();
	else				LOW_DB6();
	
	if (data & (1<<5))	HIGH_DB5();
	else				LOW_DB5();
	
	if (data & (1<<4))	HIGH_DB4();
	else				LOW_DB4();
	
	Enable_writting_LCD();

	if (data & (1<<3))	HIGH_DB7();
	else				LOW_DB7();
	
	if (data & (1<<2))	HIGH_DB6();
	else				LOW_DB6();
	
	if (data & (1<<1))	HIGH_DB5();
	else				LOW_DB5();
	
	if (data & (1<<0))	HIGH_DB4();
	else				LOW_DB4();
	
	Enable_writting_LCD();

	LOW_RS();
}

//----------------------------------------------------------------------//

static inline void Init_port_LCD ()
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

#undef BIT_RS
#undef BIT_RW
#undef BIT_EN
#undef BIT_DB4
#undef BIT_DB5
#undef BIT_DB6
#undef BIT_DB7

#undef LOW_RS
#undef LOW_RW
#undef LOW_EN
#undef LOW_DB4
#undef LOW_DB5
#undef LOW_DB6
#undef LOW_DB7

#undef HIGH_RS
#undef HIGH_RW
#undef HIGH_EN
#undef HIGH_DB4
#undef HIGH_DB5
#undef HIGH_DB6
#undef HIGH_DB7

/************************************************************************/
