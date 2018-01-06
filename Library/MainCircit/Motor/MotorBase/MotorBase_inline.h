

#pragma once

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

inline void MotorBase :: Reset(const MotorNumber _num)
{
	_mem_data._0._sub._num_md = _mem_data._1._sub._num_md = To_within(_num, 7, 0);
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	MotorRead															*/
/************************************************************************/

//----------------------------------------------------------------------//

inline MotorNumber MotorGet :: Get_number()
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

inline MotorData MotorGet :: Get_data_0()
{
	return _mem_data._0._all;
}

//----------------------------------------------------------------------//

inline MotorData MotorGet :: Get_data_1()
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

inline void MotorOperate :: Set_direct(const Pwm _pwm)
{
	_mem_data._1._sub._pwm = _pwm;
}

//----------------------------------------------------------------------//

inline void MotorOperate :: Set(const Pwm _pwm)
{
	MotorOperate :: Set_direct(To_within(_pwm + _mem_pwm_adjustment, 31, 0));
}

//----------------------------------------------------------------------//

inline void MotorOperate :: Set(const Signal _sig)
{
	_mem_data._0._sub._sig = _sig;
}

//----------------------------------------------------------------------//

inline void MotorOperate :: Set(const Signal _sig, const Pwm _pwm)
{
	MotorOperate :: Set(_sig);
	MotorOperate :: Set(_pwm);
}

//----------------------------------------------------------------------//

inline void MotorOperate :: Adjust_for(const Pwm _pwm_revi)
{
	_mem_pwm_adjustment = To_within(_pwm_revi, 31, -31);
}

//----------------------------------------------------------------------//

inline void MotorOperate :: Want_to_use_steps(const YesNo _is_on)
{
	_mem_data._0._sub._is_steps_on = _is_on;
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
