
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/AVR.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Signal.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>
#include <MainCircit/MDC/Wheel.h>

/************************************************************************/

//----------------------------------------------------------------------//

Wheel :: Wheel(const UartNum _uart_num, const Byte _num_wheel)

	: MDC(_uart_num, _num_wheel)
{
	_mem_pwm = 0;
	
	Set_turn_direction(NON_TURN);
	
	Set_move_direction(Direction::xCENTER, Direction::yCENTER);
	
	Set_steps(STEPS_USE);
}

//----------------------------------------------------------------------//

void Wheel::Set_turn_direction(const YesNo _is_turn_l, const YesNo _is_turn_r)
{
	if		(_is_turn_l)	_mem_direc_turn = LEFT_TURN;
	else if (_is_turn_r)	_mem_direc_turn = RIGHT_TURN;
	else					_mem_direc_turn = NON_TURN;
}

//----------------------------------------------------------------------//

void Wheel::operator ++ (int i)
{
	if (_mem_pwm < 31)	_mem_pwm ++;
}

//----------------------------------------------------------------------//

void Wheel::operator -- (int i)
{
	if (_mem_pwm > 0)	_mem_pwm --;
}

//----------------------------------------------------------------------//

/************************************************************************/

