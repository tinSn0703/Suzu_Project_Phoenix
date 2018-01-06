
#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

static inline void Write_PORTA(uByte _data)	{	PORTA = _data;	}
static inline void Write_PORTB(uByte _data)	{	PORTB = _data;	}
static inline void Write_PORTC(uByte _data)	{	PORTC = _data;	}
static inline void Write_PORTD(uByte _data)	{	PORTD = _data;	}
static inline void Write_PORTE(uByte _data)	{	PORTE = _data;	}
static inline void Write_PORTF(uByte _data)	{	PORTF = _data;	}
static inline void Write_PORTG(uByte _data)	{	PORTG = _data;	}
static inline void Write_PORTH(uByte _data)	{	PORTH = _data;	}
static inline void Write_PORTJ(uByte _data)	{	PORTJ = _data;	}
static inline void Write_PORTK(uByte _data)	{	PORTK = _data;	}

//----------------------------------------------------------------------//

static inline uByte Read_PORTA()	{	return PORTA;	}
static inline uByte Read_PORTB()	{	return PORTB;	}
static inline uByte Read_PORTC()	{	return PORTC;	}
static inline uByte Read_PORTD()	{	return PORTD;	}
static inline uByte Read_PORTE()	{	return PORTE;	}
static inline uByte Read_PORTF()	{	return PORTF;	}
static inline uByte Read_PORTG()	{	return PORTG;	}
static inline uByte Read_PORTH()	{	return PORTH;	}
static inline uByte Read_PORTJ()	{	return PORTJ;	}
static inline uByte Read_PORTK()	{	return PORTK;	}

//----------------------------------------------------------------------//

static inline uByte Read_PINA()	{	return PINA;	}
static inline uByte Read_PINB()	{	return PINB;	}
static inline uByte Read_PINC()	{	return PINC;	}
static inline uByte Read_PIND()	{	return PIND;	}
static inline uByte Read_PINE()	{	return PINE;	}
static inline uByte Read_PINF()	{	return PINF;	}
static inline uByte Read_PING()	{	return PING;	}
static inline uByte Read_PINH()	{	return PINH;	}
static inline uByte Read_PINJ()	{	return PINJ;	}
static inline uByte Read_PINK()	{	return PINK;	}

//----------------------------------------------------------------------//

/************************************************************************/
