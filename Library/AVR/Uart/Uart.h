
#pragma once

#if defined(__cplusplus)

/************************************************************************/

#include "UartBase/UartBase.h"

/************************************************************************/

class UartReceive : public virtual ClassUart :: UartSet
{
private:
	
	UartData9bit _mem_data_b :9;
	
public:
	
	UartReceive ();
	UartReceive (UartNum _uart_num);
	
	void Enable_receive();
	void Disable_receive();
	
	UartData9bit Receive_9bit ();
	UartData8bit Receive_8bit ();
};

/************************************************************************/

class UartTransmit : public virtual ClassUart :: UartSet
{
public:
	
	UartTransmit ();
	UartTransmit (UartNum _uart_num);
	
	void Enable_transmit();
	void Disable_transmit();
	
	void Transmit_8bit (const UartData8bit _uart_data);
	void Transmit_9bit (const UartData9bit _uart_data);
};

/************************************************************************/

class Uart	: public UartReceive
			, public UartTransmit
{
public:
	
	Uart();
	Uart(UartNum _uart_num);
};

/************************************************************************/

#include "Uart_inline.h"

/************************************************************************/

#else

#include "UartBase/Uart_func.h"

#endif /*__cplusplus*/
