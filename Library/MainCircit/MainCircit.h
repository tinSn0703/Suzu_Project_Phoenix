/*
 * MainCircit.h
 *
 * Created: 2017/02/25 14:32:54
 *  Author: Suzu
 */ 

#pragma once

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/AVR.h>

#include "Motor/Motor.h"

#include "MDC/MDC.h"
#include "MDC/Wheel.h"
#include "MDC/Omuni.h"

#include "Valve/Valve.h"

#include "Controller/Controller.h"
#include "Controller/Dualshock2.h"
#include "Controller/WiiClassic.h"

typedef IoInBit Sensor;
typedef Sensor LimitSensor;
typedef Sensor PhotoSensor;

typedef IoOutBit LED;
typedef LED Vacuum;
