/*
 * Suzu_Project_Phoenix.cpp
 *
 * Created: 2017/02/16 15:48:40
 * Author : Suzu
 *
 * �V�������v���O�����̃e�X�g�����s�����߂̃v���W�F�N�g�B
 * �e�X�g�̍ۂ͋߂��ɂ���t�H���_Library�܂Ńp�X���΂��Ă�������
 */ 

#include <MainCircit/MainCircit.h>

int main ()
{
	LCD_Init();
	LCD_Display_str(0x00, "Suzu_Phonix");
	
	Dualshock2 _controller(UART_ADRS_0);
	
	OmuniOpposite _wheel(NUM_MDC_0, UART_ADRS_1);
	
	while (1)
	{
		_controller.Receive();
		
		_wheel.Drive(_controller.Get_stick_Lx(), _controller.Get_stick_Ly());
		
		_wheel.Transmit();
	}
}
