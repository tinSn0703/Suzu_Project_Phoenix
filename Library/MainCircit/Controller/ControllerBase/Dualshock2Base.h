
#pragma once

/************************************************************************/

namespace ClassController
{

/************************************************************************/

class Dualshock2Get : public virtual ControllerGet
{
public:
	
	Btn Get_Tri();
	Btn Get_Cro();
	Btn Get_Cir();
	Btn Get_Squ();
	
	Btn Get_R1();
	Btn Get_R2();
	Btn Get_R3();
	
	Btn Get_L1();
	Btn Get_L2();
	Btn Get_L3();
	
	Btn Get_START();
	Btn Get_SELECT();
};

/************************************************************************/

class Dualshock2Push : public virtual ControllerPush
{
public:
	
	Btn Push_Tri();
	Btn Push_Cro();
	Btn Push_Cir();
	Btn Push_Squ();
	
	Btn Push_R1();
	Btn Push_R2();
	Btn Push_R3();
	
	Btn Push_L1();
	Btn Push_L2();
	Btn Push_L3();
	
	Btn Push_START();
	Btn Push_SELECT();
};

/************************************************************************/

#include "ControllerBase_inline/Dualshock2Get_inline.h"
#include "ControllerBase_inline/Dualshock2Push_inline.h"

/************************************************************************/

}

/************************************************************************/
