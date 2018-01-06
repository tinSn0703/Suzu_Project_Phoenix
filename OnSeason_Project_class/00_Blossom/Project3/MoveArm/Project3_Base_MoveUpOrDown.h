
#pragma once

/************************************************************************/

namespace Project3
{

namespace Base
{

namespace MoveArm
{

/************************************************************************/

class MoveUpOrDown
{
//variable
private:
	
	Motor _mem_motor;
	
	YesNo _mem_is_move_up :1;
	
	YesNo _mem_is_move_down :1;
	
//function
private:
	
public:
	
	MoveUpOrDown(MotorNumber _motor_num, UartTransmit *_uart);
	
	void Set(UartTransmit *_uart);
	
	void Operate(YesNo _is_move_up, YesNo _is_move_down);
	
	void Operate(Pwm _pwm);
	
	void Move();
	
	void Transmit();
	
	void Transmit_clear();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline void MoveUpOrDown :: Set(UartTransmit *_uart)
{
	_mem_motor.Set_uart(_uart);
}

//----------------------------------------------------------------------//

inline void MoveUpOrDown :: Operate(const YesNo _is_move_up, const YesNo _is_move_down)
{
	_mem_is_move_down	= _is_move_down;
	_mem_is_move_up		= _is_move_up;
}

//----------------------------------------------------------------------//

inline void MoveUpOrDown :: Transmit()
{
	_mem_motor.Transmit();
}

//----------------------------------------------------------------------//

inline void MoveUpOrDown :: Transmit_clear()
{
	_mem_motor.Transmit_clear();
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

};

/************************************************************************/
