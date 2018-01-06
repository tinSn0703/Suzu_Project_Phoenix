
#pragma once

/************************************************************************/

#include "Valve_type.h"

/************************************************************************/

namespace ClassValve
{

/************************************************************************/

#define WAIT_MS_TIME 100

/************************************************************************/

//----------------------------------------------------------------------//

class ValveBase
{
//variable
protected:
	
	Valve _mem_data;
	
//function
public:
	
	ValveBase ();
	
	void Clear ();
};

//----------------------------------------------------------------------//

class ValveSet : public virtual ValveBase
{
//function
public:
	
	ValveSet();
	
	void Want_to_open_0(YesNo _yes);
	void Want_to_open_1(YesNo _yes);
	void Want_to_open_2(YesNo _yes);
	void Want_to_open_3(YesNo _yes);
	void Want_to_open_4(YesNo _yes);
	void Want_to_open_5(YesNo _yes);
	void Want_to_open_6(YesNo _yes);
	void Want_to_open_7(YesNo _yes);
	
	void Want_to_open(ValveNum _num, YesNo _yes);
	
	void Set(ValveData _data);
};

//----------------------------------------------------------------------//

class ValveGet : public virtual ValveBase
{
//function
public:
	
	ValveGet();
	
	BOOL Is_open_for_0();
	BOOL Is_open_for_1();
	BOOL Is_open_for_2();
	BOOL Is_open_for_3();
	BOOL Is_open_for_4();
	BOOL Is_open_for_5();
	BOOL Is_open_for_6();
	BOOL Is_open_for_7();
	
	BOOL Is_open_for(ValveNum _num);
	
	ValveData Get();
};

//----------------------------------------------------------------------//

class ValveOperate	: public virtual ValveSet
					, public virtual ValveGet
{
//variable
private:	
	
	CountValue _mem_timer[8];
	uByte _mem_is_move_enabled :8;
	
//function
protected:
	
	void Set_timer(ValveNum _num);
	BOOL Compare_timer(ValveNum _num);
	
	void Want_to_enable(ValveNum _num, YesNo _yes);	
	BOOL Is_enabled(ValveNum _num);
	void Reversal_enabled(ValveNum _num);
	
public:
	
	ValveOperate ();
	
	void Toggle (ValveNum _num);
	
	void Safety (ValveNum _num_a, ValveNum _num_b);
	
	void Open_or_Close (ValveNum _num, YesNo _is_move);	
	void Open_or_Close (ValveNum _num_a, ValveNum _num_b, YesNo _is_move);
	void Open_or_Close (ValveNum _num_a, YesNo _is_move_a, ValveNum _num_b, YesNo _is_move_b);
};

//----------------------------------------------------------------------//

class ValveLCD : public virtual ValveGet
{
//function
public:
	
	ValveLCD();
	
	void Display(LcdAdrs _adrs, ValveNum _num);
	void Display(LcdAdrs _adrs, Decimal _decimal);		
};

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/

#include "ValveBase_inline/ValveBase_inline.h"
#include "ValveBase_inline/ValveWrite_inline.h"
#include "ValveBase_inline/ValveRead_inline.h"

/************************************************************************/

