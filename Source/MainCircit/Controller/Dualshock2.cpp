

#include <akilcd/akilcd.h>
#include <Others/Direc.h>
#include <AVR/AVR.h>
#include <MainCircit/Controller/Dualshock2.h>

/************************************************************************/

//----------------------------------------------------------------------//

Dualshock2 :: Dualshock2 (UartNum _arg_adrs_uart)

	: Controller(_arg_adrs_uart)
{}

//----------------------------------------------------------------------//

Dualshock2 :: Dualshock2 (UartNum _arg_adrs_uart, BOOL _arg_is_poss_rewrite)

	: Controller(_arg_adrs_uart, _arg_is_poss_rewrite)
{}

//----------------------------------------------------------------------//

/************************************************************************/
