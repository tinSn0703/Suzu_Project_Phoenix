
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/Uart/Uart.h>
#include <AVR/Timer/GeneralTimer.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Controller/Controller.h>

/************************************************************************/

namespace Controller
{
namespace Bit24
{

/************************************************************************/

//----------------------------------------------------------------------//

ControllerBase::ControllerBase(const UartNum _uart_num, const BOOL _is_data_rewrite)

	: ControllerRewrite(_is_data_rewrite)
	, _mem_uart(_uart_num)
{
	_mem_error_state = READ_NORMARY;
	
	_mem_timer = TIMER_INITAL_VALUE;
	
	_mem_receive_data[0] = 0x3f;
	_mem_receive_data[1] = 0x7f;
	_mem_receive_data[2] = 0x8f;
	_mem_receive_data[3] = 0xc0;
}

//----------------------------------------------------------------------//

void ControllerBase::Allot()
{
	_mem_data._command._cross_x	= To_DirectionX((Is_true_the(_mem_receive_data[0], 5) << 1) | Is_true_the(_mem_receive_data[1], 1));
	_mem_data._command._cross_y	= To_DirectionY((Is_true_the(_mem_receive_data[0], 4) << 1) | Is_true_the(_mem_receive_data[1], 0));
	
	_mem_data._command._stick_right_x	= To_DirectionX(_mem_receive_data[2] >> 4);
	_mem_data._command._stick_right_y	= To_DirectionY(_mem_receive_data[3] >> 0);
	
	_mem_data._command._stick_left_x	= To_DirectionX(_mem_receive_data[3] >> 2);
	_mem_data._command._stick_left_y	= To_DirectionY(_mem_receive_data[3] >> 4);
	
	_mem_data._btns._other = ((~_mem_receive_data[0]) & 0x0f);
	
	_mem_data._btns._right_left = ((~_mem_receive_data[1] >> 2) & 0x0f);
	
	_mem_data._btns._mark = ((~_mem_receive_data[2]) & 0x0f);
}

//----------------------------------------------------------------------//

void ControllerBase::Receive(Uart::ModeReceive &_uart)
{
	for (uByte i = 0, _flag = 0; i < NUM_LIMIT_RECEIVE; i++) //受信回数制限 正常時は大体5回程度で終了します。
	{
		_mem_timer = Timer::General::Set_counter(TIME_RECEIVE_WAIT); //受信の成否判断のタイマ開始
		
		while (1)
		{
			if (_uart.Is_receive_finished())	//受信成功。
			{
				const UartData8bit _temp = _uart.Get_UDR_8bit();	//受信データを受け取る
				
				if (_mem_uart.Is_error_happen() == NO)	//受信時にトラブルが発生したか確認
				{
					_mem_receive_data[((_temp >> 6) & 3)] = _temp;
					
					_flag |= (1 << ((_temp >> 6) & 3));
					
					if (_flag == 0x0f)	//全ての受信を完了
					{
						_mem_error_state = READ_SUCCESS;
						
						_mem_timer = TIMER_INITAL_VALUE;
						
						return (void)0;
					}
					else	//次の受信に移る
					{
						break;
					}
				}
			}
			else if (Timer::General::Is_current_bigger_than(_mem_timer)) //受信失敗 ひとまず次に移る。
			{
				break;
			}
		}
	}
	
	_mem_error_state = READ_INCOMPLETE;
	
	_mem_timer = TIMER_INITAL_VALUE;
}

//----------------------------------------------------------------------//

void ControllerBase::Start_timer(const mSecond _time)
{
	if (_mem_timer == TIMER_INITAL_VALUE)	//受信不可を判断するためのタイマを開始
	{
		_mem_timer = Timer::General::Set_counter(_time);
		
		_mem_error_state = READ_NORMARY;
	}
}

//----------------------------------------------------------------------//

void ControllerBase::Stop_timer()
{
	_mem_timer = TIMER_INITAL_VALUE;
}

//----------------------------------------------------------------------//

YesNo ControllerBase::Is_timer_finish()
{
	if (Timer::General::Is_current_bigger_than(_mem_timer))	//受信不可と判断
	{
		_mem_error_state = READ_FAILURE;
		
		return YES;
	}
	
	return NO;
}

//----------------------------------------------------------------------//

void ControllerBase::Read()
{
	if (_mem_uart.Is_receive_finished()) //データの読み取りに入れるかを確認
	{
		Receive(_mem_uart);
		
		Allot();
	}
	else
	{
		Start_timer(TIME_READ_ERROR);
		
		Is_timer_finish();
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

};
};

/************************************************************************/
