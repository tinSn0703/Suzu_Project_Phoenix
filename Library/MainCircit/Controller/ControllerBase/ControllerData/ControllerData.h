
#pragma once

/************************************************************************/

#define _NUM_CONTROLLER_UART_DATA_ 4
#define _NUM_CONTROLLER_DATA_ 3

/************************************************************************/

typedef Byte ControllerData;

typedef BOOL Btn;

/************************************************************************/

//----------------------------------------------------------------------//

typedef enum
{
	STI_RIGHT_X	= 0x00,
	STI_LEFT_X	= 0x04,
	BTN_CROSS_X = 0x08,
}
ControllerDirecX;

//----------------------------------------------------------------------//

typedef enum
{
	STI_RIGHT_Y	= 0x02,
	STI_LEFT_Y	= 0x06,	
	BTN_CROSS_Y = 0x0a,
}
ControllerDirecY;

//----------------------------------------------------------------------//

typedef enum
{
	BTN_X	= 0x0c,
	BTN_A	= 0x0d,
	BTN_Y	= 0x0e,
	BTN_B	= 0x0f,
	
	BTN_R	= 0x10,
	BTN_ZR	= 0x11,
	
	BTN_L	= 0x12,
	BTN_ZL	= 0x13,
	
	BTN_TRI	= 0x0c,
	BTN_CIR	= 0x0d,
	BTN_SQU	= 0x0e,
	BTN_CRO	= 0x0f,

	BTN_R1	= 0x10,
	BTN_R2	= 0x11,
	BTN_R3	= 0x15,

	BTN_L1	= 0x12,
	BTN_L2	= 0x13,
	BTN_L3	= 0x14,
	
	BTN_HOME	= 0x14,
	BTN_START	= 0x16,
	BTN_SELECT	= 0x17,
}
ControllerBtn;

//----------------------------------------------------------------------//

/************************************************************************/

#ifdef __cplusplus

namespace ClassController {

#endif	/*__cplusplus*/

/************************************************************************/

typedef union 
{
	struct StructController
	{
		//[0]
		DirecX _stick_right_x	:2; //右スティック x方向 0,1bit
		DirecY _stick_right_y	:2; //右スティック y方向 2,3bit
		DirecX _stick_left_x	:2; //左スティック x方向 4,5bit
		DirecY _stick_left_y	:2; //左スティック y方向 6,7bit
		
		//[1]
		DirecX _btn_cross_x :2; //十字キー x軸 0,1bit
		DirecY _btn_cross_y :2; //十字キー y軸 2,3bit
		
		Btn	_btn_north	:1; //上 4bit
		Btn	_btn_east	:1; //右 5bit
		Btn	_btn_west	:1; //左 6bit
		Btn _btn_south	:1; //下 7bit
		
		//[2]
		Btn _btn_right_0	:1; //0bit
		Btn _btn_right_1	:1; //1bit
		Btn _btn_left_0		:1; //2bit
		Btn _btn_left_1		:1; //3bit
		Btn _btn_other_0	:1; //4bit
		Btn _btn_other_1	:1; //5bit
		Btn _btn_start		:1; //6bit
		Btn _btn_select		:1; //7bit
	}
	_sub;
	
	ControllerData _arr_all[_NUM_CONTROLLER_DATA_];
	
	ullint _all :24;
}
Controller;

/************************************************************************/

#ifdef __cplusplus

	};

#endif	/*__cplusplus*/

/************************************************************************/

