
#include <akilcd/akilcd.h>
#include <Others/BOOL.h>
#include <AVR/AVR.h>
#include <MainCircit/Valve/ValveBase/ValveBase.h>

/************************************************************************/

namespace ClassValve
{

/************************************************************************/
/*	ValveBase															*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveBase :: ValveBase ()
{	
	ValveBase :: Clear();
}

//----------------------------------------------------------------------//

void ValveBase :: Clear()
{
	_mem_data._all = 0x00;
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	ValveWrite															*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveWrite :: ValveWrite ()
{}

//----------------------------------------------------------------------//

/************************************************************************/
/*	ValveRead															*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveRead :: ValveRead ()
{}

//----------------------------------------------------------------------//

/************************************************************************/
/*	ValveOperate														*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveOperate :: ValveOperate()
{	
	_mem_is_move_allow = 0xff;
		
	Timer_Initialize();
}

//----------------------------------------------------------------------//

void ValveOperate :: Confirm_safety
(
	const ValveNum _arg_num_a,
	const ValveNum _arg_num_b
)
{
	if (Is_open_for(_arg_num_a) & Is_open_for(_arg_num_b))
	{
		Want_to_open(_arg_num_a, FALSE);
		Want_to_open(_arg_num_b, FALSE);
	}
}

//----------------------------------------------------------------------//

void ValveOperate :: OpenClose 
(
	const ValveNum	_arg_num, 
	const BOOL		_arg_is_move
)
{
	if (_arg_is_move & Is_allow(_arg_num))
	{
		Toggle(_arg_num);
		
		Can_allow(_arg_num, FALSE);
		
		Set_timer(_arg_num);
	}
	
	if (Comp_timer(_arg_num))
	{
		Can_allow(_arg_num, TRUE);
	}
}

//----------------------------------------------------------------------//

void ValveOperate :: OpenClose 
(
	const ValveNum	_num_a, 
	const ValveNum	_num_b, 
	const BOOL		_is_move
)
{
	if (_is_move & Is_allow(_num_a))
	{
		Want_to_open(_num_a, FALSE);
		Want_to_open(_num_b, FALSE);
		
		Set_timer(_num_a);
	}
	
	if ((Is_open_for(_num_a) | Is_open_for(_num_b) | ~Comp_timer(_num_a)) == FALSE)
	{
		switch (Is_allow(_num_b))
		{
			case TRUE:	Want_to_open(_num_a, TRUE);	break;
			case FALSE:	Want_to_open(_num_b, TRUE);	break;
		}
		
		Reversal_allow(_num_b);
	}
	
	Confirm_safety(_num_a, _num_b);
	
	Can_allow(_num_a, ~_is_move);
}

//----------------------------------------------------------------------//

void ValveOperate :: OpenClose
(
	const ValveNum	_arg_num_a, 
	const BOOL		_arg_is_move_a, 
	const ValveNum	_arg_num_b, 
	const BOOL		_arg_is_move_b
)
{
	if ((Is_open_for(_arg_num_b) & _arg_is_move_a) == FALSE)
	{
		OpenClose(_arg_num_a, _arg_is_move_a);
	}
	
	if ((Is_open_for(_arg_num_a) & _arg_is_move_b) == FALSE)
	{
		OpenClose(_arg_num_b, _arg_is_move_b);
	}
	
	Confirm_safety(_arg_num_a, _arg_num_b);
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	SValveLCD															*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveLCD :: ValveLCD()	{}

//----------------------------------------------------------------------//

void ValveLCD :: LCD (const LcdAdrs _arg_adrs, const Decimal _arg_decimal)
{
	switch (_arg_decimal)
	{
		case DECIMAL_02:
		{
			LCD_Display_num(_arg_adrs, ValveRead :: Get(), 8, DECIMAL_02);
			
			break;
		}
		default:
		{
			LCD_Display_num(_arg_adrs, ValveRead :: Get(), 2, DECIMAL_16);
			
			break;
		}
	};
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
