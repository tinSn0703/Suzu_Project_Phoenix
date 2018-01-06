
#pragma once

/************************************************************************/

#include "Valve_type.h"

/************************************************************************/

namespace ClassValveBit
{

/************************************************************************/

#define WAIT_MS_TIME 100

/************************************************************************/

class ValveBase
{
//variable
private:
	
	CountValue _mem_timer;
	
	YesNo _mem_is_move_enabled :1;
	
//function
protected:
	
	void Start_timer();
	
	void Finish_timer();
	
	YesNo Is_timer_finished();
	
	void Want_move_enabled(YesNo _yes_no);
	
	YesNo Is_move_enable();
	
public:
	
	ValveBase();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline void ValveBase :: Start_timer()
{
	Want_move_enabled(NO);
	
	_mem_timer = GeneralTimer::Read() + GeneralTimer::Change_count_value(WAIT_MS_TIME);
}

//----------------------------------------------------------------------//

inline YesNo ValveBase :: Is_timer_finished()
{
	return GeneralTimer::Is_current_bigger_than(_mem_timer);
}

//----------------------------------------------------------------------//

inline void ValveBase :: Want_move_enabled(const YesNo _yes_no)
{
	_mem_is_move_enabled = _yes_no;
}

//----------------------------------------------------------------------//

inline YesNo ValveBase :: Is_move_enable()
{
	return _mem_is_move_enabled;
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/
