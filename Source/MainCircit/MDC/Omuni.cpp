
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/AVR.h>
#include <MainCircit/Motor/Motor.h>
#include <MainCircit/MDC/MDC.h>
#include <MainCircit/MDC/Wheel.h>
#include <MainCircit/MDC/Omuni.h>

/************************************************************************/
/*	OmuniDiagonal														*/
/************************************************************************/

//----------------------------------------------------------------------//

OmuniDiagonal :: OmuniDiagonal(MdcNum _mdc_num, UartNum _uart_num)

	: Wheel(_mdc_num, _uart_num)
{}

//----------------------------------------------------------------------//

void OmuniDiagonal :: Drive()
{
	//2017 4/5
	//ちゃんと動くかわかってないのでチェックを忘れないでください
	
	const Byte _temp_x_front = (_is_invert_x ? Reversal_DirecX(_mem_direc_x) : _mem_direc_x);
	const Byte _temp_x_back	 = (_is_invert_x ? _mem_direc_x : Reversal_DirecX(_mem_direc_x));
	
	const Byte _temp_y_right = (_is_invert_y ? _mem_direc_y : Reversal_DirecY(_mem_direc_y));
	const Byte _temp_y_left	 = (_is_invert_y ? Reversal_DirecY(_mem_direc_y) : _mem_direc_y);
	
	_mem_md[FRONT_RIGHT] = Convert_to_Signal(_temp_x_front	& _temp_y_right);
	_mem_md[BACK_RIGHT]	 = Convert_to_Signal(_temp_x_back	& _temp_y_right);
	_mem_md[BACK_LEFT]	 = Convert_to_Signal(_temp_x_back	& _temp_y_left);
	_mem_md[FRONT_LEFT]	 = Convert_to_Signal(_temp_x_front	& _temp_y_left);
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	OmuniOpposite														*/
/************************************************************************/

//----------------------------------------------------------------------//

OmuniOpposite :: OmuniOpposite(MdcNum _mdc_num, UartNum _uart_num)

	: Wheel(_mdc_num, _uart_num)
{}

//----------------------------------------------------------------------//

void OmuniOpposite :: Drive()
{
	//2017 4/5
	//ちゃんと動くかわかってないのでチェックを忘れないでください
	
	_mem_md[FRONT_WHEEL] = Convert_to_Signal(_is_invert_x ? _mem_direc_x : Reversal_DirecX(_mem_direc_x));
	_mem_md[RIGHT_WHEEL] = Convert_to_Signal(_is_invert_y ? Reversal_DirecY(_mem_direc_y) : _mem_direc_y);
	_mem_md[BACK_WHEEL]  = Convert_to_Signal(_is_invert_x ? Reversal_DirecX(_mem_direc_x) : _mem_direc_x);
	_mem_md[LEFT_WHEEL]  = Convert_to_Signal(_is_invert_y ? _mem_direc_y : Reversal_DirecY(_mem_direc_y));
}

//----------------------------------------------------------------------//

/************************************************************************/
