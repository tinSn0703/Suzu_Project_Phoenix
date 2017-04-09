

#pragma once

//----------------------------------------------------------------------//

inline BOOL operator == (Motor &_arg_motor , const Signal _arg_sig)
{
	return (_arg_motor.Get_sig() == _arg_sig ? TRUE : FALSE);
}

//----------------------------------------------------------------------//

inline BOOL operator != (Motor &_arg_motor , const Signal _arg_sig)
{
	return (_arg_motor.Get_sig() != _arg_sig ? TRUE : FALSE);
}

//----------------------------------------------------------------------//

inline BOOL operator == (Motor &_arg_motor , const Pwm _arg_pwm)
{
	return (_arg_motor.Get_pwm() == _arg_pwm ? TRUE : FALSE);
}

//----------------------------------------------------------------------//

inline BOOL operator != (Motor &_arg_motor , const Pwm _arg_pwm)
{
	return (_arg_motor.Get_pwm() != _arg_pwm ? TRUE : FALSE);
}

//----------------------------------------------------------------------//

inline BOOL operator > (Motor &_arg_motor , const Pwm _arg_pwm)
{
	return (_arg_motor.Get_pwm() > _arg_pwm ? TRUE : FALSE);
}

//----------------------------------------------------------------------//

inline BOOL operator < (Motor &_arg_motor , const Pwm _arg_pwm)
{
	return (_arg_motor.Get_pwm() < _arg_pwm ? TRUE : FALSE);
}

//----------------------------------------------------------------------//

inline BOOL operator >= (Motor &_arg_motor , const Pwm _arg_pwm)
{
	return (_arg_motor.Get_pwm() >= _arg_pwm ? TRUE : FALSE);
}

//----------------------------------------------------------------------//

inline BOOL operator <= (Motor &_arg_motor , const Pwm _arg_pwm)
{
	return (_arg_motor.Get_pwm() <= _arg_pwm ? TRUE : FALSE);
}

//----------------------------------------------------------------------//
