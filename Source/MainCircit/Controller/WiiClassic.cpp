

#include <akilcd/akilcd.h>
#include <Others/Direc.h>
#include <AVR/AVR.h>
#include <MainCircit/Controller/WiiClassic.h>

/************************************************************************/

//----------------------------------------------------------------------//

WiiClassic :: WiiClassic (UartNum _arg_adrs_uart)

	: Controller(_arg_adrs_uart)
{}

//----------------------------------------------------------------------//

WiiClassic :: WiiClassic (UartNum _arg_adrs_uart, BOOL _arg_is_poss_rewrite)

	: Controller(_arg_adrs_uart, _arg_is_poss_rewrite)
{}

//----------------------------------------------------------------------//

/************************************************************************/
