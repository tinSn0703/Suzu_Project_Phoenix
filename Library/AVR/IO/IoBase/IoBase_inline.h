
#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline IoAdrs IoBase :: Get_adrs()
{
	return _mem_io_adrs;
}

//----------------------------------------------------------------------//

inline Byte IoBase :: PORT ()
{
	return (*_r_port)();
}

//----------------------------------------------------------------------//

inline void IoBase :: PORT (Byte _data)
{
	return (*_w_port)(_data);
}

//----------------------------------------------------------------------//

inline Byte IoBase :: PIN ()
{
	return (*_r_pin)();
}

//----------------------------------------------------------------------//

/************************************************************************/

