
#pragma once

#include "ThreeOmuni.h"

/************************************************************************/
//‘ÎŠp

class OmuniDiagonal : public FourWheel
{
public:
	
	OmuniDiagonal(MotorNumber _min_number, UartNum _uart_num);
	
	void Move();
	void Move(double _rad);
	void Move(DirecX _direc_x, DirecY _direc_y);
	
	void Move_or_Turning();
};

/************************************************************************/
//‘Î•Ó

class OmuniOpposite : public FourWheel
{
public:
	
	OmuniOpposite(MotorNumber _min_number, UartNum _uart_num);
	
	void Move();
	void Move(double _rad);
	void Move(DirecX _direc_x, DirecY _direc_y);
	
	void Move_or_Turning();
};

/************************************************************************/

typedef OmuniDiagonal Mechanum;

/************************************************************************/

#include "Omuni_inline.h"
