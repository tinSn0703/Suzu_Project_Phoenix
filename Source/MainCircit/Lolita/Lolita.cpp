
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/AVR.h>
#include <MainCircit/Lolita/Lolita.h>

/************************************************************************/

//----------------------------------------------------------------------//

Lolita :: Lolita(const UartNum _uart_num)

	: _mem_uart(_uart_num)

{
	Initialize();
}

//----------------------------------------------------------------------//

void Lolita :: Initialize()
{	
	_mem_is_make_round = NO;
	
	_mem_data = 512;
	
	_mem_memory = 512;
}

//----------------------------------------------------------------------//

void Lolita :: Check_round()
{
	if ((_mem_data < 123) && (900 < _mem_memory))
	{
		_mem_is_make_round = YES;
	}
	else if ((_mem_memory < 123) && (900 < _mem_data))
	{
		_mem_is_make_round = YES;
	}
	else
	{
		_mem_is_make_round = NO;
	}
}

//----------------------------------------------------------------------//

void Lolita :: Read()
{
	uByte _flag = 0;
	
	_mem_data = 0;
	
	_mem_uart.Disable_9bit();
	
	for (uByte i = 0; i < 4; i++)
	{			
		const UartData8bit _temp = _mem_uart.Receive_8bit();
		
		const uByte _num = ((_temp >> 7) & 1);
		
		switch (_num)
		{
			case 1:	_mem_data |= ((_temp & 0x0f) << 6);	break;
			case 0:	_mem_data |= (_temp & 0x3f);		break;
 		}
		
		_flag |= (1 << _num);
		
		if (_flag == 0b11)	break;
	}
	
	_mem_memory = _mem_data;
	
	Check_round();
}

//----------------------------------------------------------------------//

/************************************************************************/
