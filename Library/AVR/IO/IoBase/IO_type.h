
#pragma once

/************************************************************************/

typedef uByte IoData;

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

#define IO_BIT_0 0
#define IO_BIT_1 1
#define IO_BIT_2 2
#define IO_BIT_3 3
#define IO_BIT_4 4
#define IO_BIT_5 5
#define IO_BIT_6 6
#define IO_BIT_7 7
 
typedef Byte IoBit;

//----------------------------------------------------------------------//

/************************************************************************/

#ifdef __cplusplus	//C++‚ÌŽž—p

namespace ClassIO	{

#endif /*__cplusplus*/

typedef uByte (*fpReadPIN)();
typedef uByte (*fpReadPORT)();
typedef void (*fpWritePORT)(uByte );

#ifdef __cplusplus	//C++‚ÌŽž—p

	};

#endif /*__cplusplus*/
