
#pragma once

/************************************************************************/

#include "MotorBase/MotorBase.h"

/************************************************************************/

class Motor	:	public ClassMotor::MotorOperate
			,	public ClassMotor::MotorLCD
{
protected:
	
	UartTransmit *_mem_uart;
	
	MotorData _mem_data_0 :9;
	MotorData _mem_data_1 :9;
	
public:
	
	Motor();
	Motor(MotorNumber _num_md);
	Motor(MotorNumber _num_md, UartTransmit *_uart);
	
	void Set_uart(UartTransmit *_uart);
	
	UartTransmit * Get_uart();
	
	void Transmit();
	void Transmit(UartTransmit &_uart);
	
	void Transmit_clear();
	void Transmit_clear(UartTransmit &_uart);
	
	Signal	operator = (Signal _sig);
	Pwm		operator = (Pwm _pwm);
};

/************************************************************************/

#include "Motor_inline.h"
#include "Motor_operator.h"

/************************************************************************/
