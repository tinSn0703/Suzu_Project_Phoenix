

#pragma once

/************************************************************************/

typedef usint MotorData;

typedef uByte MotorNumber;

typedef Byte Pwm;

/************************************************************************/

namespace ClassMotor
{

/************************************************************************/

typedef enum
{
	MD_DATA_0 = 0,
	MD_DATA_1 = 1
}
MdDigit;

/************************************************************************/

//MD�ɑ��M����f�[�^�̃N���X
struct Motor
{
	//MD�ɑ��M����f�[�^�B����0�B
	union MotorData0
	{
		struct MotorParts0
		{
			Signal		_sig			:2; //0,1
			BOOL		_is_steps_on	:1; //2
			usint		_without_		:2; //3,4
			MdDigit		_num_data		:1;	//5
			MotorNumber	_num_md			:3; //6,7,8
		}
		_sub;
		
		MotorData _all :9;
	}
	_0;
	
	//MD�ɑ��M����f�[�^�B����1�B
	union MotorData1
	{
		struct MotorParts1
		{
			Pwm			_pwm		:5; //0,1,2,3,4
			MdDigit		_num_data	:1;	//5
			MotorNumber	_num_md		:3; //6,7,8
		}
		_sub;
		
		MotorData _all :9;
	}
	_1;	
};

/************************************************************************/

};

/************************************************************************/
