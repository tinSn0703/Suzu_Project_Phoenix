
#pragma once

/************************************************************************/

namespace Project3
{

namespace Base
{

/************************************************************************/

class MoveWheel
{
//variable
private:
	
	OmuniOpposite _mem_wheel;
	
	CountValue _mem_time_to_allow_reverse;
	
	YesNo _mem_is_enabled_reverse :1;
	
	Signal _mem_memory_signal[4];
	
//function
private:
	
	void Adjust_pwm_move_y();
	
	void Adjust_pwm_move_x();
	
	void Adjust_pwm();
	
	void Memory_signal();
	
	void Set_stop_signal();
	
	void Move_Counter();
	
public:
	
	MoveWheel(UartNum _uart_num_wheel, MotorNumber _motor_min_num);
	
	void Operate_turn(Btn _is_turn_l, Btn _is_turn_r);
	
	void Operate_move(Direc::X _move_x, Direc::Y _move_y);
	
	void Operate_pwm(Btn _is_pwm_up, Btn _is_pwm_down);
	
	void Move();
	
	void Transmit();
	
	void Stop();
	
	Pwm Get_pwm();
	
	Pwm Get_pwm(Four::WheelPlace _place);
	
	Direc::X Get_direc_x();
	
	Direc::Y Get_direc_y();
	
	Signal Get_signal(Four::WheelPlace _place);
	
	UartTransmit * Get_uart();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline void MoveWheel :: Operate_turn(const Btn _is_turn_l, const Btn _is_turn_r)
{
	_mem_wheel.Record_direc_rote(_is_turn_l, _is_turn_r);
}

//----------------------------------------------------------------------//

inline void MoveWheel :: Operate_move(const Direc::X _move_x, const Direc::Y _move_y)
{
	_mem_wheel.Record_direc(_move_x, _move_y);
}

//----------------------------------------------------------------------//

inline Direc::X MoveWheel :: Get_direc_x()
{
	return _mem_wheel.Get_direc_x();
}

//----------------------------------------------------------------------//

inline Direc::Y MoveWheel :: Get_direc_y()
{
	return _mem_wheel.Get_direc_y();
}

//----------------------------------------------------------------------//

inline void MoveWheel :: Transmit()
{
	_mem_wheel.Transmit();
}

//----------------------------------------------------------------------//

inline void MoveWheel :: Stop()
{
	_mem_wheel.Transmit_clear();
}

//----------------------------------------------------------------------//

inline Pwm MoveWheel :: Get_pwm()
{
	return _mem_wheel.Get_pwm();
}

//----------------------------------------------------------------------//

inline Pwm MoveWheel :: Get_pwm(const Four::WheelPlace _place)
{
	return _mem_wheel[_place].Get_pwm();
}

//----------------------------------------------------------------------//

//----------------------------------------------------------------------//

//----------------------------------------------------------------------//

inline UartTransmit * MoveWheel :: Get_uart()
{
	return _mem_wheel.Get_uart();
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};
