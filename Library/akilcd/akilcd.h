
#pragma once

/************************************************************************/

#include <avr/io.h>
#include <util/delay.h>

/************************************************************************/

typedef unsigned short int Digit;
typedef unsigned char LcdAdrs;

/************************************************************************/

typedef enum
{
	DECIMAL_02 = 2,
	DECIMAL_08 = 8,
	DECIMAL_10 = 10,
	DECIMAL_16 = 16,
}
Decimal;

/************************************************************************/

#define ED_02	DECIMAL_02
#define ED_08	DECIMAL_08
#define ED_10	DECIMAL_10
#define ED_16	DECIMAL_16

#define LCD_SEMI_CLEAR	"                "

/************************************************************************/

#include "akilcd_name/akilcd_name_ver0.h"
#include "akilcd_name/akilcd_name_ver1.h"
#include "akilcd_name/akilcd_name_ver2.h"
#include "akilcd_name/akilcd_name_ver3.h"
#include "akilcd_name/akilcd_name_ver4.h"

/************************************************************************/
