

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/AVR.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>

/************************************************************************/

//----------------------------------------------------------------------//

MDC :: MDC (const MdcNum _num, const int _num_of_slot)
{
	_mem_num_of_slot = To_within(_num_of_slot, 4, 2) - 1;
	
	for (usint _num_md = 0; _num_md <= _mem_num_of_slot; _num_md++)
	{
		Motor _temp(_num, (MdNum)_num_md);
		
		_mem_md[_num_md] = _temp;
	}
}

//----------------------------------------------------------------------//

MDC :: MDC (const MdcNum _num, const UartNum _adrs, const int _num_of_slot)

	 : _mem_uart(_adrs)
{
	_mem_num_of_slot = To_within(_num_of_slot, 4, 2) - 1;
	
	for (usint _num_md = 0; _num_md <= _mem_num_of_slot; _num_md++)
	{
		Motor _temp(_num, (MdNum)_num_md);
		
		_mem_md[_num_md] = _temp;
		_mem_md[_num_md].Set_uart(&_mem_uart);
	}
}

//----------------------------------------------------------------------//

void MDC :: Set (const Signal _arg_sig)
{
	MDC :: Set_direct(_arg_sig);
	
	if (Is_Signal_rotation(_arg_sig))
	{
		MDC :: Set_direct(0);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
