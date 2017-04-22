

#pragma once

/************************************************************************/

#include "ControllerData/ControllerData.h"

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

namespace ClassController
{

/************************************************************************/

class ControllerBase
{
protected:
	
	Controller _mem_data;
	
	void Combine (const Byte _data[_NUM_CONTROLLER_UART_DATA_]);
	
public:
	
	ControllerBase () {}
	
	void Clear ();
};

/************************************************************************/

class ControllerGet : public virtual ControllerBase
{
private:
	
	int Get_base (Byte _bit, Byte _and);
	
protected:
	
	Btn Get_btn_North();
	Btn Get_btn_South();
	Btn Get_btn_East();
	Btn Get_btn_West();
	
	Btn Get_right_0();
	Btn Get_right_1();
	Btn Get_left_0();
	Btn Get_left_1();
	
	Btn Get_other_0();
	Btn Get_other_1();
	
public:
	
	ControllerGet() {}
	
	Btn Get_SELECT();
	Btn Get_START();
	
	DirecX Get_stick_Rx();
	DirecY Get_stick_Ry();
	DirecX Get_stick_Lx();
	DirecY Get_stick_Ly();
	DirecX Get_cross_x();
	DirecY Get_cross_y();
	
	ControllerData Get_data (sint _num);
	
	ullint Get_data ();
	
	Btn Get (ControllerBtn _bit);
	
	DirecX Get (ControllerDirecX _bit);
	DirecY Get (ControllerDirecY _bit);
	
	Btn operator [] (ControllerBtn _bit);
	
	DirecX operator [] (ControllerDirecX _bit);
	DirecY operator [] (ControllerDirecY _bit);
};

/************************************************************************/

class ControllerRewrite : public virtual ControllerBase
{
private:
	
	BOOL _mem_is_rewritten :1;
	
	void Rewrite_base (usint _bit, int _data, int _and);
		
public:
	
	ControllerRewrite (BOOL _is_rewritten);
	
	void Want_to_rewrite (YesNo _yes_no);
	
	void Rewrite_stick_R (DirecX _data);
	void Rewrite_stick_R (DirecY _data);
	
	void Rewrite_stick_L (DirecX _data);
	void Rewrite_stick_L (DirecY _data);
	
	void Rewrite_CROSS (DirecX _data);
	void Rewrite_CROSS (DirecY _data);
	
	void Rewrite (ControllerBtn _bit, BOOL _data);
	
	void Rewrite (ControllerDirecX _bit, DirecX _data);
	void Rewrite (ControllerDirecY _bit, DirecY _data);
};

/************************************************************************/

class ControllerPush : public virtual ControllerGet
{
private:
	
	DataBit16 _mem_is_pushed_btn :12;
	
	BOOL Is_enabled(int _btn);
	
	void Want_to_enable(int _btn, YesNo _yesno);
	
protected:
	
	Btn Push_btn_North();
	Btn Push_btn_South();
	Btn Push_btn_East();
	Btn Push_btn_West();
	
	Btn Push_right_0();
	Btn Push_right_1();
	Btn Push_left_0();
	Btn Push_left_1();
	
	Btn Push_other_0();
	Btn Push_other_1();
	
public:
	
	ControllerPush();
		
	Btn Push_SELECT();
	Btn Push_START();
	
	Btn Push(ControllerBtn _btn);
};

/************************************************************************/

class ControllerLCD : public virtual ControllerGet
{
private:
	
	void LCD_base (LcdAdrs _adrs, BOOL _data);
	void LCD_base (LcdAdrs _adrs, DirecX _data);
	void LCD_base (LcdAdrs _adrs, DirecY _data);
	
protected:
	
	void LCD_north (LcdAdrs _adrs);
	void LCD_south (LcdAdrs _adrs);
	void LCD_east (LcdAdrs _adrs);
	void LCD_west (LcdAdrs _adrs);
	
	void LCD_right_0 (LcdAdrs _adrs);
	void LCD_right_1 (LcdAdrs _adrs);
	void LCD_left_0 (LcdAdrs _adrs);
	void LCD_left_1 (LcdAdrs _adrs);
	
	void LCD_other_0 (LcdAdrs _adrs);
	void LCD_other_1 (LcdAdrs _adrs);
	
public:

	ControllerLCD () {}
	
	void LCD_SELECT (LcdAdrs _adrs);
	void LCD_START  (LcdAdrs _adrs);
	
	void LCD_stick_Rx (LcdAdrs _adrs);
	void LCD_stick_Ry (LcdAdrs _adrs);
	void LCD_stick_Lx (LcdAdrs _adrs);
	void LCD_stick_Ly (LcdAdrs _adrs);
	
	void LCD_CROSSx (LcdAdrs _adrs);
	void LCD_CROSSy (LcdAdrs _adrs);
	
	void LCD_data (LcdAdrs _adrs, usint _num);
	
	void LCD_data (LcdAdrs _adrs);
	
	void LCD (LcdAdrs _adrs, ControllerBtn _bit);
	void LCD (LcdAdrs _adrs, ControllerDirecX _bit);
	void LCD (LcdAdrs _adrs, ControllerDirecY _bit);
};

/************************************************************************/

#include "ControllerRead_inline.h"
#include "ControllerRewrite_inline.h"
#include "ControllerPush_inline.h"
#include "ControllerLCD_inline.h"

/************************************************************************/

};

/************************************************************************/

#endif //__cplusplus
