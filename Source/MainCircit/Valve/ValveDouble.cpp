
#include <akilcd/akilcd.h>
#include <Others/BOOL.h>
#include <AVR/Timer/GeneralTimer.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Valve/ValveDouble.h>

/************************************************************************/

#define WAIT_MS_TIME 50

/************************************************************************/

//----------------------------------------------------------------------//

ValveDouble::ValveDouble
(
	const ValveNum _valveNC_number, 
	const ValveNum _valveNO_number
)
{
	_state_valveNC = NO;
	_state_valveNO = NO;
	
	this->_num_valveNC = _valveNC_number;
	this->_num_valveNO = _valveNO_number;
}

//----------------------------------------------------------------------//

void ValveDouble::Safety()
{
	if ((Get_state_valveNC() & Get_state_valveNO()))
	{
		Set_NC(NO);
		Set_NO(NO);
	}
}

//----------------------------------------------------------------------//

void ValveDouble::Toggle()
{
	switch (_next_moved_valve)
	{
		case VALVE_NC:
		{
			Set(YES, NO);
			
			_next_moved_valve = VALVE_NO;
			
			break;
		}
		case VALVE_NO:
		{
			Set(NO, YES);
			
			_next_moved_valve = VALVE_NC;
			
			break;
		}
	}
}

//----------------------------------------------------------------------//

void ValveDouble::Open_or_Close(const YesNo _is_move)
{
	Open_or_Close(_is_move, WAIT_MS_TIME);
}

//----------------------------------------------------------------------//

void ValveDouble::Open_or_Close(const YesNo _is_move, const mSecond _wait_time)
{
	if (_is_move & ~Is_timer_running())	//最初の動作。両方閉じる。カウント開始
	{
		Set(NO, NO);
		
		if (_wait_time <= WAIT_MS_TIME)
		{
			Start_timer(WAIT_MS_TIME);
		}
		else
		{
			Start_timer(_wait_time);
		}
	}
	
	if (Is_timer_finished())	//カウント完了
	{
		if ((Get_state_valveNC() | Get_state_valveNO()) == NO)	//どちらかの電磁弁を開く
		{
			Toggle();
		}
		
		if (_is_move == NO)	//最後の動作。次の動作に備える。
		{
			Finish_timer();
		}
	}
}

//----------------------------------------------------------------------//

void ValveDouble::Open_and_Close(const YesNo _is_move, const mSecond _close_time)
{
	Open_and_Close(_is_move, WAIT_MS_TIME, _close_time);
}

//----------------------------------------------------------------------//

void ValveDouble::Open_and_Close(const YesNo _is_move, const mSecond _open_time, const mSecond _close_time)
{
	if (_is_move & ~Is_timer_running())	//最初の動作。両方閉じる。カウント開始
	{
		if (Get_state_valveNC() == NO)
		{
			Set(NO, NO);
			
			_next_moved_valve = VALVE_NC;
			
			Start_timer(_open_time);
		}
	}
	
	if (Is_timer_finished())	//カウント完了
	{
		if ((Get_state_valveNC() | Get_state_valveNO()) == NO)
		{
			Start_timer(_close_time);
			
			switch (_next_moved_valve)
			{
				case VALVE_NC:
				{
					Set(YES, NO);
					
					break;
				}
				case VALVE_NO:
				{
					Set(NO, YES);
					
					break;
				}
			}
		}
		else if (Get_state_valveNC() == YES)
		{
			Set(NO, NO);
			
			_next_moved_valve = VALVE_NO;
			
			Start_timer(WAIT_MS_TIME);
		}
		else
		{
			if (_is_move == NO)	//最後の動作。次の動作に備える。
			{
				Finish_timer();
			}
		}
	}
}

//----------------------------------------------------------------------//

void ValveDouble :: Open_valve_A(const YesNo _want_to_move)
{
	if (_want_to_move & ~Is_timer_running())	//最初の動作
	{
		if (Get_state_valveNO())	//B電磁弁を閉じる。カウント開始
		{
			Set_NO(NO);
			
			Start_timer(WAIT_MS_TIME);
		}
		else	//A電磁弁を開ける。終わり。
		{
			Set_NC(YES);	
		}
	}
	
	if (Is_timer_finished())	//カウント完了
	{
		if (Get_state_valveNO() == NO)	Set_NC(YES);	//A電磁弁を開ける。終わり。
		
		if ((~Get_state_valveNC() | Get_state_valveNO() | _want_to_move) == NO)	//最後の動作。次の動作に備える。
		{
			Finish_timer();
		}
	}
}

//----------------------------------------------------------------------//

void ValveDouble :: Open_valve_B(const YesNo _want_to_move)
{
	if (_want_to_move & ~Is_timer_running())	//最初の動作
	{
		if (Get_state_valveNC())	//A電磁弁を閉じる。カウント開始
		{
			Set_NC(CLOSE);
			
			Start_timer(WAIT_MS_TIME);
		}
		else	//NO側を開ける。終わり。
		{
			Set_NO(OPEN);
		}
	}
	
	if (Is_timer_finished())	//カウント完了
	{
		if (Get_state_valveNC() == CLOSE)	Set_NO(OPEN);	//NO側を開ける。終わり。
		
		if ((Get_state_valveNC() | ~Get_state_valveNO() | _want_to_move) == NO)	//最後の動作。次の動作に備える。
		{
			Finish_timer();
		}
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
