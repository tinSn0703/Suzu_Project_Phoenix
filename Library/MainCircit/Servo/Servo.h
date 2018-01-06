
#pragma once

/************************************************************************/

typedef Byte ServoData;
typedef Byte ServoAngle;

/************************************************************************/

enum ServoOldNumber
{
	SERVO_OLD_NUM_0 = 0,
	SERVO_OLD_NUM_1 = 1
};

enum ServoNewNumber
{
	SERVO_NEW_NUM_0 = 0,
	SERVO_NEW_NUM_1 = 1,
	SERVO_NEW_NUM_2 = 2,
	SERVO_NEW_NUM_3 = 3,
	SERVO_NEW_NUM_4 = 4,
	SERVO_NEW_NUM_5 = 5,
	SERVO_NEW_NUM_6 = 6,
	SERVO_NEW_NUM_7 = 7
};

/************************************************************************/

class Servo
{
private:
	
	union ServoBitData
	{
		struct OldServoBitData
		{
			ServoAngle		_angle	:7;
			ServoOldNumber	_number	:1;
		}
		_old;
		
		struct NewServoBitData
		{
			ServoAngle		_angle	:5;
			ServoNewNumber	_number	:3;
		}
		_new;
		
		ServoData _data :8;
	}
	_mem_servo;
	
	UartTransmit *_mem_uart;
	
public:
	
	Servo();
	Servo(ServoOldNumber _number);
	Servo(ServoNewNumber _number);
	
	void Reset(ServoOldNumber _number);
	void Reset(ServoNewNumber _number);
	
	void Set_uart(UartTransmit *_uart);
	void Set_angle_deg_new(ServoAngle _angle);
	void Set_angle_deg_old(ServoAngle _angle);
	
	ServoData Get();
	ServoAngle Get_angle_new();
	ServoAngle Get_angle_old();
	UartTransmit *Get_uart();

	void Transmit();
	void Transmit(UartTransmit &_uart);
};

/************************************************************************/

//----------------------------------------------------------------------//

inline ServoData Servo :: Get()
{
	return _mem_servo._data;
}

//----------------------------------------------------------------------//

inline ServoAngle Servo :: Get_angle_new()
{
	return _mem_servo._new._angle * 6;
}

//----------------------------------------------------------------------//

inline ServoAngle Servo :: Get_angle_old()
{
	return _mem_servo._old._angle * 1.5;
}

//----------------------------------------------------------------------//

inline UartTransmit * Servo ::Get_uart()
{
	return _mem_uart;
}

//----------------------------------------------------------------------//

/************************************************************************/
