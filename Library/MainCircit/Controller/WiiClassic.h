
#pragma once

#include "Controller.h"

class WiiClassic : public Controller
{
public:
	
	WiiClassic (UartNum _adrs_uart);
	WiiClassic (UartNum _adrs_uart, BOOL _is_poss_rewrite);
	
	Btn Get_X ();
	Btn Get_B ();
	Btn Get_A ();
	Btn Get_Y ();
	
	Btn Get_R ();
	Btn Get_ZR ();
	
	Btn Get_L ();
	Btn Get_ZL ();
	
	Btn Get_HOME();
	
	void LCD_X(LcdAdrs _adrs);
	void LCD_B(LcdAdrs _adrs);
	void LCD_A(LcdAdrs _adrs);
	void LCD_Y(LcdAdrs _adrs);
	
	void LCD_R(LcdAdrs _adrs);
	void LCD_ZR(LcdAdrs _adrs);
	
	void LCD_L(LcdAdrs _adrs);
	void LCD_ZL(LcdAdrs _adrs);
	
	void LCD_HOME(LcdAdrs _adrs);
};

#include "WiiClassic_inline.h"
