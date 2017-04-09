/*
 * ValveBase.h
 *
 * Created: 2017/03/05 15:00:43
 *  Author: Suzu
 */ 


#pragma once

#ifdef __cplusplus

#include "ValveData/ValveData.h"

namespace ClassValve
{

#define _WAIT_MS_TIME_ 100

/************************************************************************/
/*	ValveBase															*/
/************************************************************************/
class ValveBase
{
protected:
	
	Valve _mem_data;
	
public:
	
	ValveBase ();
	
	void Clear ();
};

/************************************************************************/
/*	ValveWrite															*/
/************************************************************************/
class ValveWrite : public virtual ValveBase
{
private:

// 	typedef void (ValveWrite :: *TypeWrite)(BOOL );
// 	
// 	TypeWrite _mem_fp_Can_open[8];
	
public:
	
	ValveWrite();
	
	void Can_open_0 (BOOL _yes);
	void Can_open_1 (BOOL _yes);
	void Can_open_2 (BOOL _yes);
	void Can_open_3 (BOOL _yes);
	void Can_open_4 (BOOL _yes);
	void Can_open_5 (BOOL _yes);
	void Can_open_6 (BOOL _yes);
	void Can_open_7 (BOOL _yes);
	
	void Can_open (ValveNum _num, BOOL _yes);
	
	void Write (ValveData _data);
};

/************************************************************************/
/*	ValveToggle															*/
/************************************************************************/
// class ValveToggle : public virtual ValveBase
// {
// private:
// 	
// 	typedef void (ValveToggle :: *TypeToggle)();
// 	
// 	TypeToggle _mem_fp_Toggle[8];
// 	
// public:
// 
// 	ValveToggle();
// 	
// 	void Toggle_0 ();
// 	void Toggle_1 ();
// 	void Toggle_2 ();
// 	void Toggle_3 ();
// 	void Toggle_4 ();
// 	void Toggle_5 ();
// 	void Toggle_6 ();
// 	void Toggle_7 ();
// };

/************************************************************************/
/*	ValveRead															*/
/************************************************************************/
class ValveRead : public virtual ValveBase
{
private:
	
// 	typedef BOOL (ValveRead :: *TypeRead)();
// 	
// 	TypeRead _mem_fp_Is_open[8];
	
public:
	
	ValveRead();
	
	BOOL Is_open_0 ();
	BOOL Is_open_1 ();
	BOOL Is_open_2 ();
	BOOL Is_open_3 ();
	BOOL Is_open_4 ();
	BOOL Is_open_5 ();
	BOOL Is_open_6 ();
	BOOL Is_open_7 ();
	
	BOOL Is_open (ValveNum _num);
	
	ValveData Read ();
	
	BOOL operator [] (ValveNum _num);
};

/************************************************************************/
/*	ValveOperate														*/
/************************************************************************/
class ValveOperate	: public virtual ValveWrite
					//, public virtual ValveToggle
					, public virtual ValveRead
{
private:	
	
	Time _mem_timer[8];
	Byte _mem_is_move_allow :8;
//	BOOL _mem_is_move_allow[8];
	
protected:
	
	void Set_timer (ValveNum _num);
	BOOL Comp_timer (ValveNum _num);
	
	void Can_allow (ValveNum _num, BOOL _yes);	
	BOOL Is_allow (ValveNum _num);
	void Reversal_allow(ValveNum _num);
	
public:
	
	ValveOperate ();
	
	void Toggle (ValveNum _num);
	
	void Check_safety (ValveNum _num_a, ValveNum _num_b);
	
	void OpenClose (ValveNum _num, BOOL _is_move);	
	void OpenClose (ValveNum _num_a, ValveNum _num_b, BOOL _is_move);
	void OpenClose (ValveNum _num_a, BOOL _is_move_a, ValveNum _num_b, BOOL _is_move_b);
};

/************************************************************************/
/*	ValveLCD															*/
/************************************************************************/
class ValveLCD : public virtual ValveRead
{
public:
	
	ValveLCD();
	
	void LCD(LcdAdrs _adrs, ValveNum _num);
	void LCD(LcdAdrs _adrs, Decimal _decimal);		
};

}

/************************************************************************/

#include "ValveBase_inline.h"
#include "ValveWrite_inline.h"
#include "ValveRead_inline.h"
//#include "ValveToggle_inline.h"

#endif /*__cplusplus*/

