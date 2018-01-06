
#pragma once

/************************************************************************/

namespace ClassController
{

/************************************************************************/

class WiiClassicGet : public virtual ControllerGet
{
	Btn Get_X();
	Btn Get_B();
	Btn Get_A();
	Btn Get_Y();
	
	Btn Get_R();
	Btn Get_ZR();
	
	Btn Get_L();
	Btn Get_ZL();
	
	Btn Get_HOME();
};

/************************************************************************/

class WiiClassicPush : public virtual ControllerPush
{
	Btn Push_X();
	Btn Push_B();
	Btn Push_A();
	Btn Push_Y();
	
	Btn Push_R();
	Btn Push_ZR();
	
	Btn Push_L();
	Btn Push_ZL();
	
	Btn Push_HOME();
};

/************************************************************************/

#include "ControllerBase_inline/WiiClassicGet_inline.h"
#include "ControllerBase_inline/WiiClassicPush_inline.h"

/************************************************************************/

};

/************************************************************************/
