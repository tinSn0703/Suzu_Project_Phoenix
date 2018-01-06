

#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline Btn WiiClassicGet :: Get_X ()
{
	return _mem_data._sub._btn_mark_o;
}

//----------------------------------------------------------------------//

inline Btn WiiClassicGet :: Get_B ()
{
	return _mem_data._sub._btn_mark_u;
}

//----------------------------------------------------------------------//

inline Btn WiiClassicGet :: Get_A ()
{
	return _mem_data._sub._btn_mark_r;
}

//----------------------------------------------------------------------//

inline Btn WiiClassicGet :: Get_Y ()
{
	return _mem_data._sub._btn_mark_l;
}

//----------------------------------------------------------------------//

inline Btn WiiClassicGet :: Get_R ()
{
	return _mem_data._sub._btn_right_0;
}

//----------------------------------------------------------------------//

inline Btn WiiClassicGet :: Get_ZR ()
{
	return _mem_data._sub._btn_right_1;
}

//----------------------------------------------------------------------//

inline Btn WiiClassicGet :: Get_L ()
{
	return _mem_data._sub._btn_left_0;
}

//----------------------------------------------------------------------//

inline Btn WiiClassicGet :: Get_ZL ()
{
	return _mem_data._sub._btn_left_1;
}

//----------------------------------------------------------------------//

inline Btn WiiClassicGet :: Get_HOME()
{
	return _mem_data._sub._btn_other_0;
}

//----------------------------------------------------------------------//

/************************************************************************/
