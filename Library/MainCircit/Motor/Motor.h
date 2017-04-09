

#pragma once

#if defined(__cplusplus)

#include "MotorBase/MotorBase.h"

/************************************************************************/

class Motor	:	public ClassMotor :: MotorOperate
			,	public ClassMotor :: MotorLCD
{
private:
	
	DataMotor _mem_memory_data_0 :9;
	DataMotor _mem_memory_data_1 :9;
	
protected:
	
	UartTransmit *_mem_uart;
	
public:
	
	Motor ();
	Motor (MdcNum _num_mdc, MdNum _num_md);
	
	void Set_uart (UartTransmit *_uart);
	
	void Transmit ();
	void Transmit (UartTransmit &_uart);
	
	void Transmit_clear ();
	void Transmit_clear (UartTransmit &_uart);
	
	Signal	operator = (Signal _sig);
	Pwm		operator = (Pwm _pwm);
};

/************************************************************************/

#include "Motor_inline.h"
#include "Motor_operator.h"

/************************************************************************/

#else

#include "MotorBase/MotorData/MotorData.h"

#endif /*__cplusplus*/