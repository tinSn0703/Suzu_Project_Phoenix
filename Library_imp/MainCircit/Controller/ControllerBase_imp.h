
#pragma once

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

#include <akilcd/akilcd.h>
#include <Others/Direc.h>
#include <MainCircit/Controller/ControllerBase/ControllerBase.h>

/************************************************************************/

namespace ClassController
{

/************************************************************************/
/*	ControllerBase														*/
/************************************************************************/

//----------------------------------------------------------------------//

void ControllerBase :: Combine (const Byte _data[_NUM_CONTROLLER_UART_DATA_])
{
	_mem_data._sub._btn_cross_x	= Convert_to_DirecX((Is_true_the(_data[1], 1) << 1) | Is_true_the(_data[0], 5));
	_mem_data._sub._btn_cross_y	= Convert_to_DirecY((Is_true_the(_data[0], 4) << 1) | Is_true_the(_data[1], 0));
	
	_mem_data._sub._stick_left_x	= Convert_to_DirecX(_data[3] >> 2);
	_mem_data._sub._stick_left_y	= Convert_to_DirecY(_data[3] >> 4);
	
	_mem_data._sub._stick_right_x	= Convert_to_DirecX(_data[2] >> 4);
	_mem_data._sub._stick_right_y	= Convert_to_DirecY(_data[3] >> 0);
	
	_mem_data._sub._btn_start	= Is_false_the(_data[0], 3);
	_mem_data._sub._btn_select	= Is_false_the(_data[0], 0);
	_mem_data._sub._btn_other_0 = Is_false_the(_data[0], 1);
	_mem_data._sub._btn_other_1 = Is_false_the(_data[0], 2);
	
	_mem_data._sub._btn_right_0	= Is_false_the(_data[1], 5);
	_mem_data._sub._btn_right_1	= Is_false_the(_data[1], 3);
	
	_mem_data._sub._btn_left_0	= Is_false_the(_data[1], 4);
	_mem_data._sub._btn_left_1	= Is_false_the(_data[1], 2);
	
	_mem_data._sub._btn_west	= Is_false_the(_data[2], 3);
	_mem_data._sub._btn_south	= Is_false_the(_data[2], 2);
	_mem_data._sub._btn_east	= Is_false_the(_data[2], 1);
	_mem_data._sub._btn_north	= Is_false_the(_data[2], 0);
}

//----------------------------------------------------------------------//

void ControllerBase :: Clear()
{
	_mem_data._arr_all[0] = 0xff;
	_mem_data._arr_all[1] = 0x0f;
	_mem_data._arr_all[2] = 0x00;
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	ControllerRewrite													*/
/************************************************************************/

//----------------------------------------------------------------------//

ControllerRewrite :: ControllerRewrite (BOOL _arg_is_poss_rewrite)
{
	_mem_is_rewritten = _arg_is_poss_rewrite;
}

//----------------------------------------------------------------------//

void ControllerRewrite :: Rewrite_base(usint _arg_bit, int _arg_data, int _arg_and)
{
	_mem_data._all &= ~(_arg_and  << _arg_bit);
	_mem_data._all |=  (_arg_data << _arg_bit);
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/

#endif	//__cplusplus

/************************************************************************/

