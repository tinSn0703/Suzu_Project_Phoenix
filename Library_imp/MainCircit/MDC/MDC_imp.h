
#pragma once

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/AVR.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>

/************************************************************************/

//----------------------------------------------------------------------//

MDC :: MDC (NumMDC _num)
{
	for (usint _num_md = 0; _num_md < 4; _num_md++)
	{
		Motor _temp(_num, (NumMD)_num_md);
		
		_mem_md[_num_md] = _temp;
	}
}

//----------------------------------------------------------------------//

MDC :: MDC (NumMDC _num, UartNum _adrs)

	 : _mem_uart(_adrs)
{
	for (usint _num_md = 0; _num_md < 4; _num_md++)
	{
		Motor _temp(_num, (NumMD)_num_md);
		
		_mem_md[_num_md] = _temp;
		_mem_md[_num_md].Set_uart(&_mem_uart);
	}
}

//----------------------------------------------------------------------//

void MDC :: Set (const Signal _arg_sig)
{
	MDC :: Set_direct(_arg_sig);
	
	if (Is_Signal_rotation(_arg_sig))
	{
		MDC :: Set_direct(0);
	}
}

//----------------------------------------------------------------------//

void MDC :: Set (const Pwm _arg_pwm)
{
	_mem_md[0] = _mem_md[1] = _mem_md[2] = _mem_md[3] = _arg_pwm;
}

//----------------------------------------------------------------------//

void MDC :: Set
(
	const Signal	_arg_sig, 
	const Pwm		_arg_pwm, 
	const BOOL		_arg_is_steps_on
)
{
	_mem_md[0].Set(_arg_sig, _arg_pwm, _arg_is_steps_on);
	_mem_md[1].Set(_arg_sig, _arg_pwm, _arg_is_steps_on);
	_mem_md[2].Set(_arg_sig, _arg_pwm, _arg_is_steps_on);
	_mem_md[3].Set(_arg_sig, _arg_pwm, _arg_is_steps_on);
}

//----------------------------------------------------------------------//

void MDC :: Transmit()
{
	_mem_md[0].Transmit(_mem_uart);
	_mem_md[1].Transmit(_mem_uart);
	_mem_md[2].Transmit(_mem_uart);
	_mem_md[3].Transmit(_mem_uart);
}

//----------------------------------------------------------------------//

void MDC :: Transmit (UartTransmit &_arg_uart)
{
	_mem_md[0].Transmit(_arg_uart);
	_mem_md[1].Transmit(_arg_uart);
	_mem_md[2].Transmit(_arg_uart);
	_mem_md[3].Transmit(_arg_uart);
}

//----------------------------------------------------------------------//

/************************************************************************/

#endif	//__cplusplus

/************************************************************************/

