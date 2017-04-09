
#pragma once

#include <avr/io.h>
#include <util/delay.h>

#if		defined(_LCD_ADC_)
#	include "akilcd_ADchangeCircit.h"
#elif	defined(_LCD_BLUEMASTER_)
#	include "akilcd_BlueMaster_Send.h"
#elif	defined(_LCD_CIC_)
#	include "akilcd_CiCircit.h"
#elif	defined(_LCD_MAINC_)
#	include "akilcd_MainCircit.h"
#elif	defined(_LCD_NMAINC_)
#	include "akilcd_NewMainCircit.h"
#elif	defined(_LCD_ROBOBA005_)
#	include "akilcd_ROBOBA005_Send.h"
#else
#	include "akilcd_NewMainCircit.h"
#endif

#include <Akiduki_LCD/akilcd.h>

