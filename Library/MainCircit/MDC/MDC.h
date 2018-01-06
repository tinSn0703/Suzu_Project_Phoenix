
#pragma once

/************************************************************************/

class MDC
{
private:
	
	UartTransmit _mem_uart;
	
	uByte _mem_num_of_slot :2;
	
	Pwm _mem_pwm : 5;
	
protected:
	
	Motor _mem_md[4];
	
public:
	
	MDC(MotorNumber _min_number, Byte _num_of_slot = 4);
	MDC(MotorNumber _min_number, UartNum _uart_adrs, Byte _num_of_slot = 4);
	
	uByte Get_num_of_slot();
	
	UartTransmit * Get_uart();
	
	void Set(Pwm _pwm);
	void Set(Signal _sig);
	
	void Set_non_memory(Pwm _pwm);
	
	Pwm Get_pwm();
	
	void Want_to_use_steps(YesNo _yes_no);
	
	void Display_pwm(LcdAdrs _adrs);
	void Display_signal(LcdAdrs _adrs);
	
	void Transmit();
	void Transmit(UartTransmit &_uart);
	
	void Transmit_clear();
	void Transmit_clear(UartTransmit &_uart);
	
	Motor & Slot(MotorNumber _slot);
	
	Motor & operator [] (MotorNumber _slot);
	
	void operator ++ (int );
	void operator -- (int );
	
	Pwm		operator = (Pwm _pwm);
	Signal	operator = (Signal _sig);
};

/************************************************************************/

#include "MDC_inline.h"