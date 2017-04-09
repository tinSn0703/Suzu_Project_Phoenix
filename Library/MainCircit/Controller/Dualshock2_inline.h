

#pragma once

//----------------------------------------------------------------------//

inline BOOL Dualshock2 :: Get_Tri ()	{	return Get_btn_North();	}

//----------------------------------------------------------------------//

inline BOOL Dualshock2 :: Get_Cro ()	{	return Get_btn_South();	}

//----------------------------------------------------------------------//

inline BOOL Dualshock2 :: Get_Cir ()	{	return Get_btn_East();	}

//----------------------------------------------------------------------//

inline BOOL Dualshock2 :: Get_Squ ()	{	return Get_btn_West();	}

//----------------------------------------------------------------------//

inline BOOL Dualshock2 :: Get_R1 ()	{	return Get_right_0();	}

//----------------------------------------------------------------------//

inline BOOL Dualshock2 :: Get_R2 ()	{	return Get_right_1();	}

//----------------------------------------------------------------------//

inline BOOL Dualshock2 :: Get_R3 ()	{	return Get_other_1();	}

//----------------------------------------------------------------------//

inline BOOL Dualshock2 :: Get_L1 ()	{	return Get_left_0();	}

//----------------------------------------------------------------------//

inline BOOL Dualshock2 :: Get_L2 ()	{	return Get_left_1();	}

//----------------------------------------------------------------------//

inline BOOL Dualshock2 :: Get_L3 ()	{	return Get_other_0();	}

//----------------------------------------------------------------------//

inline void Dualshock2 :: LCD_Tri(LcdAdrs _adrs)	{	LCD_north(_adrs);	}

//----------------------------------------------------------------------//

inline void Dualshock2 :: LCD_Cro(LcdAdrs _adrs)	{	LCD_south(_adrs);	}

//----------------------------------------------------------------------//

inline void Dualshock2 :: LCD_Cir(LcdAdrs _adrs)	{	LCD_east(_adrs);	}

//----------------------------------------------------------------------//

inline void Dualshock2 :: LCD_Squ(LcdAdrs _adrs)	{	LCD_west(_adrs);	}

//----------------------------------------------------------------------//

inline void Dualshock2 :: LCD_R1(LcdAdrs _adrs)	{	LCD_right_0(_adrs);	}

//----------------------------------------------------------------------//

inline void Dualshock2 :: LCD_R2(LcdAdrs _adrs)	{	LCD_right_1(_adrs);	}

//----------------------------------------------------------------------//

inline void Dualshock2 :: LCD_R3(LcdAdrs _adrs)	{	LCD_other_1(_adrs);	}

//----------------------------------------------------------------------//

inline void Dualshock2 :: LCD_L1(LcdAdrs _adrs)	{	LCD_left_0(_adrs);	}

//----------------------------------------------------------------------//

inline void Dualshock2 :: LCD_L2(LcdAdrs _adrs)	{	LCD_left_1(_adrs);	}

//----------------------------------------------------------------------//

inline void Dualshock2 :: LCD_L3(LcdAdrs _adrs)	{	LCD_other_0(_adrs);	}

//----------------------------------------------------------------------//
