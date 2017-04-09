/*
 * ValveBase_inline.h
 *
 * Created: 2017/03/06 10:27:10
 *  Author: Suzu
 */ 


#pragma once

namespace ClassValve
{
/************************************************************************/
/*	ValveOperate														*/
/************************************************************************/

//----------------------------------------------------------------------//

inline void ValveOperate :: Set_timer (const ValveNum _arg_num)
{
	Timer_Set(&_mem_timer[_arg_num], _WAIT_MS_TIME_);
}

//----------------------------------------------------------------------//

inline BOOL ValveOperate :: Comp_timer (const ValveNum _arg_num)
{
	return Timer_Comp(&_mem_timer[_arg_num]);
}

//----------------------------------------------------------------------//

inline void ValveOperate :: Can_allow 
(
	const ValveNum	_arg_num, 
	const BOOL		_arg_is_allow
)
{
	_mem_is_move_allow &= ~(1 << _arg_num);
	_mem_is_move_allow |=  (_arg_is_allow << _arg_num);
}

//----------------------------------------------------------------------//

inline void ValveOperate :: Reversal_allow (const ValveNum _arg_num)
{
	_mem_is_move_allow ^= (1 << _arg_num);
}

//----------------------------------------------------------------------//

inline BOOL ValveOperate :: Is_allow (const ValveNum _arg_num)
{
	return Is_true_the(_mem_is_move_allow, _arg_num);
}

//----------------------------------------------------------------------//

inline void ValveOperate :: Toggle (const ValveNum _arg_num)
{
	_mem_data._all ^= (1 << _arg_num);
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	ValveLCD															*/
/************************************************************************/

//----------------------------------------------------------------------//

inline void ValveLCD :: LCD (const LcdAdrs _arg_adrs, const ValveNum _arg_num)
{	
	LCD_Display_num(_arg_adrs, Is_open(_arg_num), 1, DECIMAL_02);
}

//----------------------------------------------------------------------//

};
