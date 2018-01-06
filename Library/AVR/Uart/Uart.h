
#pragma once

/************************************************************************/

#include "UartBase/UartBase.h"

/************************************************************************/

class UartReceive : public ClassUart::UartSet
{
private:
	
	YesNo _mem_did_error_occurr :1;	//受信エラーの記録
	
public:
	
	UartReceive();
	UartReceive(UartNum _uart_num);
	
	void Enable_receive();
	void Disable_receive();
	
	/**
	 *	受信時にエラーが起きたかどうかを確認するための関数
	 *	データは受信後から、次に受信するまで保持される
	**/
	YesNo Did_error_occurr();
	
	UartData8bit Receive_8bit();
	UartData9bit Receive_9bit();
};

/************************************************************************/

class UartTransmit : public ClassUart::UartSet
{
public:
	
	UartTransmit();
	UartTransmit(UartNum _uart_num);
	
	void Enable_transmit();
	void Disable_transmit();
	
	void Transmit_8bit(UartData8bit _uart_data);
	void Transmit_9bit(UartData9bit _uart_data);
};

/************************************************************************/

#include "Uart_inline.h"

/************************************************************************/
