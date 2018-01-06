
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/Uart/Uart.h>
#include <AVR/Uart/Uart_func.h>
#include <MainCircit/Signal.h>
#include <MainCircit/Motor/Motor.h>

/************************************************************************/

//----------------------------------------------------------------------//

Motor::Motor()
{}

//----------------------------------------------------------------------//

Motor::Motor(const MotorNum _motor_number, const YesNo _is_signal_reverse)

	: MotorOperate(_motor_number, _is_signal_reverse)
{
	Set_steps(STEPS_USE);
}

//----------------------------------------------------------------------//

void Motor::Write(Uart::ModeTransmit *_uart)
{
	_uart->Enable_9bit();
	
	_uart->Transmit_9bit(Get_data_0());
	_uart->Transmit_9bit(Get_data_1());
	
	_delay_us(100);
}

//----------------------------------------------------------------------//

void Motor::Write_clear(Uart::ModeTransmit *_uart)
{
	_uart->Enable_9bit();
	
	_uart->Transmit_9bit(Get_data_0() & 0x1e0);
	_uart->Transmit_9bit(Get_data_1() & 0x1e0);
	
	_delay_us(100);
}

//----------------------------------------------------------------------//


void Motor::Write(Uart::ModeTransmit &_uart)
{
	_uart.Enable_9bit();
	
	_uart.Transmit_9bit(Get_data_0());
	_uart.Transmit_9bit(Get_data_1());
	
	_delay_us(100);
}

//----------------------------------------------------------------------//

void Motor::Write_clear(Uart::ModeTransmit &_uart)
{
	_uart.Enable_9bit();
	
	_uart.Transmit_9bit(Get_data_0() & 0x1e0);
	_uart.Transmit_9bit(Get_data_1() & 0x1e0);
	
	_delay_us(100);
}

//----------------------------------------------------------------------//

/************************************************************************/
