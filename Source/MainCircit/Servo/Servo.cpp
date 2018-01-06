
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Servo/Servo.h>

/************************************************************************/

#define ADJUST_NEW_ANGLE 6
#define ADJUST_OLD_ANGLE 1.5

/************************************************************************/

//----------------------------------------------------------------------//

Servo :: Servo()
{
	_mem_servo._data = 0x00;
	
	_mem_is_uart_set = NO;
}

//----------------------------------------------------------------------//

Servo :: Servo(const ServoNewNumber _number, Uart::ModeTransmit *_uart)
{
	_mem_uart = _uart;
	
	_mem_is_uart_set = YES;
	
	_mem_servo._new._number = _number;
	_mem_servo._new._angle = 0;
}

//----------------------------------------------------------------------//

Servo :: Servo(const ServoOldNumber _number, Uart::ModeTransmit *_uart)
{
	_mem_uart = _uart;
	
	_mem_is_uart_set = YES;
	
	_mem_servo._old._number = _number;
	_mem_servo._old._angle = 0;
}

//----------------------------------------------------------------------//

void Servo :: Reset(const ServoNewNumber _number)
{
	_mem_servo._new._angle = _number;
}

//----------------------------------------------------------------------//

void Servo :: Reset(const ServoOldNumber _number)
{
	_mem_servo._old._angle = _number;
}

//----------------------------------------------------------------------//

void Servo :: Reset(Uart::ModeTransmit *_uart)
{
	_mem_uart = _uart;
	
	_mem_is_uart_set = YES;
}

//----------------------------------------------------------------------//

void Servo :: Set_angle_deg_new(const ServoAngle _angle)
{
	if (_angle > 180)
	{
		_mem_servo._new._angle = 30;
	}
	else if (_angle < 0)
	{
		_mem_servo._new._angle = 0;
	}
	else
	{
		_mem_servo._new._angle = (_angle / ADJUST_NEW_ANGLE);
	}
}

//----------------------------------------------------------------------//

void Servo :: Set_angle_deg_old(const ServoAngle _angle)
{
	if (_angle > 180)
	{
		_mem_servo._old._angle = 120;
	}
	else if (_angle < 0)
	{
		_mem_servo._old._angle = 0;
	}
	else
	{
		_mem_servo._old._angle = (_angle / ADJUST_OLD_ANGLE);
	}
}

//----------------------------------------------------------------------//

void Servo ::Write(Uart::ModeTransmit &_uart)
{
	_uart.Transmit_8bit(_mem_servo._data);
}

//----------------------------------------------------------------------//


void Servo :: Write()
{
	if (_mem_is_uart_set)
	{
		_mem_uart->Transmit_8bit(_mem_servo._data);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
