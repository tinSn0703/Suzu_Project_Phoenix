

#pragma once

/************************************************************************/

#include "Controller_type.h"

/************************************************************************/

namespace ClassController
{

/************************************************************************/

class ControllerBase
{
protected:
	
	Controller _mem_data;
	
public:
	
	ControllerBase();
};

/************************************************************************/

class ControllerGet : public virtual ControllerBase
{
private:
	
	int Get_base(uByte _bit, uByte _and);
	
public:
	
	ControllerGet();
	
	DirecX Get_stick_Rx();
	DirecY Get_stick_Ry();
	DirecX Get_stick_Lx();
	DirecY Get_stick_Ly();
	DirecX Get_cross_x();
	DirecY Get_cross_y();
	
	ControllerData Get_data(sint _num);
	
	ullint Get_data();
	
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
	
	ControllerRewrite(BOOL _is_rewritten);
	
	void Want_to_rewrite(YesNo _yes_no);
	
	void Rewrite_stick_R(DirecX _data);
	void Rewrite_stick_R(DirecY _data);
	
	void Rewrite_stick_L(DirecX _data);
	void Rewrite_stick_L(DirecY _data);
	
	void Rewrite_cross(DirecX _data);
	void Rewrite_cross(DirecY _data);
	
	void Rewrite(ControllerBtn _bit, BOOL _data);
	
	void Rewrite(ControllerDirecX _bit, DirecX _data);
	void Rewrite(ControllerDirecY _bit, DirecY _data);
};

/************************************************************************/

class ControllerPush : public virtual ControllerGet
{
private:
	
	DataBit16 _mem_is_pushed_btn :12;
	
	BOOL Is_enabled(int _btn);
	
	void Want_to_enable(int _btn, YesNo _yesno);
	
public:
	
	ControllerPush();
	
	Btn Push(ControllerBtn _btn);
};

/************************************************************************/

class ControllerLCD : public virtual ControllerGet
{
private:
	
	void Display_base(LcdAdrs _adrs, BOOL _data);
	void Display_base(LcdAdrs _adrs, DirecX _data);
	void Display_base(LcdAdrs _adrs, DirecY _data);
	
public:

	ControllerLCD();
	
	void Display_stick_Rx(LcdAdrs _adrs);
	void Display_stick_Ry(LcdAdrs _adrs);
	void Display_stick_Lx(LcdAdrs _adrs);
	void Display_stick_Ly(LcdAdrs _adrs);
	
	void Display_cross_x(LcdAdrs _adrs);
	void Display_cross_y(LcdAdrs _adrs);
	
	void Display_data(LcdAdrs _adrs);
	void Display_data(LcdAdrs _adrs, usint _num);
	
	void Display(ControllerBtn _bit, LcdAdrs _adrs);
	void Display(ControllerDirecX _bit, LcdAdrs _adrs);
	void Display(ControllerDirecY _bit, LcdAdrs _adrs);
};

/************************************************************************/

#include "ControllerBase_inline/ControllerGet_inline.h"
#include "ControllerBase_inline/ControllerRewrite_inline.h"
#include "ControllerBase_inline/ControllerPush_inline.h"
#include "ControllerBase_inline/ControllerLCD_inline.h"

/************************************************************************/

};

/************************************************************************/
