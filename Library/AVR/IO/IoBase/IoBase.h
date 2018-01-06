
#pragma once

/************************************************************************/

#include "IO_type.h"

/************************************************************************/

namespace ClassIO
{

/************************************************************************/

class IoBase
{
//variable
private:
	
	IoAdrs _mem_io_adrs :4;
	
//function
private:	
	
	fpReadPORT  _r_port;
	fpWritePORT _w_port;
	
	fpReadPIN _r_pin;
	
	void Set_DDR(IoBit _bit, BOOL _is_out_mode);
	void Set_DDR(uByte _set_in_or_out);
	
	void Set_r_pin();
	void Set_r_port();
	void Set_w_port();

protected:
	
	uByte PORT ();
	uByte PORT (uByte _data);
	uByte PORT (IoBit _bit, BOOL _is_on);
	
	uByte PIN ();
	
	void Initialize(IoAdrs _io_adrs, IoBit _bit, BOOL _is_out_mode);
	void Initialize(IoAdrs _io_adrs, uByte _set_in_or_out);
	
public:
	
	IoBase();
	IoBase(IoAdrs _io_adrs, IoBit _bit, YesNo _is_out_mode);
	IoBase(IoAdrs _io_adrs, uByte _set_in_or_out);
	
	IoAdrs Get_adrs();
};

/************************************************************************/

}

/************************************************************************/

#include "IoBase_inline.h"

/************************************************************************/
