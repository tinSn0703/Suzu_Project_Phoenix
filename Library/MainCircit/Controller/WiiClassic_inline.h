

#pragma once

//----------------------------------------------------------------------//

inline BOOL WiiClassic :: Get_X ()	{	return Get_btn_North();	}

//----------------------------------------------------------------------//

inline BOOL WiiClassic :: Get_B ()	{	return Get_btn_South();	}

//----------------------------------------------------------------------//

inline BOOL WiiClassic :: Get_A ()	{	return Get_btn_East();	}

//----------------------------------------------------------------------//

inline BOOL WiiClassic :: Get_Y ()	{	return Get_btn_West();	}

//----------------------------------------------------------------------//

inline BOOL WiiClassic :: Get_R ()	{	return Get_right_0();	}

//----------------------------------------------------------------------//

inline BOOL WiiClassic :: Get_ZR ()	{	return Get_right_1();	}

//----------------------------------------------------------------------//

inline BOOL WiiClassic :: Get_L ()	{	return Get_left_0();	}

//----------------------------------------------------------------------//

inline BOOL WiiClassic :: Get_ZL ()	{	return Get_left_1();	}

//----------------------------------------------------------------------//

inline BOOL WiiClassic :: Get_HOME()	{	return Get_other_0();	}

//----------------------------------------------------------------------//

inline void WiiClassic :: LCD_X(LcdAdrs _adrs)	{	LCD_north(_adrs);	}

//----------------------------------------------------------------------//

inline void WiiClassic :: LCD_B(LcdAdrs _adrs)	{	LCD_south(_adrs);	}

//----------------------------------------------------------------------//

inline void WiiClassic :: LCD_A(LcdAdrs _adrs)	{	LCD_east(_adrs);	}

//----------------------------------------------------------------------//

inline void WiiClassic :: LCD_Y(LcdAdrs _adrs)	{	LCD_west(_adrs);	}

//----------------------------------------------------------------------//

inline void WiiClassic :: LCD_R(LcdAdrs _adrs)	{	LCD_right_0(_adrs);	}

//----------------------------------------------------------------------//

inline void WiiClassic :: LCD_ZR(LcdAdrs _adrs)	{	LCD_right_1(_adrs);	}

//----------------------------------------------------------------------//

inline void WiiClassic :: LCD_L(LcdAdrs _adrs)	{	LCD_left_0(_adrs);	}

//----------------------------------------------------------------------//

inline void WiiClassic :: LCD_ZL(LcdAdrs _adrs)	{	LCD_left_1(_adrs);	}

//----------------------------------------------------------------------//

inline void WiiClassic :: LCD_HOME(LcdAdrs _adrs)	{	LCD_other_0(_adrs);	}

//----------------------------------------------------------------------//
