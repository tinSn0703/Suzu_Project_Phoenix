
#pragma once

/************************************************************************/

#include "UartBase/UartBase.h"

/************************************************************************/

class UartReceive : public ClassUart::UartSet
{
private:
	
	YesNo _mem_did_error_occurr :1;	//��M�G���[�̋L�^
	
public:
	
	UartReceive();
	UartReceive(UartNum _uart_num);
	
	void Enable_receive();
	void Disable_receive();
	
	/**
	 *	��M���ɃG���[���N�������ǂ������m�F���邽�߂̊֐�
	 *	�f�[�^�͎�M�ォ��A���Ɏ�M����܂ŕێ������
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
