/*
 * AirCylinder.cpp
 *
 * Created: 2018/01/03 22:21:34
 *  Author: FUJITSU
 */ 

#include <akilcd/akilcd.h>
#include <Others/BOOL.h>
#include <AVR/Timer/GeneralTimer.h>
#include <AVR/Uart/Uart.h>
#include <MainCircit/Valve/ValveSingle.h>
#include <MainCircit/Valve/ValveDouble.h>
#include <MainCircit/AirCylinder/AirCylinder.h>

SingleAirCylinder::SingleAirCylinder()
{
	
}

SingleAirCylinder::SingleAirCylinder(const ValveNum _num)

	: _valve(_num)
{
	
}

