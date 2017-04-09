
#pragma once

#if defined(__cplusplus)

#include "IoBase/IoBase.h"

/************************************************************************/

class IoOut : public ClassIO :: IoBase
{
public:
	
	IoOut(IoAdrs _io_adrs);
	
	void Write (Byte _out_data);
	void Write (BOOL _is_high, IoBit _bit);
	
	void Write_high (IoBit _bit);
	void Write_low	(IoBit _bit);
};

/************************************************************************/

class IoIn : public ClassIO :: IoBase
{
public:
	
	IoIn(IoAdrs _io_adrs);
	
	Byte Read();
	BOOL Read(IoBit _bit);
};

/************************************************************************/

class IoOutBit : public ClassIO :: IoBase
{
	IoBit _mem_bit :3;
	
public:
	
	IoOutBit(IoAdrs _io_adrs, IoBit _bit);
	
	void Write(BOOL _is_high);
	
	void Write_low();
	void Write_high();
};

/************************************************************************/

class IoInBit : public ClassIO :: IoBase
{
	IoBit _mem_bit :3;
	
public:
	
	IoInBit(IoAdrs _io_adrs, IoBit _bit);
	
	BOOL Read();
};

/************************************************************************/

#else

#endif
