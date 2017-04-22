

#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline void MDC :: Set_uart (UartTransmit *_uart)
{
	for (Byte i = 0; i <= _mem_num_of_slot; i++)
	{
		_mem_md[i].Set_uart(_uart);
	}
}

//----------------------------------------------------------------------//

inline void MDC :: Set_direct (const Signal _sig)
{
	for (Byte i = 0; i <= _mem_num_of_slot; i++)
	{
		_mem_md[i].Set_direct(_sig);
	}
}

//----------------------------------------------------------------------//

inline void MDC :: Set_direct (const Pwm _pwm)
{
	for (Byte i = 0; i <= _mem_num_of_slot; i++)
	{
		_mem_md[i].Set_direct(_pwm);
	}
}

//----------------------------------------------------------------------//

inline void MDC :: Set_direct 
(
	const Signal	_sig, 
	const Pwm		_pwm, 
	const BOOL		_is_steps_on
)
{
	for (Byte i = 0; i <= _mem_num_of_slot; i++)
	{
		_mem_md[i].Set_direct(_sig, _pwm, _is_steps_on);
	}
}

//----------------------------------------------------------------------//

inline void MDC :: Can_you_want_use_steps (const BOOL _is_steps_on)
{
	for (Byte i = 0; i <= _mem_num_of_slot; i++)
	{
		_mem_md[i].Want_to_use_steps(_is_steps_on);
	}
}

//----------------------------------------------------------------------//


inline void MDC :: Set (const Pwm _pwm)
{
	for (Byte i = 0; i <= _mem_num_of_slot; i++)
	{
		_mem_md[i].Set(_pwm);
	}
}

//----------------------------------------------------------------------//

inline void MDC :: Set
(
	const Signal	_sig, 
	const Pwm		_pwm, 
	const BOOL		_is_steps_on
)
{
	for (Byte i = 0; i <= _mem_num_of_slot; i++)
	{
		_mem_md[i].Set(_sig, _pwm, _is_steps_on);
	}
}

//----------------------------------------------------------------------//

inline void MDC :: Transmit()
{
	for (Byte i = 0; i <= _mem_num_of_slot; i++)
	{
		_mem_md[i].Transmit(_mem_uart);
	}
}

//----------------------------------------------------------------------//

inline void MDC :: Transmit (UartTransmit &_uart)
{
	for (Byte i = 0; i <= _mem_num_of_slot; i++)
	{
		_mem_md[i].Transmit(_uart);
	}
}

//----------------------------------------------------------------------//

inline void MDC :: LCD_signal (const LcdAdrs _adrs)
{
	for (Byte i = 0; i <= _mem_num_of_slot; i++)
	{
		_mem_md[i].LCD_signal(_adrs + 3 * i);
	}
}

//----------------------------------------------------------------------//

inline void MDC :: LCD_pwm (const LcdAdrs _adrs)
{
	for (Byte i = 0; i <= _mem_num_of_slot; i++)
	{
		_mem_md[i].LCD_pwm(_adrs + 3 * i);
	}
}

//----------------------------------------------------------------------//

inline Motor & MDC :: operator [] (const MdNum _num)
{
	return _mem_md[To_within(_num, _mem_num_of_slot, NUM_MD_0)];
}

//----------------------------------------------------------------------//

inline Signal MDC :: operator = (const Signal _sig)
{
	MDC :: Set(_sig);
	
	return _sig;
}

//----------------------------------------------------------------------//

inline Pwm MDC :: operator = (const Pwm _pwm)
{
	MDC :: Set(_pwm);
	
	return _pwm;
}

//----------------------------------------------------------------------//

/************************************************************************/
