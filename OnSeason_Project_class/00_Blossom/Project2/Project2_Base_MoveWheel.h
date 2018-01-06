
#pragma once

namespace Project2
{

/************************************************************************/

namespace Base
{

/************************************************************************/

class MoveWheel
{
//variable
private:
		
	CountValue _mem_time_to_allow_reverse;
	
	YesNo _mem_is_enabled_reverse :1;
	
	Signal _mem_memory_signal[4];
	
protected:
	
	Mechanum _mem_wheel;
	
//function
private:
	
	void Adjust_pwm_move_y();
	
	void Adjust_pwm_move_x();
	
	void Adjust_pwm();
	
	void Memory_signal(Four::WheelPlace _place);
	
	void Memory_signal();
	
	void Set_stop_signal(Four::WheelPlace _place);
	
	void Set_stop_signal();
	
	void Stop_driving();
	
protected:
	
	void Operate_turn(Btn _is_turn_l, Btn _is_turn_r);
	
	void Operate_move(Direc::X _move_x, Direc::Y _move_y);
	
	void Operate_pwm(Btn _is_pwm_up, Btn _is_pwm_down);
	
	void Drive();
	
	void Transmit();
	
	void Transmit_clear();
	
public:
	
	MoveWheel();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline void MoveWheel :: Memory_signal(const Four::WheelPlace _place)
{
	_mem_memory_signal[_place] = _mem_wheel[_place].Get_sig();
}

//----------------------------------------------------------------------//

inline void MoveWheel :: Memory_signal()
{
	MoveWheel::Memory_signal(Four::FRONT_RIGHT);
	MoveWheel::Memory_signal(Four::FRONT_LEFT);
	MoveWheel::Memory_signal(Four::BACK_LEFT);
	MoveWheel::Memory_signal(Four::BACK_RIGHT);
}

//----------------------------------------------------------------------//

inline void MoveWheel :: Set_stop_signal(const Four::WheelPlace _place)
{
	_mem_wheel[_place] = Reversal(_mem_memory_signal[_place]);
}

//----------------------------------------------------------------------//

inline void MoveWheel :: Set_stop_signal()
{
	MoveWheel::Set_stop_signal(Four::FRONT_RIGHT);
	MoveWheel::Set_stop_signal(Four::FRONT_LEFT);
	MoveWheel::Set_stop_signal(Four::BACK_LEFT);
	MoveWheel::Set_stop_signal(Four::BACK_RIGHT);
}

//----------------------------------------------------------------------//

inline void MoveWheel :: Operate_turn(const Btn _is_turn_l, const Btn _is_turn_r)
{
	_mem_wheel.Record_direc_rote(_is_turn_r, _is_turn_l);
}

//----------------------------------------------------------------------//

inline void MoveWheel :: Operate_move(const Direc::X _move_x, const Direc::Y _move_y)
{	
	_mem_wheel.Record_direc(_move_x, _move_y);
}

//----------------------------------------------------------------------//

inline void MoveWheel :: Transmit()
{
	_mem_wheel.Transmit();
}

//----------------------------------------------------------------------//

inline void MoveWheel :: Transmit_clear()
{
	_mem_wheel.Transmit_clear();
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/

};

/************************************************************************/
