
#pragma once

#include "IoBase/IoBase.h"

/************************************************************************/

class IoOut : public ClassIO :: IoBase
{
public:
	
	IoOut();
	IoOut(IoAdrs _io_adrs);
	
	void Reset(IoAdrs _io_adrs);
	
	void Out(uByte _out_data);
	void Out(BOOL _is_high, IoBit _bit);
	
	void Out_high(IoBit _bit);
	void Out_low(IoBit _bit);
};

/************************************************************************/

class IoIn : public ClassIO :: IoBase
{
public:
	
	IoIn();
	IoIn(IoAdrs _io_adrs);
	
	void Reset(IoAdrs _io_adrs);
	
	uByte In();
	BOOL In(IoBit _bit);
};

/************************************************************************/

class IoOutBit : public ClassIO :: IoBase
{
	IoBit _mem_bit :3;
	
public:
	
	IoOutBit();
	IoOutBit(IoAdrs _io_adrs, IoBit _bit);
	
	void Reset(IoAdrs _io_adrs, IoBit _bit);
	
	void Out(BOOL _is_high);
	
	void Out_low();
	void Out_high();
};

/************************************************************************/

class IoInBit : public ClassIO :: IoBase
{
	IoBit _mem_bit :3;
	
public:
	
	IoInBit();
	IoInBit(IoAdrs _io_adrs, IoBit _bit);
	
	void Reset(IoAdrs _io_adrs, IoBit _bit);
	
	BOOL In();
};

/************************************************************************/

#include "IO_inline.h"
