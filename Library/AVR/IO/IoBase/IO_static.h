
#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

static inline void Write_PORTA(Byte _data)	{	PORTA = _data;	}
static inline void Write_PORTB(Byte _data)	{	PORTB = _data;	}
static inline void Write_PORTC(Byte _data)	{	PORTC = _data;	}
static inline void Write_PORTD(Byte _data)	{	PORTD = _data;	}
static inline void Write_PORTE(Byte _data)	{	PORTE = _data;	}
static inline void Write_PORTF(Byte _data)	{	PORTF = _data;	}
static inline void Write_PORTG(Byte _data)	{	PORTG = _data;	}
static inline void Write_PORTH(Byte _data)	{	PORTH = _data;	}
static inline void Write_PORTJ(Byte _data)	{	PORTJ = _data;	}
static inline void Write_PORTK(Byte _data)	{	PORTK = _data;	}

//----------------------------------------------------------------------//

static inline Byte Read_PORTA()	{	return PORTA;	}
static inline Byte Read_PORTB()	{	return PORTB;	}
static inline Byte Read_PORTC()	{	return PORTC;	}
static inline Byte Read_PORTD()	{	return PORTD;	}
static inline Byte Read_PORTE()	{	return PORTE;	}
static inline Byte Read_PORTF()	{	return PORTF;	}
static inline Byte Read_PORTG()	{	return PORTG;	}
static inline Byte Read_PORTH()	{	return PORTH;	}
static inline Byte Read_PORTJ()	{	return PORTJ;	}
static inline Byte Read_PORTK()	{	return PORTK;	}

//----------------------------------------------------------------------//

static inline Byte Read_PINA()	{	return PINA;	}
static inline Byte Read_PINB()	{	return PINB;	}
static inline Byte Read_PINC()	{	return PINC;	}
static inline Byte Read_PIND()	{	return PIND;	}
static inline Byte Read_PINE()	{	return PINE;	}
static inline Byte Read_PINF()	{	return PINF;	}
static inline Byte Read_PING()	{	return PING;	}
static inline Byte Read_PINH()	{	return PINH;	}
static inline Byte Read_PINJ()	{	return PINJ;	}
static inline Byte Read_PINK()	{	return PINK;	}

//----------------------------------------------------------------------//

/************************************************************************/
