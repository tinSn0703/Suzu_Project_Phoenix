

#pragma once

//----------------------------------------------------------------------//

inline UartTransmit * Motor :: Get_uart()
{
	return _mem_uart;
}

//----------------------------------------------------------------------//

inline Signal Motor :: operator = (const Signal _sig)
{
	Motor :: Set(_sig);

	return _sig;
}

//----------------------------------------------------------------------//

inline Pwm Motor :: operator = (const Pwm _pwm)
{
	Motor :: Set(_pwm);
	
	return _pwm;
}

//----------------------------------------------------------------------//
