
#pragma once

#include "ValveBase/ValveBit.h"

/************************************************************************/

class ValveSingle : public ClassValveBit::ValveBase
{
//variable
private:
	
	YesNo _mem_is_valve_closed :1;
	
	ValveNum _mem_valve_number :3;
	
//function
private:
	
	void Toggle();
	
public:
	
	ValveSingle();
	ValveSingle(ValveNum _valve_number);
	
	void Reset(ValveNum _valve_number);
	
	ValveNum Get_valve_num();
	
	YesNo Is_open();
	
	void Want_to_open(YesNo _yes_no);
	
	void Open_or_Close(YesNo _want_to_move);
	
	ValveData Get_data();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline void ValveSingle :: Reset(const ValveNum _valve_slot_number)
{
	_mem_valve_number = _valve_slot_number;
}

//----------------------------------------------------------------------//

inline ValveNum ValveSingle :: Get_valve_num()
{
	return _mem_valve_number;
}

//----------------------------------------------------------------------//

inline YesNo ValveSingle :: Is_open()
{
	return _mem_is_valve_closed;
}

//----------------------------------------------------------------------//

inline void ValveSingle :: Want_to_open(const YesNo _yes_no)
{
	_mem_is_valve_closed = _yes_no;
}

//----------------------------------------------------------------------//

inline void ValveSingle :: Toggle()
{
	_mem_is_valve_closed = Reversal_BOOL(_mem_is_valve_closed);
}

//----------------------------------------------------------------------//

inline ValveData ValveSingle :: Get_data()
{
	return (_mem_is_valve_closed << _mem_valve_number);
}

//----------------------------------------------------------------------//

/************************************************************************/
