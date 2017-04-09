
#pragma once

#include "Controller.h"

class Dualshock2 : public Controller
{
public:
	
	Dualshock2 (UartNum _adrs_uart);
	Dualshock2 (UartNum _adrs_uart, BOOL _is_poss_rewrite);
	
	Btn Get_Tri ();
	Btn Get_Cro ();
	Btn Get_Cir ();
	Btn Get_Squ ();
	
	Btn Get_R1 ();
	Btn Get_R2 ();
	Btn Get_R3 ();
	
	Btn Get_L1 ();
	Btn Get_L2 ();
	Btn Get_L3 ();
	
	void LCD_Tri(LcdAdrs _adrs);
	void LCD_Cro(LcdAdrs _adrs);
	void LCD_Cir(LcdAdrs _adrs);
	void LCD_Squ(LcdAdrs _adrs);
	
	void LCD_R1(LcdAdrs _adrs);
	void LCD_R2(LcdAdrs _adrs);
	void LCD_R3(LcdAdrs _adrs);
	
	void LCD_L1(LcdAdrs _adrs);
	void LCD_L2(LcdAdrs _adrs);
	void LCD_L3(LcdAdrs _adrs);
};

#include "Dualshock2_inline.h"
