
#pragma once

/************************************************************************/

class MDC
{
private:
	
	UartTransmit _mem_uart;
	
	Byte _mem_num_of_slot :3;
	
protected:
	
	Motor _mem_md[4];
	
public:
	
	MDC (MdcNum _num_mdc, int _num_of_slot = 4);
	MDC (MdcNum _num_mdc, UartNum _uart_adrs, int _num_of_slot = 4);
	
	void Set_uart (UartTransmit *_uart);
	
	void Set_direct (Signal _sig);
	void Set_direct (Pwm _pwm);
	void Set_direct (Signal _sig, Pwm _pwm, BOOL _is_steps_on);
	
	void Set (Signal _sig);
	void Set (Pwm _pwm);
	void Set (Signal _sig, Pwm _pwm, BOOL _is_steps_on);
	
	void Can_you_want_use_steps (YesNo _yes_no);
	
	void LCD_signal (LcdAdrs _adrs);
	void LCD_pwm (LcdAdrs _adrs);
	
	void Transmit ();
	void Transmit (UartTransmit &_uart);
	
	Motor & operator [] (MdNum _num);
	
	Signal	operator = (Signal _sig);
	Pwm		operator = (Pwm _pwm);
};

/************************************************************************/

#include "MDC_inline.h"