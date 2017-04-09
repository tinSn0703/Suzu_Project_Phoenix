
#pragma once

/************************************************************************/

#include "IO_type.h"

/************************************************************************/

namespace ClassIO
{

/************************************************************************/

class IoBase
{
private:
	
	IoAdrs _mem_io_adrs :4;
	
	fpReadPORT  _r_port;
	fpWritePORT _w_port;
	
	fpReadPIN _r_pin;
	
	void Set_DDR(IoBit _bit, BOOL _is_out_mode);
	void Set_DDR(Byte _set_in_or_out);
	
	void Set_r_pin();
	void Set_r_port();
	void Set_w_port();

protected:
	
	Byte PORT ();
	void PORT (Byte _data);
	
	Byte PIN ();
	
	void Initialize(IoAdrs _io_adrs, IoBit _bit, BOOL _is_out_mode);
	void Initialize(IoAdrs _io_adrs, Byte _set_in_or_out);
	
public:
	
	IoBase();
	IoBase(IoAdrs _io_adrs, IoBit _bit, BOOL _is_out_mode);
	IoBase(IoAdrs _io_adrs, Byte _set_in_or_out);
	
	IoAdrs Get_adrs();
};

/************************************************************************/

#include "IoBase_inline.h"

/************************************************************************/

}

/************************************************************************/
