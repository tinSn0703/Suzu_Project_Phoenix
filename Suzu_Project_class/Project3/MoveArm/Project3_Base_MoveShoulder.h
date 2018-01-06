
#pragma once

/************************************************************************/

namespace Project3
{

namespace Base
{

namespace MoveArm
{

/************************************************************************/

class MoveShoulder
{
//variable
private:
	
	Motor _mem_motor;
	
	YesNo _mem_is_turn_right :1;
	
	YesNo _mem_is_turn_left :1;
	
//function
public:
	
	MoveShoulder(MotorNumber _motor_num, UartTransmit *_uart);
	
	void Set(UartTransmit *_uart);
	
	void Operate(YesNo _is_turn_left, YesNo _is_turn_right);
	
	void Operate(Pwm _pwm);
	
	void Move();
	
	void Transmit();
	
	void Transmit_clear();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline void MoveShoulder :: Set(UartTransmit *_uart)
{
	_mem_motor.Set_uart(_uart);
}

//----------------------------------------------------------------------//

inline void MoveShoulder :: Operate(const YesNo _is_turn_left, const YesNo _is_turn_right)
{
	_mem_is_turn_left	= _is_turn_left;
	_mem_is_turn_right	= _is_turn_right;
}

//----------------------------------------------------------------------//

inline void MoveShoulder :: Transmit()
{
	_mem_motor.Transmit();
}

//----------------------------------------------------------------------//

inline void MoveShoulder :: Transmit_clear()
{
	_mem_motor.Transmit_clear();
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

};

/************************************************************************/
