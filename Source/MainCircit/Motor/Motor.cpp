

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/AVR.h>
#include <MainCircit/Motor/Motor.h>

/************************************************************************/

//----------------------------------------------------------------------//

Motor :: Motor()	{}

//----------------------------------------------------------------------//

Motor :: Motor 
(
	const MdcNum	_arg_num_mdc, 
	const MdNum		_arg_num_md
)
{
	Initialize(_arg_num_mdc, _arg_num_md);

	_mem_memory_data_0 = 0x0;
	_mem_memory_data_1 = 0x0;
}

//----------------------------------------------------------------------//

void Motor :: Transmit ()
{	
	if	(
			(_mem_memory_data_0 != Get_data_0()) || 
			(_mem_memory_data_1 != Get_data_1())
		)
	{
		_mem_memory_data_0 = Get_data_0();
		_mem_memory_data_1 = Get_data_1();
		
		_mem_uart->Enable_9bit();
		
		_mem_uart->Transmit_9bit(Get_data_0());
		_mem_uart->Transmit_9bit(Get_data_1());
		
		_delay_us(100);
	}
}

//----------------------------------------------------------------------//

void Motor :: Transmit (UartTransmit &_arg_uart)
{
//	if	(
//			(_mem_memory_data_0 != Get_data_0()) || 
//			(_mem_memory_data_1 != Get_data_1())
//		)
	{
		_arg_uart.Enable_9bit();
		
		_arg_uart.Transmit_9bit(Get_data_0());
		_arg_uart.Transmit_9bit(Get_data_1());
		
		_delay_us(100);
	}
}

//----------------------------------------------------------------------//

void Motor :: Transmit_clear ()
{	
	_mem_uart->Enable_9bit();
	
	_mem_uart->Transmit_9bit(Get_data_0() & 0x1e0);
	_mem_uart->Transmit_9bit(Get_data_1() & 0x1e0);
	
	_delay_us(100);
}

//----------------------------------------------------------------------//

void Motor :: Transmit_clear (UartTransmit &_arg_uart)
{
	_arg_uart.Enable_9bit();
	
	_arg_uart.Transmit_9bit(Get_data_0() & 0x1e0);
	_arg_uart.Transmit_9bit(Get_data_1() & 0x1e0);
	
	_delay_us(100);
}

//----------------------------------------------------------------------//

/************************************************************************/
