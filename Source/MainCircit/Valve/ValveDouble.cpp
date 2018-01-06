
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
	if (_is_move & ~Is_timer_running())	//�ŏ��̓���B��������B�J�E���g�J�n
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
	
	if (Is_timer_finished())	//�J�E���g����
	{
		if ((Is_open_NC() | Is_open_NO()) == NO)	//�ǂ��炩�̓d���ق��J��
		{
			Toggle();
		}
		
		if (_is_move == NO)	//�Ō�̓���B���̓���ɔ�����B
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
	if (_is_move & ~Is_timer_running())	//�ŏ��̓���B��������B�J�E���g�J�n
	{
		if (Is_open_NC() == NO)
		{
			Want_to_open(NO, NO);
			
			_next_moved_valve = VALVE_NC;
			
			Start_timer(_open_time);
		}
	}
	
	if (Is_timer_finished())	//�J�E���g����
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
			if (_is_move == NO)	//�Ō�̓���B���̓���ɔ�����B
			{
				Finish_timer();
			}
		}
	}
}

//----------------------------------------------------------------------//

void ValveDouble :: Open_valve_A(const YesNo _want_to_move)
{
	if (_want_to_move & ~Is_timer_running())	//�ŏ��̓���
	{
		if (Is_open_NO())	//B�d���ق����B�J�E���g�J�n
		{
			Want_to_open_NO(NO);
			
			Start_timer(WAIT_MS_TIME);
		}
		else	//A�d���ق��J����B�I���B
		{
			Want_to_open_NC(YES);	
		}
	}
	
	if (Is_timer_finished())	//�J�E���g����
	{
		if (Is_open_NO() == NO)	Want_to_open_NC(YES);	//A�d���ق��J����B�I���B
		
		if ((~Is_open_NC() | Is_open_NO() | _want_to_move) == NO)	//�Ō�̓���B���̓���ɔ�����B
		{
			Finish_timer();
		}
	}
}

//----------------------------------------------------------------------//

void ValveDouble :: Open_valve_B(const YesNo _want_to_move)
{
	if (_want_to_move & ~Is_timer_running())	//�ŏ��̓���
	{
		if (Is_open_NC())	//A�d���ق����B�J�E���g�J�n
		{
			Want_to_open_NC(NO);
			
			Start_timer(WAIT_MS_TIME);
		}
		else	//B�d���ق��J����B�I���B
		{
			Want_to_open_NO(YES);
		}
	}
	
	if (Is_timer_finished())	//�J�E���g����
	{
		if (Is_open_NC() == NO)	Want_to_open_NO(YES);	//B�d���ق��J����B�I���B
		
		if ((Is_open_NC() | ~Is_open_NO() | _want_to_move) == NO)	//�Ō�̓���B���̓���ɔ�����B
		{
			Finish_timer();
		}
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
