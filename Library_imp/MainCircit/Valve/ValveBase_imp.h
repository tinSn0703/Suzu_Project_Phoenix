
#pragma once

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

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
{	
// 	_mem_fp_Can_open[0] = &ValveWrite :: Can_open_0;
// 	_mem_fp_Can_open[1] = &ValveWrite :: Can_open_1;
// 	_mem_fp_Can_open[2] = &ValveWrite :: Can_open_2;
// 	_mem_fp_Can_open[3] = &ValveWrite :: Can_open_3;
// 	_mem_fp_Can_open[4] = &ValveWrite :: Can_open_4;
// 	_mem_fp_Can_open[5] = &ValveWrite :: Can_open_5;
// 	_mem_fp_Can_open[6] = &ValveWrite :: Can_open_6;
// 	_mem_fp_Can_open[7] = &ValveWrite :: Can_open_7;
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	ValveToggle															*/
/************************************************************************/

//----------------------------------------------------------------------//

// ValveToggle :: ValveToggle ()
// {	
// 	_mem_fp_Toggle[0] = &ValveToggle :: Toggle_0;
// 	_mem_fp_Toggle[1] = &ValveToggle :: Toggle_1;
// 	_mem_fp_Toggle[2] = &ValveToggle :: Toggle_2;
// 	_mem_fp_Toggle[3] = &ValveToggle :: Toggle_3;
// 	_mem_fp_Toggle[4] = &ValveToggle :: Toggle_4;
// 	_mem_fp_Toggle[5] = &ValveToggle :: Toggle_5;
// 	_mem_fp_Toggle[6] = &ValveToggle :: Toggle_6;
// 	_mem_fp_Toggle[7] = &ValveToggle :: Toggle_7;
// }

//----------------------------------------------------------------------//

/************************************************************************/
/*	ValveRead															*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveRead :: ValveRead ()
{
// 	_mem_fp_Is_open[0] = &ValveRead :: Is_open_0;
// 	_mem_fp_Is_open[1] = &ValveRead :: Is_open_1;
// 	_mem_fp_Is_open[2] = &ValveRead :: Is_open_2;
// 	_mem_fp_Is_open[3] = &ValveRead :: Is_open_3;
// 	_mem_fp_Is_open[4] = &ValveRead :: Is_open_4;
// 	_mem_fp_Is_open[5] = &ValveRead :: Is_open_5;
// 	_mem_fp_Is_open[6] = &ValveRead :: Is_open_6;
// 	_mem_fp_Is_open[7] = &ValveRead :: Is_open_7;
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	ValveOperate														*/
/************************************************************************/

//----------------------------------------------------------------------//

ValveOperate :: ValveOperate()
{
// 	for (usint i = 0; i < 8; i++)
// 	{
// 		_mem_is_move_allow[i] = TRUE;
// 	}
	
	_mem_is_move_allow = 0xff;
		
	Timer_Init();
}
//----------------------------------------------------------------------//

void ValveOperate :: Check_safety
(
	const ValveNum _arg_num_a,
	const ValveNum _arg_num_b
)
{
	if (Is_open(_arg_num_a) & Is_open(_arg_num_b))
	{
		Can_open(_arg_num_a, FALSE);
		Can_open(_arg_num_b, FALSE);
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
	const ValveNum	_arg_num_a, 
	const ValveNum	_arg_num_b, 
	const BOOL		_arg_is_move
)
{
	if (_arg_is_move & Is_allow(_arg_num_a))
	{
		Can_open(_arg_num_a, FALSE);
		Can_open(_arg_num_b, FALSE);
		
		Set_timer(_arg_num_a);
	}
	
	if ((Is_open(_arg_num_a) | Is_open(_arg_num_b) | ~Comp_timer(_arg_num_a)) == FALSE)
	{
		switch (Is_allow(_arg_num_b))
		{
			case TRUE:	Can_open(_arg_num_a, TRUE);	break;
			case FALSE:	Can_open(_arg_num_b, TRUE);	break;
		}
		
		Reversal_allow(_arg_num_b);
	}
	
	Check_safety(_arg_num_a, _arg_num_b);
	
	Can_allow(_arg_num_a, ~_arg_is_move);
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
	if ((Is_open(_arg_num_b) & _arg_is_move_a) == FALSE)
	{
		OpenClose(_arg_num_a, _arg_is_move_a);
	}
	
	if ((Is_open(_arg_num_a) & _arg_is_move_b) == FALSE)
	{
		OpenClose(_arg_num_b, _arg_is_move_b);
	}
	
	Check_safety(_arg_num_a, _arg_num_b);
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
			LCD_Display_num(_arg_adrs, ValveRead :: Read(), 8, DECIMAL_02);
			
			break;
		}
		default:
		{
			LCD_Display_num(_arg_adrs, ValveRead :: Read(), 2, DECIMAL_16);
			
			break;
		}
	};
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/

#endif	//__cplusplus

/************************************************************************/

