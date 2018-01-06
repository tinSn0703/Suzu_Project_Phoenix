
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Controller/Controller28bit.h>

/************************************************************************/

namespace Controller
{
namespace Bit28
{

/************************************************************************/

//----------------------------------------------------------------------//

ControllerBase :: ControllerBase(const UartNum _num_uart)

	: ClassController::ControllerRewrite(NO)
	, _mem_uart(_num_uart)
{
	_mem_is_stick_lx_high = NO;
	_mem_is_stick_ly_high = NO;
	_mem_is_stick_rx_high = NO;
	_mem_is_stick_ry_high = NO;
}

//----------------------------------------------------------------------//

void ControllerBase :: Allot(const UartData8bit _data[NUM_CONTROLLER_28BIT])
{
	_mem_data._command._cross_x	= To_DirectionX((Is_true_the(_data[1], 4) << 1) | Is_true_the(_data[1], 3));
	_mem_data._command._cross_y	= To_DirectionY((Is_true_the(_data[0], 4) << 1) | Is_true_the(_data[0], 3));
	
	_mem_data._command._stick_left_x = To_DirectionX((Is_true_the(_data[2], 2) << 1) | Is_true_the(_data[2], 0));
	_mem_data._command._stick_left_y = To_DirectionY((Is_true_the(_data[3], 2) << 1) | Is_true_the(_data[3], 0));
	
	_mem_is_stick_lx_high = Is_true_the(_data[2], 1);
	_mem_is_stick_ly_high = Is_true_the(_data[3], 1);
	
	_mem_data._command._stick_right_x = To_DirectionX((Is_true_the(_data[0], 2) << 1) | Is_true_the(_data[0], 0));
	_mem_data._command._stick_right_y = To_DirectionY((Is_true_the(_data[1], 2) << 1) | Is_true_the(_data[1], 0));
	
	_mem_is_stick_rx_high = Is_true_the(_data[0], 1);
	_mem_is_stick_ry_high = Is_true_the(_data[1], 1);
	
	_mem_data._btns._right_left  = (_data[2] >> 1) & 0x0c;
	_mem_data._btns._right_left |= (_data[3] >> 3) & 0x03;
	
	_mem_data._btns._other = _data[4] & 0x0f;
	
	_mem_data._btns._mark = _data[5] & 0x0f;
}

//----------------------------------------------------------------------//

void ControllerBase :: Clear()
{
	_mem_data._array[0] = 0x00;
	_mem_data._array[1] = 0xf0;
	_mem_data._array[2] = 0xff;
	
	_mem_is_stick_lx_high = NO;
	_mem_is_stick_ly_high = NO;
	_mem_is_stick_rx_high = NO;
	_mem_is_stick_ry_high = NO;
}

//----------------------------------------------------------------------//

void ControllerBase :: Read(Uart::ModeReceive &_uart)
{
	if (_mem_uart.Is_receive_finished())
	{
		uByte _flag = 0;
		
		uByte _receive_data[NUM_CONTROLLER_24BIT] = {0x3f, 0x7f, 0x8f, 0xc0};
		
		_uart.Disable_9bit();
		
		for (uByte i = 0; i < 10; i++)
		{
			const UartData8bit _temp = _uart.Receive_8bit();
			
			const uByte _num = ((_temp >> 6) & 3);
			
			_receive_data[_num] = _temp;
			
			_flag |= (1 << _num);
			
			if (_flag == 0xf)	break;
		}
		
		Allot(_receive_data);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

}
}

/************************************************************************/
