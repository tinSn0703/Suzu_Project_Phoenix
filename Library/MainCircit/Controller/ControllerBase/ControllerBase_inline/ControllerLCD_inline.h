
#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display_base (const LcdAdrs _adrs, const BOOL _data)
{
	LCD::Write(_adrs, _data, 1, DECIMAL_02);
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display_base (const LcdAdrs _adrs, const DirecX _data)
{
	LCD::Write(_adrs, _data, 1, DECIMAL_10);
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display_base (const LcdAdrs _adrs, const DirecY _data)
{
	LCD::Write(_adrs, _data, 1, DECIMAL_10);
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display_stick_Rx (LcdAdrs _adrs)
{
	Display_base(_adrs, Get_stick_Rx());
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display_stick_Ry (LcdAdrs _adrs)
{
	Display_base(_adrs, Get_stick_Ry());
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display_stick_Lx (LcdAdrs _adrs)
{
	Display_base(_adrs, Get_stick_Lx());
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display_stick_Ly (LcdAdrs _adrs)
{
	Display_base(_adrs, Get_stick_Ly());
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display_cross_x (LcdAdrs _adrs)
{
	Display_base(_adrs, Get_cross_x());
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display_cross_y (LcdAdrs _adrs)
{
	Display_base(_adrs, Get_cross_y());
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display_data(LcdAdrs _adrs, usint _num)
{
	LCD_Display_num(_adrs, Get_data(_num), 2, DECIMAL_16);
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display_data(LcdAdrs _adrs)
{
	LCD_Display_num(_adrs, _mem_data._all, 6, DECIMAL_16);
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display(const ControllerBtn _bit, const LcdAdrs _adrs)
{
	Display_base(_adrs, ControllerGet::operator [](_bit));
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display(const ControllerDirecX _bit, const LcdAdrs _adrs)
{
	Display_base(_adrs, ControllerGet::operator [](_bit));
}

//----------------------------------------------------------------------//

inline void ControllerLCD :: Display(const ControllerDirecY _bit, const LcdAdrs _adrs)
{
	Display_base(_adrs, ControllerGet::operator [](_bit));
}

//----------------------------------------------------------------------//

/************************************************************************/
