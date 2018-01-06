

#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline uByte MDC :: Get_num_of_slot()
{
	return _mem_num_of_slot;
}

//----------------------------------------------------------------------//

inline UartTransmit * MDC :: Get_uart()
{
	return &_mem_uart;
}

//----------------------------------------------------------------------//

inline Pwm MDC :: Get_pwm()
{
	return _mem_pwm;
};

//----------------------------------------------------------------------//

inline Motor & MDC :: Slot(const MotorNumber _slot_num)
{
	return _mem_md[To_within(_slot_num, _mem_num_of_slot, 0)];
}

//----------------------------------------------------------------------//

inline Motor & MDC :: operator [] (const MotorNumber _slot_num)
{
	return _mem_md[To_within(_slot_num, _mem_num_of_slot, 0)];
}

//----------------------------------------------------------------------//

inline Signal MDC :: operator = (const Signal _sig)
{
	MDC::Set(_sig);
	
	return _sig;
}

//----------------------------------------------------------------------//

inline Pwm MDC :: operator = (const Pwm _pwm)
{
	MDC::Set(_pwm);
	
	return _pwm;
}

//----------------------------------------------------------------------//

/************************************************************************/
