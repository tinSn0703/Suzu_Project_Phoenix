
/***********************************************************
akilcd.c
void INI_LCD_PORT(void);
void INI_LCD(void);
void LCD_ON_OFF(unsigned char d,unsigned char c,unsigned char b);
void CLR_DISPLAY(void);
void CLR(void);
void CURSOL_HOME(void)
void SI_CTRL(unsigned char d);
void SIFTL(void);
void ENABLE(void);
void PUT_LCD(unsigned char data);----------------CHAR
void ADRS_SET(unsigned char adrs);
void STR_LCD(unsigned char adrs,char* data);-----STR
void STR_LCD2(char* data);
void WRITE1(unsigned char data);
void WRITE2(unsigned char data);
void WRITE3(unsigned char data);
void PUT_2BYTE(unsigned short data);
void PUT_BYTE(unsigned char data);
void PUT_NUM(unsigned char adrs,unsigned long data,unsigned char num,unsigned char n);
***********************************************************/

#ifdef _AKILCD_ORIGINAL_C_

#include "akilcd_original.h"

void ENABLE(void)
{
	_delay_us(25)	;
	PORT_EN	|=	(1<<EN)	;
	_delay_us(25)	;
	PORT_EN	&=	(~(1<<EN))	;
	_delay_us(25)	;
	
}
void WRITE1(unsigned char data)
{
	PORT_RW &=~(1<<RW)	;
	PORT_RS &=~(1<<RS)	;

	if(data&(1<<7))		PORT_DB7 |=(1<<DB7)	;
	else				PORT_DB7 &=~(1<<DB7)	;
	if(data&(1<<6))		PORT_DB6 |=(1<<DB6)	;
	else				PORT_DB6 &=~(1<<DB6)	;
	if(data&(1<<5))		PORT_DB5 |=(1<<DB5)	;
	else				PORT_DB5 &=~(1<<DB5)	;
	if(data&(1<<4))		PORT_DB4 |=(1<<DB4)	;
	else				PORT_DB4 &=~(1<<DB4)	;
	ENABLE()	;

}
void WRITE2(unsigned char data)
{
	PORT_RW &=~(1<<RW)	;
	PORT_RS &=~(1<<RS)	;

	if(data&(1<<7))		PORT_DB7 |=(1<<DB7)	;
	else				PORT_DB7 &=~(1<<DB7)	;
	if(data&(1<<6))		PORT_DB6 |=(1<<DB6)	;
	else				PORT_DB6 &=~(1<<DB6)	;
	if(data&(1<<5))		PORT_DB5 |=(1<<DB5)	;
	else				PORT_DB5 &=~(1<<DB5)	;
	if(data&(1<<4))		PORT_DB4 |=(1<<DB4)	;
	else				PORT_DB4 &=~(1<<DB4)	;
	ENABLE()	;

	if(data&(1<<3))		PORT_DB7 |=(1<<DB7)	;
	else				PORT_DB7 &=~(1<<DB7)	;
	if(data&(1<<2))		PORT_DB6 |=(1<<DB6)	;
	else				PORT_DB6 &=~(1<<DB6)	;
	if(data&(1<<1))		PORT_DB5 |=(1<<DB5)	;
	else				PORT_DB5 &=~(1<<DB5)	;
	if(data&(1<<0))		PORT_DB4 |=(1<<DB4)	;
	else				PORT_DB4 &=~(1<<DB4)	;
	ENABLE()	;
}
void WRITE3(unsigned char data)
{
	PORT_RW &=~(1<<RW)	;
	PORT_RS |=(1<<RS)	;

	if(data&(1<<7))		PORT_DB7 |=(1<<DB7)	;
	else				PORT_DB7 &=~(1<<DB7)	;
	if(data&(1<<6))		PORT_DB6 |=(1<<DB6)	;
	else				PORT_DB6 &=~(1<<DB6)	;
	if(data&(1<<5))		PORT_DB5 |=(1<<DB5)	;
	else				PORT_DB5 &=~(1<<DB5)	;
	if(data&(1<<4))		PORT_DB4 |=(1<<DB4)	;
	else				PORT_DB4 &=~(1<<DB4)	;
	ENABLE()	;

	if(data&(1<<3))		PORT_DB7 |=(1<<DB7)	;
	else				PORT_DB7 &=~(1<<DB7)	;
	if(data&(1<<2))		PORT_DB6 |=(1<<DB6)	;
	else				PORT_DB6 &=~(1<<DB6)	;
	if(data&(1<<1))		PORT_DB5 |=(1<<DB5)	;
	else				PORT_DB5 &=~(1<<DB5)	;
	if(data&(1<<0))		PORT_DB4 |=(1<<DB4)	;
	else				PORT_DB4 &=~(1<<DB4)	;
	ENABLE()	;

	PORT_RS &=~(1<<RS)	;
}

void INI_LCD_PORT(void)
{
	DDR_RS  |=(1<<RS);
	PORT_RS &=~(1<<RS);

	DDR_RW  |=(1<<RW);
	PORT_RW &=~(1<<RW);

	DDR_EN  |=(1<<EN);
	PORT_EN &=~(1<<EN);

	DDR_DB4  |=(1<<DB4);
	PORT_DB4 &=~(1<<DB4);

	DDR_DB5  |=(1<<DB5);
	PORT_DB5 &=~(1<<DB5);

	DDR_DB6  |=(1<<DB6);
	PORT_DB6 &=~(1<<DB6);

	DDR_DB7  |=(1<<DB7);
	PORT_DB7 &=~(1<<DB7);
}

void CLR_DISPLAY(void)
{
	WRITE2(0b00000001)	;
	_delay_ms(2)	;
}
void LCD_ON_OFF(unsigned char d,unsigned char c,unsigned char b)
{
	unsigned char t	=	0b00001000;
	if(d == 1)	t	|=	(1<<2)	;
	if(c == 1)	t	|=	(1<<1)	;
	if(b == 1)	t	|=	(1<<0)	;
	
	WRITE2(t)	;
	
}

void INI_LCD(void)
{
	PORT_RW	&=	(~(1<<RW))	;	//R/W
	PORT_RS	&=	(~(1<<RS))	;	//RS

	WRITE1(0b00110000)	;	//function set(8bit)
	
	_delay_ms(5)	;
	
	WRITE1(0b00110000)	;	//function set(8bit)
	
	_delay_ms(1)	;
	
	WRITE1(0b00110000)	;	//function set(8bit)
	
	_delay_ms(1)	;
	
	WRITE1(0b00100000)	;	//function set(4bit)
	
	_delay_ms(4)	;
	
	WRITE2(0b00101000)	;	//function set(interface data : 4bit)
	//function set(1/16duety 5*7dot)
	_delay_ms(4)	;
	
	LCD_ON_OFF(1,1,1)	;
	
	_delay_ms(4)	;

	WRITE2(0b00000110)	;	//entry mode set
	
	_delay_ms(4);
	
	CLR_DISPLAY()	;
	
	_delay_ms(4)	;

}

void CURSOL_HOME(void)
{
	_delay_ms(1)	;
	WRITE2(0b00000010);
	_delay_ms(1)	;
}

void CLR(void)
{
	CLR_DISPLAY();
	CURSOL_HOME()	;
	LCD_ON_OFF(1,1,1)	;
}

void SIFTL(void)
{
	_delay_ms(500)	;
	WRITE2(0b00011000)	;
}

void SI_CTRL(unsigned char d)
{
	unsigned char k;
	for(k=0;k<=d;k++)
	{
		SIFTL() ;
	}
	
}

void PUT_LCD(unsigned char data)
{
	_delay_ms(1)	;
	WRITE3(data)	;
	_delay_ms(1)	;
}

void ADRS_SET(unsigned char adrs)
{
	adrs |=0b10000000;
	WRITE2(adrs)	;
}
void STR_LCD(unsigned char adrs,const char* data)
{
	ADRS_SET(adrs)	;

	while(*data != 0)
	{
		WRITE3(*data)	;
		
		data++ ;
	}
	data=0x00;
}

void STR_LCD2(const char* data)
{
	while(*data != 0)
	{
		WRITE3(*data)	;
		
		data++ ;
	}
	data=0x00;
}

void PUT_2BYTE(unsigned short data)
{
	unsigned char i;
	STR_LCD(0x00,"DATA=");
	ADRS_SET(0x40);
	for(i=16;i>0;i--)
	{
		if(data&(1<<(i-1)))
		PUT_LCD('1');
		else
		PUT_LCD('0');
	}
}
void PUT_BYTE(unsigned char data)
{
	unsigned char i;
	STR_LCD(0x00,"DATA=");
	ADRS_SET(0x40);
	for(i=8;i>0;i--)
	{
		if(data&(1<<(i-1)))
		PUT_LCD('1');
		else
		PUT_LCD('0');
	}
}

void PUT_NUM(unsigned char adrs,unsigned long data,unsigned char num,unsigned char n)
{
	unsigned char i;
	unsigned char CHARA[num];
	char str[num+1];

	for(i=0;i<num;i++)
	{
		CHARA[(num-1)-i] = (unsigned char)(data%n);
		data /=n;
	}
	for(i=0;i<num;i++)
	{
		if(CHARA[i] == 0)
		str[i]='0';
		else if(CHARA[i] == 1)
		str[i]='1';
		else if(CHARA[i] == 2)
		str[i]='2';
		else if(CHARA[i] == 3)
		str[i]='3';
		else if(CHARA[i] == 4)
		str[i]='4';
		else if(CHARA[i] == 5)
		str[i]='5';
		else if(CHARA[i] == 6)
		str[i]='6';
		else if(CHARA[i] == 7)
		str[i]='7';
		else if(CHARA[i] == 8)
		str[i]='8';
		else if(CHARA[i] == 9)
		str[i]='9';
		else if(CHARA[i] == 0xa)
		str[i]='a';
		else if(CHARA[i] == 0xb)
		str[i]='b';
		else if(CHARA[i] == 0xc)
		str[i]='c';
		else if(CHARA[i] == 0xd)
		str[i]='d';
		else if(CHARA[i] == 0xe)
		str[i]='e';
		else if(CHARA[i] == 0xf)
		str[i]='f';
	}
	str[num]=0;
	STR_LCD(adrs,str);
}

#endif