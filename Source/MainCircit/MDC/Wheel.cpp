

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/AVR.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>
#include <MainCircit/MDC/Wheel.h>

/************************************************************************/

//----------------------------------------------------------------------//

Wheel :: Wheel(MdcNum _num_mdc, UartNum _uart_num)

	: MDC(_num_mdc, _uart_num, 4)

{
	_is_invert_y = FALSE;
	
	Wheel :: Set(CENTER_X, CENTER_Y);
}

//----------------------------------------------------------------------//

void Wheel :: Turning 
(
	const BOOL	_is_turn_right, 
	const BOOL	_is_turn_left
)
{
	MDC :: Set
	(
		_is_turn_right	? SIGNAL_FORWARD :
		_is_turn_left	? SIGNAL_REVERSE :
		SIGNAL_BREAK
	);
	
	MDC :: Can_you_want_use_steps(YES);
}

//----------------------------------------------------------------------//

void Wheel :: Drive_front_or_back()
{
	//2017 4/5
	//ちゃんと動くかわかってないのでチェックを忘れないでください
	
	const Byte _temp_right = 
	(
		_is_invert_y ? Reversal_DirecY(_mem_direc_y) : _mem_direc_y
	);
	
	const Byte _temp_left = 
	(
		_is_invert_y ? _mem_direc_y : Reversal_DirecY(_mem_direc_y)
	);
	
	_mem_md[FRONT_RIGHT] = Convert_to_Signal(_temp_right);
	_mem_md[BACK_RIGHT]	 = Convert_to_Signal(_temp_right);
	_mem_md[BACK_LEFT]	 = Convert_to_Signal(_temp_left);
	_mem_md[FRONT_LEFT]	 = Convert_to_Signal(_temp_left);
	
	MDC :: Can_you_want_use_steps(YES);
}

//----------------------------------------------------------------------//

/************************************************************************/
