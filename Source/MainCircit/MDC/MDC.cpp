
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Signal.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>

/************************************************************************/

//----------------------------------------------------------------------//

MDC::MDC(const UartNum _uart_num, const Byte _num_of_slot)

	 : _uart(_uart_num)
{
	MDC::_num_of_slot = To_within(_num_of_slot, 4, 2) - 1;
	
	_motor[0].Reset(0);
	_motor[1].Reset(1);
	_motor[2].Reset(2);
	_motor[3].Reset(3);
}

//----------------------------------------------------------------------//

void MDC::Set(const Signal _sig)
{
	for (uByte i = 0; i <= _num_of_slot; i++)
	{
		_motor[i].Set(_sig);
	}
}

//----------------------------------------------------------------------//

void MDC::Set(const Power _pwm)
{
	for (uByte i = 0; i <= _num_of_slot; i++)
	{
		_motor[i].Set(_pwm);
	}
}

//----------------------------------------------------------------------//

void MDC::Set_steps(const StepsMode _steps_mode)
{
	for (uByte i = 0; i <= _num_of_slot; i++)
	{
		_motor[i].Set_steps(_steps_mode);
	}
}

//----------------------------------------------------------------------//

Pwm MDC::Get_max_pwm()
{
	Pwm _max_pwm = 0;
	
	for (uByte i = 1; i <= _num_of_slot; i++)
	{
		if (_motor[i] != SIGNAL_BREAK)
		{
			if (_max_pwm < _motor[i].Get_pwm())
			{
				_max_pwm = _motor[i].Get_pwm();
			}
		}
	}

	return _max_pwm;
}

//----------------------------------------------------------------------//

void MDC::Write()
{
	for (uByte i = 0; i <= _num_of_slot; i++)
	{
		_motor[i].Write(_uart);
	}
}

//----------------------------------------------------------------------//

void MDC::Write_clear()
{
	for (uByte i = 0; i <= _num_of_slot; i++)
	{
		_motor[i].Write_clear(_uart);
	}
}

//----------------------------------------------------------------------//

void MDC::Display_signal(const LcdAdrs _adrs)
{
	for (uByte i = 0; i <= _num_of_slot; i++)
	{
		_motor[i].Display_signal(_adrs + 2 * i);
	}
}

//----------------------------------------------------------------------//

void MDC::Display_power(const LcdAdrs _adrs)
{
	for (uByte i = 0; i <= _num_of_slot; i++)
	{
		_motor[i].Display_power(_adrs + 3 * i);
	}
}

//----------------------------------------------------------------------//

void MDC::Display_pwm(const LcdAdrs _adrs)
{
	for (uByte i = 0; i <= _num_of_slot; i++)
	{
		_motor[i].Display_pwm(_adrs + 3 * i);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
