
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
	_is_valveNC_open = NO;
	_is_valveNO_open = NO;
	
	this->_valveNC_number = _valveNC_number;
	this->_valveNO_number = _valveNO_number;
}

//----------------------------------------------------------------------//

void ValveDouble::Safety()
{
	if ((Is_open_NC() & Is_open_NO()))
	{
		Want_to_open_NC(NO);
		Want_to_open_NO(NO);
	}
}

//----------------------------------------------------------------------//

void ValveDouble::Toggle()
{
	switch (_next_moved_valve)
	{
		case VALVE_NC:
		{
			Want_to_open_NC(YES);
			Want_to_open_NO(NO);
			
			_next_moved_valve = VALVE_NO;
			
			break;
		}
		case VALVE_NO:
		{
			Want_to_open_NC(NO);
			Want_to_open_NO(YES);
			
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
		Want_to_open(NO, NO);
		
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
		if ((Is_open_NC() | Is_open_NO()) == NO)	//どちらかの電磁弁を開く
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
		if (Is_open_NC() == NO)
		{
			Want_to_open(NO, NO);
			
			_next_moved_valve = VALVE_NC;
			
			Start_timer(_open_time);
		}
	}
	
	if (Is_timer_finished())	//カウント完了
	{
		if ((Is_open_NC() | Is_open_NO()) == NO)
		{
			switch (_next_moved_valve)
			{
				case VALVE_NC:
				{
					Want_to_open(YES, NO);
					
					Start_timer(_close_time);
					
					break;
				}
				case VALVE_NO:
				{
					Want_to_open(NO, YES);
					
					break;
				}
			}
		}
		else if (Is_open_NC() == YES)
		{
			Want_to_open(NO, NO);
			
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
		if (Is_open_NO())	//B電磁弁を閉じる。カウント開始
		{
			Want_to_open_NO(NO);
			
			Start_timer(WAIT_MS_TIME);
		}
		else	//A電磁弁を開ける。終わり。
		{
			Want_to_open_NC(YES);	
		}
	}
	
	if (Is_timer_finished())	//カウント完了
	{
		if (Is_open_NO() == NO)	Want_to_open_NC(YES);	//A電磁弁を開ける。終わり。
		
		if ((~Is_open_NC() | Is_open_NO() | _want_to_move) == NO)	//最後の動作。次の動作に備える。
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
		if (Is_open_NC())	//A電磁弁を閉じる。カウント開始
		{
			Want_to_open_NC(NO);
			
			Start_timer(WAIT_MS_TIME);
		}
		else	//B電磁弁を開ける。終わり。
		{
			Want_to_open_NO(YES);
		}
	}
	
	if (Is_timer_finished())	//カウント完了
	{
		if (Is_open_NC() == NO)	Want_to_open_NO(YES);	//B電磁弁を開ける。終わり。
		
		if ((Is_open_NC() | ~Is_open_NO() | _want_to_move) == NO)	//最後の動作。次の動作に備える。
		{
			Finish_timer();
		}
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
