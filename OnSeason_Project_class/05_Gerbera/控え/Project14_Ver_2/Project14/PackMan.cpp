
#include <MainCircit/MainCircit.h>

#include "PackMan.h"

/************************************************************************/

namespace Gerbera
{
namespace BanriFinal
{

/************************************************************************/

#define NUM_MOTOR_ARM 4

#define RIGHT_OVER	0
#define LEFT_OVER	1
#define LEFT_UNDER	2
#define RIGHT_UNDER	3

#define PWM_PACK_MAN_OVER	16
#define PWM_PACK_MAN_UNDER	10

/************************************************************************/

//----------------------------------------------------------------------//

PackMan::PackMan(const MotorNum _num, const UartNum _uart_num)
	
	: _motor_pack_man_stand(_num, _uart_num)
{
	_motor_pack_man_stand.Want_to_use_steps(YES);
	
	_motor_pack_man_arm[RIGHT_OVER	].Reset(IO::NUM_E, IO::BIT_3, IO::BIT_2);
	_motor_pack_man_arm[LEFT_OVER	].Reset(IO::NUM_E, IO::BIT_5, IO::BIT_4);
	_motor_pack_man_arm[LEFT_UNDER	].Reset(IO::NUM_E, IO::BIT_7, IO::BIT_6);
	_motor_pack_man_arm[RIGHT_UNDER	].Reset(IO::NUM_F, IO::BIT_1, IO::BIT_0);
	
	_limit_stand_under.Reset(IO::NUM_F, IO::BIT_2);
	_limit_stand_over.Reset( IO::NUM_F, IO::BIT_3);
	
	_limit_arm_stretch[RIGHT_OVER	].Reset(IO::NUM_F, IO::BIT_4);
	_limit_arm_stretch[LEFT_OVER	].Reset(IO::NUM_F, IO::BIT_5);
	_limit_arm_stretch[LEFT_UNDER	].Reset(IO::NUM_F, IO::BIT_6);
	_limit_arm_stretch[RIGHT_UNDER	].Reset(IO::NUM_F, IO::BIT_7);
	
	_limit_arm_shorten[RIGHT_OVER	].Reset(IO::NUM_K, IO::BIT_0);
	_limit_arm_shorten[LEFT_OVER	].Reset(IO::NUM_K, IO::BIT_2);
	_limit_arm_shorten[LEFT_UNDER	].Reset(IO::NUM_K, IO::BIT_2);
	_limit_arm_shorten[RIGHT_UNDER	].Reset(IO::NUM_K, IO::BIT_3);
	
	_direcion_stand = Direction::yCENTER;
	
	_is_stand_over  = YES;
	_is_stand_under = YES;
}

//----------------------------------------------------------------------//

void PackMan::Clear()
{
	_direcion_stand = Direction::yCENTER;
	
	_motor_pack_man_stand.Set(SIGNAL_BREAK);
}

//----------------------------------------------------------------------//

void PackMan::Read()
{
	_limit_stand_over.Read();
	_limit_stand_under.Read();
	
	for (uByte i = 0; i < NUM_MOTOR_ARM; i++)
	{
		_limit_arm_stretch[i].Read();
		_limit_arm_shorten[i].Read();
	}
}

//----------------------------------------------------------------------//

void PackMan::Set_stand_over(const YesNo _yes_no)
{
	if (_yes_no)
	{
		if (_is_stand_over)
		{
			if (_direcion_stand == Direction::OVER)
			{
				_direcion_stand = Direction::yCENTER;
			}
			else
			{
				_direcion_stand = Direction::OVER;
			}
			
			_is_stand_over = NO;
		}
	}
	else
	{
		_is_stand_over = YES;
	}
}

//----------------------------------------------------------------------//

void PackMan::Set_stand_under(const YesNo _yes_no)
{
	if (_yes_no)
	{
		if (_is_stand_under)
		{
			if (_direcion_stand == Direction::UNDER)
			{
				_direcion_stand = Direction::yCENTER;
			}
			else
			{
				_direcion_stand = Direction::UNDER;
			}
			
			_is_stand_under = NO;
		}
	}
	else
	{
		_is_stand_under = YES;
	}
}

//----------------------------------------------------------------------//

void PackMan::Move_stand()
{
	switch (_direcion_stand)
	{
		case Direction::OVER:
		{
			if (_limit_stand_over.Get())
			{
				_motor_pack_man_stand.Set(SIGNAL_FORWARD, PWM_PACK_MAN_OVER);
			}
			else
			{
				_motor_pack_man_stand.Set(SIGNAL_BREAK);
				
				_direcion_stand = Direction::yCENTER;
			}
			
			break;
		}
		case Direction::UNDER:
		{
			if (_limit_stand_under.Get())
			{
				_motor_pack_man_stand.Set(SIGNAL_REVERSE, PWM_PACK_MAN_UNDER);
			}
			else
			{
				_motor_pack_man_stand.Set(SIGNAL_BREAK);
				
				_direcion_stand = Direction::yCENTER;
			}
			
			break;
		}
		case Direction::yCENTER:
		{
			_motor_pack_man_stand.Set(SIGNAL_BREAK);
			
			break;
		}
	}
}

//----------------------------------------------------------------------//

void PackMan::Move_pack_man_arm_stretch()
{
	for (uByte i = 0; i < NUM_MOTOR_ARM; i++)
	{
		if (_limit_arm_stretch[i].Get() == NO)
		{
			_motor_pack_man_arm[i].Set(SIGNAL_FORWARD);
		}
		else
		{
			_motor_pack_man_arm[i].Set(SIGNAL_FREE);
		}
	}
}

//----------------------------------------------------------------------//

void PackMan::Move_pack_man_arm_shorten()
{
	for (uByte i = 0; i < NUM_MOTOR_ARM; i++)
	{
		if (_limit_arm_shorten[i].Get() == NO)
		{
			_motor_pack_man_arm[i].Set(SIGNAL_REVERSE);
		}
		else
		{
			_motor_pack_man_arm[i].Set(SIGNAL_FREE);
		}
	}
}

//----------------------------------------------------------------------//

void PackMan::Move_pack_man_arm_stop()
{
	for (uByte i = 0; i < NUM_MOTOR_ARM; i++)
	{
		_motor_pack_man_arm[i].Set(SIGNAL_FREE);
	}
}

//----------------------------------------------------------------------//

void PackMan::Move_pack_man_arm(const YesNo _is_stretch, const YesNo _is_shorten)
{
	if (_is_stretch)		Move_pack_man_arm_stretch();
	else if (_is_shorten)	Move_pack_man_arm_shorten();
	else					Move_pack_man_arm_stop();
}

//----------------------------------------------------------------------//

void PackMan::Move_pack_man_arm(const DirectionY _move)
{
	switch (_move)
	{
		case Direction::OVER:		Move_pack_man_arm_stretch();	break;
		case Direction::UNDER:		Move_pack_man_arm_shorten();	break;
		case Direction::yCENTER:	Move_pack_man_arm_stop();		break;
	}
}

//----------------------------------------------------------------------//

void PackMan::Write()
{
	_motor_pack_man_stand.Write();
	
	for (uByte i = 0; i < NUM_MOTOR_ARM; i++)
	{
		_motor_pack_man_arm[i].Write();
	}
}

//----------------------------------------------------------------------//

void PackMan::Write_clear()
{
	_motor_pack_man_stand.Write_clear();
	
	for (uByte i = 0; i < NUM_MOTOR_ARM; i++)
	{
		_motor_pack_man_arm[i].Write_clear();
	}
}

//----------------------------------------------------------------------//

void PackMan::Display_motor_stand(const LcdAdrs _adrs)
{
	_motor_pack_man_stand.Display_signal(_adrs);
}

//----------------------------------------------------------------------//

void PackMan::Display_motor_arm(const LcdAdrs _adrs, const uByte _space)
{
	for (uByte i = 0; i < NUM_MOTOR_ARM; i++)
	{
		LCD::Write(_adrs + i * (_space + 1), _motor_pack_man_arm[i].Get(), 1, DECIMAL_10);
	}
}

//----------------------------------------------------------------------//

void PackMan::Display_sensor_stand(const LcdAdrs _adrs, const uByte _space)
{
	LCD::Write(_adrs + 0,			_limit_stand_over.Get(),  1, DECIMAL_02);
	LCD::Write(_adrs + 1 + _space,	_limit_stand_under.Get(), 1, DECIMAL_02);
}

//----------------------------------------------------------------------//

void PackMan::Display_sensor_arm_stretch(const LcdAdrs _adrs, const uByte _space)
{
	for (uByte i = 0; i < NUM_MOTOR_ARM; i++)
	{
		LCD::Write(_adrs + i * (_space + 1), _limit_arm_stretch[i].Get(), 1, DECIMAL_02);
	}
}

//----------------------------------------------------------------------//

void PackMan::Display_sensor_arm_shorten(const LcdAdrs _adrs, const uByte _space)
{
	for (uByte i = 0; i < NUM_MOTOR_ARM; i++)
	{
		LCD::Write(_adrs + i * (_space + 1), _limit_arm_shorten[i].Get(), 1, DECIMAL_02);
	}
}

//----------------------------------------------------------------------//

void PackMan::Display_sensor_num_stand_over(const LcdAdrs _adrs)
{
	LCD::Write(_adrs + 0, _limit_stand_over.Get_num());
	LCD::Write(_adrs + 1, _limit_stand_over.Get_bit(), 1, DECIMAL_10);
}

//----------------------------------------------------------------------//

void PackMan::Display_sensor_num_stand_under(const LcdAdrs _adrs)
{
	LCD::Write(_adrs + 0, _limit_stand_under.Get_num());
	LCD::Write(_adrs + 1, _limit_stand_under.Get_bit(), 1, DECIMAL_10);
}

//----------------------------------------------------------------------//

void PackMan::Display_sensor_num_arm_stretch(const LcdAdrs _adrs, const uByte _space)
{
	for (uByte i = 0; i < NUM_MOTOR_ARM; i ++)
	{
		LCD::Write(_adrs + 0 + i * (_space + 1), _limit_arm_stretch[i].Get_num());
		LCD::Write(_adrs + 1 + i * (_space + 1), _limit_arm_stretch[i].Get_bit(), 1, DECIMAL_10);
	}
}

//----------------------------------------------------------------------//

void PackMan::Display_sensor_num_arm_shorten(const LcdAdrs _adrs, const uByte _space)
{
	for (uByte i = 0; i < NUM_MOTOR_ARM; i ++)
	{
		LCD::Write(_adrs + 0 + i * (_space + 1), _limit_arm_shorten[i].Get_num());
		LCD::Write(_adrs + 1 + i * (_space + 1), _limit_arm_shorten[i].Get_bit(), 1, DECIMAL_10);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/

};
};

/************************************************************************/
