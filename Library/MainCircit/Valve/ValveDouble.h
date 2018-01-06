
#pragma once

/************************************************************************/

#include "ValveBase/ValveBit.h"

/************************************************************************/

class ValveDouble : public ClassValveBit::ValveBase
{
//variable
private:
	
	YesNo _mem_is_valveA_closed :1;
	YesNo _mem_is_valveB_closed :1;
	
	ValveNum _mem_valveA_number :3;
	ValveNum _mem_valveB_number :3;
	
	enum DoubleValve
	{
		VALVE_A = 0,
		VALVE_B = 1
	}
	_mem_choise_moved_valve :1; 
	
//function
private:
	
	void Toggle();
		
	void Safety();
	
public:
	
	ValveDouble();
	ValveDouble(ValveNum _valveA_number, ValveNum _valveB_number);
	
	void Reset(ValveNum _valveA_number, ValveNum _valveB_number);
	
	ValveNum Get_valveA_num();
	ValveNum Get_valveB_num();
	
	YesNo Is_open_A();
	YesNo Is_open_B();
	
	void Want_to_open_A(YesNo _yes_no);
	void Want_to_open_B(YesNo _yes_no);	
	
	void Open_or_Close(YesNo _want_to_move);
	
	ValveData Get_data();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline void ValveDouble :: Reset
(
	const ValveNum _valveA_num, 
	const ValveNum _valveB_num
)
{
	_mem_valveA_number = _valveA_num;
	_mem_valveB_number = _valveB_num;
}

//----------------------------------------------------------------------//

inline ValveNum ValveDouble :: Get_valveA_num()
{
	return _mem_valveA_number;
}

//----------------------------------------------------------------------//

inline ValveNum ValveDouble :: Get_valveB_num()
{
	return _mem_valveB_number;
}

//----------------------------------------------------------------------//

inline YesNo ValveDouble :: Is_open_A()
{
	return _mem_is_valveA_closed;
}

//----------------------------------------------------------------------//

inline YesNo ValveDouble :: Is_open_B()
{
	return _mem_is_valveB_closed;
}

//----------------------------------------------------------------------//

inline void ValveDouble :: Want_to_open_A(const YesNo _yes_no)
{
	_mem_is_valveA_closed = _yes_no;
}

//----------------------------------------------------------------------//

inline void ValveDouble :: Want_to_open_B(const YesNo _yes_no)
{
	_mem_is_valveB_closed = _yes_no;
}

//----------------------------------------------------------------------//

inline ValveData ValveDouble :: Get_data()
{
	return 
	(
		(_mem_is_valveA_closed << _mem_valveA_number) |
		(_mem_is_valveB_closed << _mem_valveB_number)
	);
}

//----------------------------------------------------------------------//

/************************************************************************/
