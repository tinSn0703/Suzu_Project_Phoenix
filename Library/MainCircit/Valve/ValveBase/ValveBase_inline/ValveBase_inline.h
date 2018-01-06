/*
 * ValveBase_inline.h
 *
 * Created: 2017/03/06 10:27:10
 *  Author: Suzu
 */ 


#pragma once

/************************************************************************/

namespace ClassValve
{

/************************************************************************/
/*	ValveOperate														*/
/************************************************************************/

//----------------------------------------------------------------------//

inline void ValveOperate :: Set_timer (const ValveNum _num)
{
	_mem_timer[_num] = GeneralTimer::Read() + GeneralTimer::Change_count_value(WAIT_MS_TIME);
}

//----------------------------------------------------------------------//

inline BOOL ValveOperate :: Compare_timer (const ValveNum _num)
{
	return GeneralTimer::Is_current_bigger_than(_mem_timer[_num]);
}

//----------------------------------------------------------------------//

inline void ValveOperate :: Want_to_enable 
(
	const ValveNum	_num, 
	const YesNo		_yes_no
)
{
	_mem_is_move_enabled &= ~(1 << _num);
	_mem_is_move_enabled |=  (_yes_no << _num);
}

//----------------------------------------------------------------------//

inline void ValveOperate :: Reversal_enabled (const ValveNum _num)
{
	_mem_is_move_enabled ^= (1 << _num);
}

//----------------------------------------------------------------------//

inline BOOL ValveOperate :: Is_enabled (const ValveNum _num)
{
	return Is_true_the(_mem_is_move_enabled, _num);
}

//----------------------------------------------------------------------//

inline void ValveOperate :: Toggle (const ValveNum _num)
{
	_mem_data._all ^= (1 << _num);
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	ValveLCD															*/
/************************************************************************/

//----------------------------------------------------------------------//

inline void ValveLCD :: Display (const LcdAdrs _adrs, const ValveNum _num)
{	
	LCD::Write(_adrs, Is_open_for(_num), 1, DECIMAL_02);
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
