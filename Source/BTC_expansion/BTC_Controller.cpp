
#include <akilcd/akilcd.h>
#include <BTC/BTC.h>
#include <MainCircit/Direction.h>
#include <MainCircit/Controller/ControllerBase/ControllerBase.h>
#include <MainCircit/Controller/ControllerBase/Dualshock2Base.h>
#include <MainCircit/Controller/ControllerBase/WiiClassicBase.h>
#include <BTC_expansion/BTC_Receive.h>
#include <BTC_expansion/BTC_Controller.h>

/************************************************************************/

namespace Bluetooth
{

namespace Bit24
{

/************************************************************************/

//----------------------------------------------------------------------//

Controller :: Controller(const UartNum _num_bt_uart, const BOOL _is_data_rewrite)
	
	: ControllerRewrite(_is_data_rewrite)
{
	ReceiveCircit::Initialize();
	
	ReceiveCircit::Connect();
}

//----------------------------------------------------------------------//

void Controller :: Allot()
{
	_mem_data._command._cross_x = To_DirectionX
	(
		(Is_true_the(Get_read_data(1), 1) << 1) | 
		(Is_true_the(Get_read_data(0), 5) << 0)
	);
	
	_mem_data._command._cross_y = To_DirectionY
	(
		(Is_true_the(Get_read_data(0), 4) << 1) | 
		(Is_true_the(Get_read_data(1), 0) << 0)
	);
	
	_mem_data._command._stick_left_x = To_DirectionX(Get_read_data(3) >> 2);
	_mem_data._command._stick_left_y = To_DirectionY(Get_read_data(3) >> 4);
	
	_mem_data._command._stick_right_x = To_DirectionX(Get_read_data(2) >> 4);
	_mem_data._command._stick_right_y = To_DirectionY(Get_read_data(3) >> 0);
	
	_mem_data._btns._other = ((~Get_read_data(0)) & 0x0f);
	
	_mem_data._btns._right_left = (((~Get_read_data(1)) >> 2) & 0x0f);
	
	_mem_data._btns._mark = ((~Get_read_data(2)) & 0x0f);
}

//----------------------------------------------------------------------//

void Controller :: Read()
{
	ReceiveCircit::Receive();
	
	Allot();
}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

Dualshock2 :: Dualshock2(const UartNum _uart_num, const YesNo _is_data_rewrite)

	: Controller(_uart_num, _is_data_rewrite)
{}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

Dualshock2AddPush :: Dualshock2AddPush(const UartNum _uart_num, const YesNo _is_data_rewrite)

	: Controller(_uart_num, _is_data_rewrite)
{}

//----------------------------------------------------------------------//

void Dualshock2AddPush :: Read()
{
	Stock();
	
	Controller::Read();
	
	Set_btn_data();
}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

WiiClassic :: WiiClassic(const UartNum _uart_num, const BOOL _is_poss_rewrite)

	: Controller(_uart_num, _is_poss_rewrite)
{}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

WiiClassicAddPush :: WiiClassicAddPush(const UartNum _uart_num, const BOOL _is_poss_rewrite)

	: Controller(_uart_num, _is_poss_rewrite)
{}

//----------------------------------------------------------------------//

void WiiClassicAddPush :: Read()
{
	Stock();
	
	Controller::Read();
	
	Set_btn_data();
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

/************************************************************************/
