

#pragma once

/************************************************************************/

typedef usint DataMotor;

typedef sint Pwm;

/************************************************************************/

typedef enum
{
	NUM_MD_0 = 0,
	NUM_MD_1 = 1,
	NUM_MD_2 = 2,
	NUM_MD_3 = 3
}
MdNum;
 
typedef enum
{
	NUM_MDC_0 = 0,
	NUM_MDC_1 = 1
}
MdcNum;

typedef enum
{
	MD_DATA_0 = 0,
	MD_DATA_1 = 1
}
DistiMD;

/************************************************************************/

#ifdef __cplusplus

namespace ClassMotor	{

#endif /*__cplusplus*/

/************************************************************************/

//MDに送信するデータのクラス
typedef struct
{
	//MDに送信するデータ。その0。
	union MotorData0
	{
		struct MotorPiece0
		{
			Signal	_sig			:2; //0,1
			BOOL	_is_steps_on	:1; //2
			usint	_without_		:2; //3,4
			DistiMD	_num_data		:1;	//5
			MdNum	_num_md			:2; //6,7
			MdcNum	_num_mdc		:1; //8
		}
		_sub;
		
		DataMotor _all :9;
	}
	_0;
	
	//MDに送信するデータ。その1。
	union MotorData1
	{
		struct MotorPiece1
		{
			Pwm		_pwm		:5; //0,1,2,3,4
			DistiMD _num_data	:1;	//5
			MdNum	_num_md		:2; //6,7
			MdcNum	_num_mdc	:1; //8
		}
		_sub;
		
		DataMotor _all :9;
	}
	_1;	
}
Motor;

/************************************************************************/

#ifdef __cplusplus

	}

#endif /*__cplusplus*/

/************************************************************************/