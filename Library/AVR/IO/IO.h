
#pragma once

#if defined(__cplusplus)

#include "IoBase/IoBase.h"

/************************************************************************/

class IoOut : public ClassIO :: IoBase
{
public:
	
	IoOut(IoAdrs _io_adrs);
	
	void Out (Byte _out_data);
	void Out (BOOL _is_high, IoBit _bit);
	
	void Out_high (IoBit _bit);
	void Out_low	(IoBit _bit);
};

/************************************************************************/

class IoIn : public ClassIO :: IoBase
{
public:
	
	IoIn(IoAdrs _io_adrs);
	
	Byte In();
	BOOL In(IoBit _bit);
};

/************************************************************************/

class IoOutBit : public ClassIO :: IoBase
{
	IoBit _mem_bit :3;
	
public:
	
	IoOutBit(IoAdrs _io_adrs, IoBit _bit);
	
	void Out(BOOL _is_high);
	
	void Out_low();
	void Out_high();
};

/************************************************************************/

class IoInBit : public ClassIO :: IoBase
{
	IoBit _mem_bit :3;
	
public:
	
	IoInBit(IoAdrs _io_adrs, IoBit _bit);
	
	BOOL In();
};

/************************************************************************/

#else

#endif
