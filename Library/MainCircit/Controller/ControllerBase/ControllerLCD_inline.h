
#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_base (LcdAdrs _adrs, BOOL _data)
{	LCD_Write_num(_adrs, _data, 1, DECIMAL_02);	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_base (LcdAdrs _adrs, DirecX _data)
{	LCD_Write_num(_adrs, _data, 1, DECIMAL_10);	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_base (LcdAdrs _adrs, DirecY _data)
{	LCD_Write_num(_adrs, _data, 1, DECIMAL_10);	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_north (LcdAdrs _adrs)	
{	LCD_base(_adrs,Get_btn_North());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_south (LcdAdrs _adrs)	
{	LCD_base(_adrs,Get_btn_South());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_east (LcdAdrs _adrs)	
{	LCD_base(_adrs,Get_btn_East());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_west (LcdAdrs _adrs)	
{	LCD_base(_adrs,Get_btn_West());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_right_0 (LcdAdrs _adrs)	
{	LCD_base(_adrs,Get_right_0());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_right_1 (LcdAdrs _adrs)	
{	LCD_base(_adrs,Get_right_1());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_left_0 (LcdAdrs _adrs)
{	LCD_base(_adrs,Get_left_0());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_left_1 (LcdAdrs _adrs)	
{	LCD_base(_adrs,Get_left_1());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_other_0 (LcdAdrs _adrs)
{	LCD_base(_adrs,Get_other_0());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_other_1 (LcdAdrs _adrs)
{	LCD_base(_adrs,Get_other_1());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_SELECT	(LcdAdrs _adrs)
{	LCD_base(_adrs,Get_SELECT());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_START	(LcdAdrs _adrs)
{	LCD_base(_adrs,Get_START());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_stick_Rx (LcdAdrs _adrs)
{	LCD_base(_adrs,Get_stick_Rx());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_stick_Ry (LcdAdrs _adrs)
{	LCD_base(_adrs,Get_stick_Ry());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_stick_Lx (LcdAdrs _adrs)
{	LCD_base(_adrs,Get_stick_Lx());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_stick_Ly (LcdAdrs _adrs)
{	LCD_base(_adrs,Get_stick_Ly());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_CROSSx (LcdAdrs _adrs)
{	LCD_base(_adrs,Get_cross_x());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_CROSSy (LcdAdrs _adrs)
{	LCD_base(_adrs,Get_cross_y());	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_data(LcdAdrs _adrs, usint _num)
{	LCD_Display_num(_adrs, Get_data(_num), 2, DECIMAL_16);	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD_data(LcdAdrs _adrs)
{	LCD_Display_num(_adrs, _mem_data._all, 6, DECIMAL_16);	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD (LcdAdrs _adrs, ControllerBtn _bit)
{	LCD_base(_adrs,Get(_bit));	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD(LcdAdrs _adrs, ControllerDirecX _bit)
{	LCD_base(_adrs,Get(_bit));	}

//----------------------------------------------------------------------//

inline void ControllerLCD :: LCD(LcdAdrs _adrs, ControllerDirecY _bit)
{	LCD_base(_adrs,Get(_bit));	}

//----------------------------------------------------------------------//

/************************************************************************/
