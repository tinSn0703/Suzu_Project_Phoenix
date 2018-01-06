
#include <avr/io.h>
#include <Others/BOOL.h>
#include <AVR/IO/IoBase/IoBase.h>

/************************************************************************/

namespace IO
{

namespace BaseClass
{

/************************************************************************/

//----------------------------------------------------------------------//

static inline void Write_PORTA(uByte _data)	{	PORTA = _data;	}
static inline void Write_PORTB(uByte _data)	{	PORTB = _data;	}
static inline void Write_PORTC(uByte _data)	{	PORTC = _data;	}
static inline void Write_PORTD(uByte _data)	{	PORTD = _data;	}

//----------------------------------------------------------------------//

static inline uByte Read_PORTA()	{	return PORTA;	}
static inline uByte Read_PORTB()	{	return PORTB;	}
static inline uByte Read_PORTC()	{	return PORTC;	}
static inline uByte Read_PORTD()	{	return PORTD;	}

//----------------------------------------------------------------------//

static inline uByte Read_PINA()	{	return PINA;	}
static inline uByte Read_PINB()	{	return PINB;	}
static inline uByte Read_PINC()	{	return PINC;	}
static inline uByte Read_PIND()	{	return PIND;	}

//----------------------------------------------------------------------//

#ifdef _AVR_IOM640_H_

//----------------------------------------------------------------------//
	
static inline void Write_PORTE(uByte _data)	{	PORTE = _data;	}
static inline void Write_PORTF(uByte _data)	{	PORTF = _data;	}
static inline void Write_PORTG(uByte _data)	{	PORTG = _data;	}
static inline void Write_PORTH(uByte _data)	{	PORTH = _data;	}
static inline void Write_PORTJ(uByte _data)	{	PORTJ = _data;	}
static inline void Write_PORTK(uByte _data)	{	PORTK = _data;	}

//----------------------------------------------------------------------//

static inline uByte Read_PORTE()	{	return PORTE;	}
static inline uByte Read_PORTF()	{	return PORTF;	}
static inline uByte Read_PORTG()	{	return PORTG;	}
static inline uByte Read_PORTH()	{	return PORTH;	}
static inline uByte Read_PORTJ()	{	return PORTJ;	}
static inline uByte Read_PORTK()	{	return PORTK;	}

//----------------------------------------------------------------------//

static inline uByte Read_PINE()	{	return PINE;	}
static inline uByte Read_PINF()	{	return PINF;	}
static inline uByte Read_PING()	{	return PING;	}
static inline uByte Read_PINH()	{	return PINH;	}
static inline uByte Read_PINJ()	{	return PINJ;	}
static inline uByte Read_PINK()	{	return PINK;	}

//----------------------------------------------------------------------//

#endif

/************************************************************************/
/*	IoBase																*/
/************************************************************************/

//----------------------------------------------------------------------//

IoBase :: IoBase()	{}

//----------------------------------------------------------------------//

IoBase :: IoBase (const IoNum _io_adrs, const uByte _set_in_or_out)
{
	Initialize(_io_adrs, _set_in_or_out);
}

//----------------------------------------------------------------------//

IoBase :: IoBase
(
	const IoNum	_io_adrs, 
	const IoBit	_bit, 
	const YesNo	_is_out_mode
)
{
	Initialize(_io_adrs, _bit, _is_out_mode);
}

//----------------------------------------------------------------------//

void IoBase :: Initialize
(
	const IoNum	_io_adrs, 
	const IoBit	_bit, 
	const YesNo	_is_out_mode
)
{
	_mem_io_adrs = _io_adrs;
	
	Set_DDR(_bit, _is_out_mode);
	
	Set_r_port();
	Set_w_port();
	Set_r_pin();
}

//----------------------------------------------------------------------//

void IoBase :: Initialize(const IoNum _io_adrs, const uByte _set_in_or_out)
{
	_mem_io_adrs = _io_adrs;
	
	Set_DDR(_set_in_or_out);
	
	Set_r_port();
	Set_w_port();
	Set_r_pin();
}

//----------------------------------------------------------------------//

void IoBase :: Set_DDR (const uByte _set_in_or_out)
{
	switch (Get_num())
	{
		case IO::NUM_A:	DDRA = _set_in_or_out;	break;
		case IO::NUM_B:	DDRB = _set_in_or_out;	break;
		case IO::NUM_C:	DDRC = _set_in_or_out;	break;
		case IO::NUM_D:	DDRD = _set_in_or_out;	break;
		
#ifdef _AVR_IOM640_H_
		
		case IO::NUM_E:	DDRE = _set_in_or_out;	break;
		case IO::NUM_F:	DDRF = _set_in_or_out;	break;
		case IO::NUM_G:	DDRG = _set_in_or_out;	break;
		case IO::NUM_H:	DDRH = _set_in_or_out;	break;
		case IO::NUM_J:	DDRJ = _set_in_or_out;	break;
		case IO::NUM_K:	DDRK = _set_in_or_out;	break;
		
#endif
		
	};
}

//----------------------------------------------------------------------//

void IoBase :: Set_DDR (const IoBit _bit, const BOOL _is_out_mode)
{
	switch (Get_num())
	{
		case IO::NUM_A:	DDRA &= ~(1<< _bit);	DDRA |= (_is_out_mode << _bit);	break;
		case IO::NUM_B:	DDRB &= ~(1<< _bit);	DDRB |= (_is_out_mode << _bit);	break;
		case IO::NUM_C:	DDRC &= ~(1<< _bit);	DDRC |= (_is_out_mode << _bit);	break;
		case IO::NUM_D:	DDRD &= ~(1<< _bit);	DDRD |= (_is_out_mode << _bit);	break;
		
#ifdef _AVR_IOM640_H_
		
		case IO::NUM_E:	DDRE &= ~(1<< _bit);	DDRE |= (_is_out_mode << _bit);	break;
		case IO::NUM_F:	DDRF &= ~(1<< _bit);	DDRF |= (_is_out_mode << _bit);	break;
		case IO::NUM_G:	DDRG &= ~(1<< _bit);	DDRG |= (_is_out_mode << _bit);	break;
		case IO::NUM_H:	DDRH &= ~(1<< _bit);	DDRH |= (_is_out_mode << _bit);	break;
		case IO::NUM_J:	DDRJ &= ~(1<< _bit);	DDRJ |= (_is_out_mode << _bit);	break;
		case IO::NUM_K:	DDRK &= ~(1<< _bit);	DDRK |= (_is_out_mode << _bit);	break;
		
#endif
		
	};
}

//----------------------------------------------------------------------//

void IoBase :: Set_r_pin()
{
	switch (Get_num())
	{
		case IO::NUM_A:	_r_pin = Read_PINA;	break;
		case IO::NUM_B:	_r_pin = Read_PINB;	break;
		case IO::NUM_C:	_r_pin = Read_PINC;	break;
		case IO::NUM_D:	_r_pin = Read_PIND;	break;
		
#ifdef _AVR_IOM640_H_
		
		case IO::NUM_E:	_r_pin = Read_PINE;	break;
		case IO::NUM_F:	_r_pin = Read_PINF;	break;
		case IO::NUM_G:	_r_pin = Read_PING;	break;
		case IO::NUM_H:	_r_pin = Read_PINH;	break;
		case IO::NUM_J:	_r_pin = Read_PINJ;	break;
		case IO::NUM_K:	_r_pin = Read_PINK;	break;
		
#endif
		
	};
}

//----------------------------------------------------------------------//

void IoBase :: Set_r_port()
{
	switch (Get_num())
	{
		case IO::NUM_A:	_r_port = Read_PORTA;	break;
		case IO::NUM_B:	_r_port = Read_PORTB;	break;
		case IO::NUM_C:	_r_port = Read_PORTC;	break;
		case IO::NUM_D:	_r_port = Read_PORTD;	break;
		
#ifdef _AVR_IOM640_H_
		
		case IO::NUM_E:	_r_port = Read_PORTE;	break;
		case IO::NUM_F:	_r_port = Read_PORTF;	break;
		case IO::NUM_G:	_r_port = Read_PORTG;	break;
		case IO::NUM_H:	_r_port = Read_PORTH;	break;
		case IO::NUM_J:	_r_port = Read_PORTJ;	break;
		case IO::NUM_K:	_r_port = Read_PORTK;	break;
		
#endif
		
	};
}

//----------------------------------------------------------------------//

void IoBase :: Set_w_port()
{
	switch (Get_num())
	{
		case IO::NUM_A:	_w_port = Write_PORTA;	break;
		case IO::NUM_B:	_w_port = Write_PORTB;	break;
		case IO::NUM_C:	_w_port = Write_PORTC;	break;
		case IO::NUM_D:	_w_port = Write_PORTD;	break;
		
#ifdef _AVR_IOM640_H_
		
		case IO::NUM_E:	_w_port = Write_PORTE;	break;
		case IO::NUM_F:	_w_port = Write_PORTF;	break;
		case IO::NUM_G:	_w_port = Write_PORTG;	break;
		case IO::NUM_H:	_w_port = Write_PORTH;	break;
		case IO::NUM_J:	_w_port = Write_PORTJ;	break;
		case IO::NUM_K:	_w_port = Write_PORTK;	break;
		
#endif
		
	};
}

//----------------------------------------------------------------------//

void IoBase :: Enable_isr()
{
	if (_mem_io_adrs)
	{
		
	}
}

//----------------------------------------------------------------------//

//----------------------------------------------------------------------//

/************************************************************************/

};

};

/************************************************************************/
