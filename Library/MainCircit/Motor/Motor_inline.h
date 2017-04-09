

#pragma once

//----------------------------------------------------------------------//

inline void Motor :: Set_uart (UartTransmit *_arg_uart)
{
	_mem_uart = _arg_uart;
}

//----------------------------------------------------------------------//

inline Signal Motor :: operator = (const Signal _arg_sig)
{
	Set(_arg_sig);

	return _arg_sig;
}

//----------------------------------------------------------------------//

inline Pwm Motor :: operator = (const Pwm _arg_pwm)
{
	Set(_arg_pwm);
	
	return _arg_pwm;
}

//----------------------------------------------------------------------//
