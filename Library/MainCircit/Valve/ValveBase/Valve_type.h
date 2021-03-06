
#pragma once

/************************************************************************/

typedef uByte ValveData;

/************************************************************************/

typedef enum
{
	NUM_VALVE_0 = 0,
	NUM_VALVE_1 = 1,
	NUM_VALVE_2 = 2,
	NUM_VALVE_3 = 3,
	NUM_VALVE_4 = 4,
	NUM_VALVE_5 = 5,
	NUM_VALVE_6 = 6,
	NUM_VALVE_7 = 7,
}
ValveNum;

/************************************************************************/

namespace ClassValve
{

/************************************************************************/

typedef union
{
	struct InUnionValveData
	{
		BOOL _0 :1;
		BOOL _1 :1;
		BOOL _2 :1;
		BOOL _3 :1;
		BOOL _4 :1;
		BOOL _5 :1;
		BOOL _6 :1;
		BOOL _7 :1;
	}
	_bit;
	
	ValveData _all :8;
}
Valve;

/************************************************************************/

};

/************************************************************************/
