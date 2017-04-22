

#pragma once

namespace ClassMotor
{

/************************************************************************/
/*	MotorBase															*/
/************************************************************************/

//----------------------------------------------------------------------//

inline void MotorBase :: Clear()
{
	_mem_data._0._sub._sig = SIGNAL_FREE;
	_mem_data._1._sub._pwm = 0;
	
	_mem_data._0._sub._is_steps_on = FALSE;
}

//----------------------------------------------------------------------//

inline void MotorBase :: Reset(const MdNum _md_num)
{
	_mem_data._0._sub._num_md = _md_num;
	_mem_data._1._sub._num_md = _md_num;
}

//----------------------------------------------------------------------//

inline void MotorBase :: Reset(const MdcNum _mdc_num)
{
	_mem_data._0._sub._num_mdc = _mdc_num;
	_mem_data._1._sub._num_mdc = _mdc_num;
}

//----------------------------------------------------------------------//

inline void MotorBase :: Reset
(
	const MdcNum	_arg_num_mdc,
	const MdNum		_arg_num_md
)
{
	_mem_data._0._sub._num_mdc = _arg_num_mdc;
	_mem_data._1._sub._num_mdc = _arg_num_mdc;
	
	_mem_data._0._sub._num_md = _arg_num_md;
	_mem_data._1._sub._num_md = _arg_num_md;
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	MotorRead															*/
/************************************************************************/

//----------------------------------------------------------------------//

inline MdcNum MotorGet :: Get_mdc_num()
{
	return _mem_data._0._sub._num_mdc;
}

//----------------------------------------------------------------------//

inline MdNum MotorGet :: Get_md_num()
{
	return _mem_data._0._sub._num_md;
}

//----------------------------------------------------------------------//

inline Signal MotorGet :: Get_sig()
{
	return _mem_data._0._sub._sig;
}

//----------------------------------------------------------------------//

inline Pwm MotorGet :: Get_pwm()
{
	return _mem_data._1._sub._pwm;
}

//----------------------------------------------------------------------//

inline DataMotor MotorGet :: Get_data_0()
{
	return _mem_data._0._all;
}

//----------------------------------------------------------------------//

inline DataMotor MotorGet :: Get_data_1()
{
	return _mem_data._1._all;
}

//----------------------------------------------------------------------//

inline BOOL MotorGet :: Is_steps_used()
{
	return _mem_data._0._sub._is_steps_on;
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	MotorOperate														*/
/************************************************************************/

//----------------------------------------------------------------------//

inline void MotorOperate :: Set
(
	const Signal	_arg_sig,
	const Pwm		_arg_pwm,
	const BOOL		_arg_is_steps_on
)
{
	Set_direct(_arg_sig);
	Set(_arg_pwm);
	Want_to_use_steps(_arg_is_steps_on);
}

//----------------------------------------------------------------------//

inline void MotorOperate :: Adjust_for (const Pwm _arg_pwm_revi)
{
	_mem_pwm_adjustment = To_within(_arg_pwm_revi, 31, -31);
}

//----------------------------------------------------------------------//

inline void MotorOperate :: Set_direct (const Signal _arg_sig)
{
	_mem_data._0._sub._sig = _arg_sig;
}

//----------------------------------------------------------------------//

inline void MotorOperate :: Set_direct (const Pwm _arg_pwm)
{
	_mem_data._1._sub._pwm = _arg_pwm;
}

//----------------------------------------------------------------------//

inline void MotorOperate :: Set_direct
(
	const Signal	_arg_sig,
	const Pwm		_arg_pwm,
	const BOOL		_arg_is_steps_on
)
{
	Set_direct(_arg_sig);
	Set_direct(_arg_pwm);
	Want_to_use_steps(_arg_is_steps_on);
}

//----------------------------------------------------------------------//

inline void MotorOperate :: Want_to_use_steps (const YesNo _arg_is_on)
{
	_mem_data._0._sub._is_steps_on = _arg_is_on;
}

//----------------------------------------------------------------------//

inline void MotorOperate :: operator ++ (int i)
{
	if (_mem_data._1._sub._pwm < 31)	_mem_data._1._sub._pwm ++;
}

//----------------------------------------------------------------------//

inline void MotorOperate :: operator -- (int i)
{
	if (_mem_data._1._sub._pwm > 0)		_mem_data._1._sub._pwm --;
}

//----------------------------------------------------------------------//

};
