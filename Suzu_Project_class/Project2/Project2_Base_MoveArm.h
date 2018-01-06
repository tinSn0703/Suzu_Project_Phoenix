
#pragma once

#include "Project2_Base_ArmSensor.h"

namespace Project2
{

/************************************************************************/

namespace Base
{

/************************************************************************/

class MovwUpDown
{
//variable
private:
	
	DirecY _mem_move_up_or_down :2;
	
protected:
	
	Motor _mem_up_dowm_motor;
	
//function
public:
	
	MovwUpDown();
	
	void Operate(DirecY _move_up_or_down);
	
	void Move();
};

/************************************************************************/

class MoveArm : public virtual ArmSensor
{
//variable
private:
	
	YesNo _mem_is_moved_auto :1;
	
	YesNo _mem_is_enabled_auto_move :1;
	
	CountValue _mem_time_auto_move;
	
	ArmSensor :: SensorSide _mem_move_side :1;
	
protected:
	
	Motor _mem_upper_arm_motor;
	
	Motor _mem_forearm_motor;
	
//function
private:
	
	void Move_manual();
	
	void Move_auto_right();
	
	void Move_auto_left();
	
protected:
	
	void Set_uart_upper_arm(UartTransmit * _uart);
	
	void Set_uart_forearm(UartTransmit * _uart);
	
public:
	
	MoveArm();
	
	void Operate(YesNo _is_enabled_auto_move);
	
	void Move();
	
	void Transmit();
	
	void Stop();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline void MoveArm :: Set_uart_upper_arm(UartTransmit * _uart)
{
	_mem_upper_arm_motor.Set_uart(_uart);
}

//----------------------------------------------------------------------//

inline void MoveArm :: Set_uart_forearm(UartTransmit * _uart)
{
	_mem_forearm_motor.Set_uart(_uart);
}

//----------------------------------------------------------------------//

inline void MoveArm :: Operate(const YesNo _is_enabled_auto_move)
{
	_mem_is_enabled_auto_move = _is_enabled_auto_move;
}

//----------------------------------------------------------------------//

inline void MoveArm :: Transmit()
{
	_mem_upper_arm_motor.Transmit();
	
	_mem_forearm_motor.Transmit();
}

//----------------------------------------------------------------------//

inline void MoveArm :: Stop()
{
	_mem_upper_arm_motor.Transmit_clear();
	
	_mem_forearm_motor.Transmit_clear();
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/

};

/************************************************************************/
