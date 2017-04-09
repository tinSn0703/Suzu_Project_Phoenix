
#pragma once

/************************************************************************/
//�Ίp

class OmuniDiagonal : public Wheel
{
public:
	
	OmuniDiagonal(MdcNum _mdc_num, UartNum _uart_num);
	
	void Drive();
	void Drive(DirecX _direc_x, DirecY _direc_y);
};

/************************************************************************/
//�Ε�

class OmuniOpposite : public Wheel
{
public:
	
	OmuniOpposite(MdcNum _mdc_num, UartNum _uart_num);
	
	void Drive();
	void Drive(DirecX _direc_x, DirecY _direc_y);
};

/************************************************************************/

#include "Omuni_inline.h"
