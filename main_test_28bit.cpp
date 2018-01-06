/*
 * main_test_28bit.cpp
 *
 * Created: 2017/05/02 17:11:51
 *  Author: FUJITSU
 */ 

#include <MainCircit/MainCircit.h>

union Controller_28bit
{
	struct BitController_28bit
	{
		YesNo _stick_r_right	:1;
		YesNo _stick_rx_high	:1;
		YesNo _stick_r_left		:1;
		
		Btn _cross_under	:1;
		Btn _cross_over		:1;
		
		Byte __void_0__	:3;
		
		YesNo _stick_r_under	:1;
		YesNo _stick_ry_high	:1;
		YesNo _stick_r_over		:1;
		
		Btn _cross_right	:1;
		Btn _cross_left		:1;
		
		Byte __void_1__	:3;
		
		YesNo _stick_lx_right	:1;
		YesNo _stick_lx_high	:1;
		YesNo _stick_lx_left	:1;
		
		Btn _L1	:1;
		Btn _R1	:1;
		
		Byte __void_2__	:3;
		
		YesNo _stick_ly_right	:1;
		YesNo _stick_ly_high	:1;
		YesNo _stick_ly_left	:1;
		
		Btn _L2	:1;
		Btn _R2	:1;
		
		Byte __void_3__	:3;
		
		Btn _SELECT	:1;
		Btn _L3		:1;
		Btn _R3		:1;
		Btn _START	:1;
		
		Byte __void_4__	:4;
		
		Btn _Tri	:1;
		Btn _Cir	:1;
		Btn _Cro	:1;
		Btn _Squ	:1;
		
		Byte __void_5__	:4;
		
	}
	_bit;
	
	ControllerData _arr[6];
};

int main()
{
	LCD_Init();
	
	Controller_28bit _controller;
	
	UartReceive _uart(UART_NUM_0);
	
	while (1)
	{
		uByte _flag = 0;
		
		for (uByte i = 0; i < 10; i++)
		{
			const UartData8bit _temp = _uart.Receive_8bit();
			
			const uByte _num = ((_temp >> 5) & 7);
			
			_controller._arr[_num] = _temp;
			
			_flag |= (1 << _num);
			
			if (_flag == 0b111111)	break;			
		}
		
		for (uByte i = 0; i < 6; i++)
		{
			LCD_Write_num(0x40 + i * 2, _controller._arr[i], 2, DECIMAL_10);
		}
	}
}
