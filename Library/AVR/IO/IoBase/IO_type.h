
#pragma once

/************************************************************************/

typedef Byte IoData;

/************************************************************************/

//----------------------------------------------------------------------//

typedef enum
{
	IO_ADRS_A = 0,
	IO_ADRS_B = 1,
	IO_ADRS_C = 2,
	IO_ADRS_D = 3,
	IO_ADRS_E = 4,
	IO_ADRS_F = 5,
	IO_ADRS_G = 6,
	IO_ADRS_H = 7,
	IO_ADRS_J = 8,
	IO_ADRS_K = 9,
}
IoAdrs;

//----------------------------------------------------------------------//

typedef enum
{
	IO_BIT_0 = 0,
	IO_BIT_1 = 1,
	IO_BIT_2 = 2,
	IO_BIT_3 = 3,
	IO_BIT_4 = 4,
	IO_BIT_5 = 5,
	IO_BIT_6 = 6,
	IO_BIT_7 = 7
}
IoBit;

//----------------------------------------------------------------------//

/************************************************************************/

typedef Byte (*fpReadPIN)();
typedef Byte (*fpReadPORT)();
typedef void (*fpWritePORT)(Byte );