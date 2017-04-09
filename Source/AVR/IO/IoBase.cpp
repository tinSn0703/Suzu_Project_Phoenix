
#include <avr/io.h>
#include <Others/BOOL.h>
#include <AVR/IO/IoBase/IoBase.h>
#include <AVR/IO/IoBase/IO_static.h>

/************************************************************************/

namespace ClassIO
{

/************************************************************************/
/*	IoBase																*/
/************************************************************************/

//----------------------------------------------------------------------//

IoBase :: IoBase()	{}

//----------------------------------------------------------------------//

IoBase :: IoBase (const IoAdrs _io_adrs, const Byte _set_in_or_out)
{
	Initialize(_io_adrs, _set_in_or_out);
}

//----------------------------------------------------------------------//

IoBase :: IoBase 
(
	const IoAdrs	_io_adrs,
	const IoBit		_bit,
	const BOOL		_is_out_mode
)
{
	Initialize(_io_adrs, _bit, _is_out_mode);
}

//----------------------------------------------------------------------//

void IoBase :: Initialize
(
	const IoAdrs	_io_adrs, 
	const IoBit		_bit, 
	const BOOL		_is_out_mode
)
{
	_mem_io_adrs = _io_adrs;
	
	Set_DDR(_bit, _is_out_mode);
	
	Set_r_port();
	Set_w_port();
	Set_r_pin();
}

//----------------------------------------------------------------------//

void IoBase :: Initialize(const IoAdrs _io_adrs, const Byte _set_in_or_out)
{
	_mem_io_adrs = _io_adrs;
	
	Set_DDR(_set_in_or_out);
	
	Set_r_port();
	Set_w_port();
	Set_r_pin();
}

//----------------------------------------------------------------------//

void IoBase :: Set_DDR (const Byte _set_in_or_out)
{
	switch (IoBase :: Get_adrs())
	{
		case IO_ADRS_A:	DDRA = _set_in_or_out;	break;
		case IO_ADRS_B:	DDRB = _set_in_or_out;	break;
		case IO_ADRS_C:	DDRC = _set_in_or_out;	break;
		case IO_ADRS_D:	DDRD = _set_in_or_out;	break;
		case IO_ADRS_E:	DDRE = _set_in_or_out;	break;
		case IO_ADRS_F:	DDRF = _set_in_or_out;	break;
		case IO_ADRS_G:	DDRG = _set_in_or_out;	break;
		case IO_ADRS_H:	DDRH = _set_in_or_out;	break;
		case IO_ADRS_J:	DDRJ = _set_in_or_out;	break;
		case IO_ADRS_K:	DDRK = _set_in_or_out;	break;
	};
}

//----------------------------------------------------------------------//

void IoBase :: Set_DDR (const IoBit _bit, const BOOL _is_out_mode)
{
	switch (IoBase :: Get_adrs())
	{
		case IO_ADRS_A:	DDRA &= ~(1<< _bit);	DDRA |= (_is_out_mode << _bit);	break;
		case IO_ADRS_B:	DDRB &= ~(1<< _bit);	DDRB |= (_is_out_mode << _bit);	break;
		case IO_ADRS_C:	DDRC &= ~(1<< _bit);	DDRC |= (_is_out_mode << _bit);	break;
		case IO_ADRS_D:	DDRD &= ~(1<< _bit);	DDRD |= (_is_out_mode << _bit);	break;
		case IO_ADRS_E:	DDRE &= ~(1<< _bit);	DDRE |= (_is_out_mode << _bit);	break;
		case IO_ADRS_F:	DDRF &= ~(1<< _bit);	DDRF |= (_is_out_mode << _bit);	break;
		case IO_ADRS_G:	DDRG &= ~(1<< _bit);	DDRG |= (_is_out_mode << _bit);	break;
		case IO_ADRS_H:	DDRH &= ~(1<< _bit);	DDRH |= (_is_out_mode << _bit);	break;
		case IO_ADRS_J:	DDRJ &= ~(1<< _bit);	DDRJ |= (_is_out_mode << _bit);	break;
		case IO_ADRS_K:	DDRK &= ~(1<< _bit);	DDRK |= (_is_out_mode << _bit);	break;
	};
}

//----------------------------------------------------------------------//

void IoBase :: Set_r_pin()
{
	switch (IoBase :: Get_adrs())
	{
		case IO_ADRS_A:	_r_pin  = Read_PINA;	break;
		case IO_ADRS_B:	_r_pin  = Read_PINB;	break;
		case IO_ADRS_C:	_r_pin  = Read_PINC;	break;
		case IO_ADRS_D:	_r_pin  = Read_PIND;	break;
		case IO_ADRS_E:	_r_pin  = Read_PINE;	break;
		case IO_ADRS_F:	_r_pin  = Read_PINF;	break;
		case IO_ADRS_G:	_r_pin  = Read_PING;	break;
		case IO_ADRS_H:	_r_pin  = Read_PINH;	break;
		case IO_ADRS_J:	_r_pin  = Read_PINJ;	break;
		case IO_ADRS_K:	_r_pin  = Read_PINK;	break;
	};
}

//----------------------------------------------------------------------//

void IoBase :: Set_r_port()
{
	switch (IoBase :: Get_adrs())
	{
		case IO_ADRS_A:	_r_port = Read_PORTA;	break;
		case IO_ADRS_B:	_r_port = Read_PORTB;	break;
		case IO_ADRS_C:	_r_port = Read_PORTC;	break;
		case IO_ADRS_D:	_r_port = Read_PORTD;	break;
		case IO_ADRS_E:	_r_port = Read_PORTE;	break;
		case IO_ADRS_F:	_r_port = Read_PORTF;	break;
		case IO_ADRS_G:	_r_port = Read_PORTG;	break;
		case IO_ADRS_H:	_r_port = Read_PORTH;	break;
		case IO_ADRS_J:	_r_port = Read_PORTJ;	break;
		case IO_ADRS_K:	_r_port = Read_PORTK;	break;
	};
}

//----------------------------------------------------------------------//

void IoBase :: Set_w_port()
{
	switch (IoBase :: Get_adrs())
	{
		case IO_ADRS_A:	_w_port = Write_PORTA;	break;
		case IO_ADRS_B:	_w_port = Write_PORTB;	break;
		case IO_ADRS_C:	_w_port = Write_PORTC;	break;
		case IO_ADRS_D:	_w_port = Write_PORTD;	break;
		case IO_ADRS_E:	_w_port = Write_PORTE;	break;
		case IO_ADRS_F:	_w_port = Write_PORTF;	break;
		case IO_ADRS_G:	_w_port = Write_PORTG;	break;
		case IO_ADRS_H:	_w_port = Write_PORTH;	break;
		case IO_ADRS_J:	_w_port = Write_PORTJ;	break;
		case IO_ADRS_K:	_w_port = Write_PORTK;	break;
	};
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
