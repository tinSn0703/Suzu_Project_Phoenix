
#include <akilcd/akilcd.h>
#include <Others/BOOL.h>
#include <AVR/Timer/GeneralTimer.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Valve/ValveBase/ValveBase.h>

/************************************************************************/

#define WAIT_MS_TIME 50

/************************************************************************/

namespace ClassValve
{

/************************************************************************/
/*	ValveBase															*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveBase :: ValveBase ()
{	
	Clear();
}

//----------------------------------------------------------------------//

void ValveBase :: Clear()
{
	_mem_data._all = 0x00;
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	ValveSet															*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveSet :: ValveSet ()	{}

//----------------------------------------------------------------------//

/************************************************************************/
/*	ValveGet															*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveGet :: ValveGet ()	{}

//----------------------------------------------------------------------//

/************************************************************************/
/*	ValveOperate														*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveOperate :: ValveOperate()
{	
	_mem_is_move_enabled = 0xff;
}

//----------------------------------------------------------------------//

void ValveOperate :: Set_timer(const ValveNum _num)
{
	_mem_timer[_num] = Timer::General::Read() + Timer::General::To_count_value(WAIT_MS_TIME);
}

//----------------------------------------------------------------------//

void ValveOperate :: Safety
(
	const ValveNum _num_a,
	const ValveNum _num_b
)
{
	if (Is_open_for(_num_a) & Is_open_for(_num_b))
	{
		Want_to_open(_num_a, FALSE);
		Want_to_open(_num_b, FALSE);
	}
}

//----------------------------------------------------------------------//

void ValveOperate :: Open_or_Close 
(
	const ValveNum	_num, 
	const BOOL		_is_move
)
{
	if (_is_move & Is_enabled(_num))
	{
		Toggle(_num);
		
		Want_to_enable(_num, FALSE);
		
		Set_timer(_num);
	}
	
	if (Compare_timer(_num))
	{
		Want_to_enable(_num, TRUE);
	}
}

//----------------------------------------------------------------------//

void ValveOperate :: Open_or_Close 
(
	const ValveNum	_num_a, 
	const ValveNum	_num_b, 
	const BOOL		_is_move
)
{
	if (_is_move & Is_enabled(_num_a))
	{
		Want_to_open(_num_a, NO);
		Want_to_open(_num_b, NO);
		
		Set_timer(_num_a);
	}
	
	if ((Is_open_for(_num_a) | Is_open_for(_num_b) | ~Compare_timer(_num_a)) == NO)
	{
		switch (Is_enabled(_num_b))
		{
			case YES:	Want_to_open(_num_a, YES);	break;
			case NO:	Want_to_open(_num_b, YES);	break;
		}
		
		Reversal_enabled(_num_b);
	}
	
	Safety(_num_a, _num_b);
	
	Want_to_enable(_num_a, ~_is_move);
}

//----------------------------------------------------------------------//

void ValveOperate :: Open_or_Close
(
	const ValveNum	_num_a, 
	const BOOL		_is_move_a, 
	const VALVE::Num	_num_b, 
	const BOOL		_is_move_b
)
{
	if ((Is_open_for(_num_b) & _is_move_a) == NO)
	{
		Open_or_Close(_num_a, _is_move_a);
	}
	
	if ((Is_open_for(_num_a) & _is_move_b) == NO)
	{
		Open_or_Close(_num_b, _is_move_b);
	}
	
	Safety(_num_a, _num_b);
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	SValveLCD															*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveLCD :: ValveLCD()	{}

//----------------------------------------------------------------------//

void ValveLCD :: Display(const LcdAdrs _adrs, const Decimal _decimal)
{
	switch (_decimal)
	{
		case DECIMAL_02:
		{
			LCD::Write(_adrs, Get(), 8, DECIMAL_02);
			
			break;
		}
		default:
		{
			LCD::Write(_adrs, Get(), 2, DECIMAL_16);
			
			break;
		}
	};
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
