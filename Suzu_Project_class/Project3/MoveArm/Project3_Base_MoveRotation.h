
#pragma once

/************************************************************************/

namespace Project3
{

namespace Base
{

namespace MoveArm
{


/************************************************************************/

class MoveRotation
{
//variable
private:
	
	Motor _mem_motor;
	
	Lolita _mem_lolita;
	
	YesNo _mem_is_turn_right :1;
	
	YesNo _mem_is_turn_left :1;
	
	YesNo _mem_is_auto_enabled :1;
	
	YesNo _mem_is_o_current :1;
	
	DataBit16 _mem_data_o :10;
	DataBit16 _mem_data_r :10;
	
	DataBit16 _mem_target_value :10;

//function
private:
	
	void Move_auto();
	
public:
	
	MoveRotation(MotorNumber _motor_num,UartTransmit *_uart, UartNum _lolita_uart_num);
	
	void Set(UartTransmit *_uart);
	
	void Read();
	
	void Operate(YesNo _is_turn_left, YesNo _is_turn_right);
	
	void Operate(Direction _move_direction);
	
	void Operate(Pwm _pwm);
	
	void Move();
	
	DataBit16 Get_target();
	
	DataBit16 Get_loup();
	
	DataBit16 Get_current();
	
	DataBit16 Get_current_o();
	
	DataBit16 Get_current_r();
	
	void Transmit();
	
	void Transmit_clear();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline void MoveRotation :: Set(UartTransmit *_uart)
{
	_mem_motor.Set_uart(_uart);
}

//----------------------------------------------------------------------//

inline void MoveRotation :: Operate(const YesNo _is_turn_left, const YesNo _is_turn_right)
{
	_mem_is_turn_left	= _is_turn_left;
	_mem_is_turn_right	= _is_turn_right;
}

//----------------------------------------------------------------------//

inline DataBit16 MoveRotation :: Get_target()
{
	return _mem_target_value;
}

//----------------------------------------------------------------------//

inline DataBit16 MoveRotation :: Get_current()
{
	return  (_mem_is_o_current ? _mem_data_o : _mem_data_r);
}

//----------------------------------------------------------------------//

inline DataBit16 MoveRotation :: Get_current_o()
{
	return _mem_data_o;
}

//----------------------------------------------------------------------//

inline DataBit16 MoveRotation :: Get_current_r()
{
	return _mem_data_r;
}

//----------------------------------------------------------------------//

inline void MoveRotation :: Transmit()
{
	_mem_motor.Transmit();
}

//----------------------------------------------------------------------//

inline void MoveRotation :: Transmit_clear()
{
	_mem_motor.Transmit_clear();
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

};

/************************************************************************/
