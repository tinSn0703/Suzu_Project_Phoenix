
#pragma once

#ifdef __cplusplus

/************************************************************************/

#include "ValveData/ValveData.h"

/************************************************************************/

namespace ClassValve
{

/************************************************************************/

#define _WAIT_MS_TIME_ 100

/************************************************************************/

//----------------------------------------------------------------------//

class ValveBase
{
protected:
	
	Valve _mem_data;
	
public:
	
	ValveBase ();
	
	void Clear ();
};

//----------------------------------------------------------------------//

class ValveWrite : public virtual ValveBase
{
public:
	
	ValveWrite();
	
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

class ValveRead : public virtual ValveBase
{	
public:
	
	ValveRead();
	
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
	
	BOOL operator [] (ValveNum _num);
};

//----------------------------------------------------------------------//

class ValveOperate	: public virtual ValveWrite
					, public virtual ValveRead
{
private:	
	
	Time _mem_timer[8];
	Byte _mem_is_move_allow :8;
	
protected:
	
	void Set_timer(ValveNum _num);
	BOOL Comp_timer(ValveNum _num);
	
	void Can_allow(ValveNum _num, BOOL _yes);	
	BOOL Is_allow(ValveNum _num);
	void Reversal_allow(ValveNum _num);
	
public:
	
	ValveOperate ();
	
	void Toggle (ValveNum _num);
	
	void Confirm_safety (ValveNum _num_a, ValveNum _num_b);
	
	void OpenClose (ValveNum _num, BOOL _is_move);	
	void OpenClose (ValveNum _num_a, ValveNum _num_b, BOOL _is_move);
	void OpenClose (ValveNum _num_a, BOOL _is_move_a, ValveNum _num_b, BOOL _is_move_b);
};

//----------------------------------------------------------------------//

class ValveLCD : public virtual ValveRead
{
public:
	
	ValveLCD();
	
	void LCD(LcdAdrs _adrs, ValveNum _num);
	void LCD(LcdAdrs _adrs, Decimal _decimal);		
};

//----------------------------------------------------------------------//

/************************************************************************/

}

/************************************************************************/

#include "ValveBase_inline.h"
#include "ValveWrite_inline.h"
#include "ValveRead_inline.h"

/************************************************************************/

#endif /*__cplusplus*/

