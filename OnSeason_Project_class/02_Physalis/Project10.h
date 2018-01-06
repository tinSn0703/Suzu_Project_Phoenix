/************************************************************************/
/*	220 : ìÒçÜã@ñWäQ													*/
/************************************************************************/

namespace Physalis
{

namespace Otegine
{

/************************************************************************/

class Main
{
//variable
private:
	
	Controller::Bit24::Dualshock2AddPush _controller;
	
	FourWheel _wheel;
	
	Uart::ModeTransmit _uart_valve;
	
	ValveSingle _valve_rod;
	
	YesNo _is_movement_lock :1;
	
//function	
public:
	
	Main();
	
	void Input();
	
	void Process();
	
	void Output();
};

/************************************************************************/

}

}

/************************************************************************/