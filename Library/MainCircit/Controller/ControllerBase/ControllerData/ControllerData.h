
#pragma once

/************************************************************************/

#define _NUM_CONTROLLER_UART_DATA_ 4
#define _NUM_CONTROLLER_DATA_ 3

/************************************************************************/

typedef Byte ControllerData;

typedef BOOL Btn;

#define BTN_ON	TRUE
#define BTN_OFF	FALSE

/************************************************************************/

//----------------------------------------------------------------------//

typedef enum
{
	STI_RIGHT_X	= 16,
	STI_LEFT_X	= 20,
	BTN_CROSS_X = 12,
}
ControllerDirecX;

//----------------------------------------------------------------------//

typedef enum
{
	STI_RIGHT_Y	= 18,
	STI_LEFT_Y	= 22,	
	BTN_CROSS_Y = 14,
}
ControllerDirecY;

//----------------------------------------------------------------------//

typedef enum
{	
	BTN_R	= 0,
	BTN_ZR	= 1,
	
	BTN_L	= 2,
	BTN_ZL	= 3,
	
	BTN_HOME = 4,
	
	BTN_X	= 8,
	BTN_A	= 9,
	BTN_Y	= 10,
	BTN_B	= 11,
	
	BTN_R1	= 0,
	BTN_R2	= 1,
	BTN_R3	= 5,

	BTN_L1	= 2,
	BTN_L2	= 3,
	BTN_L3	= 4,
	
	BTN_TRI	= 8,
	BTN_CIR	= 9,
	BTN_SQU	= 10,
	BTN_CRO	= 11,
	
	BTN_START	= 6,
	BTN_SELECT	= 7,
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
		Btn _btn_right_0	:1; //0bit
		Btn _btn_right_1	:1; //1bit
		Btn _btn_left_0		:1; //2bit
		Btn _btn_left_1		:1; //3bit
		Btn _btn_other_0	:1; //4bit
		Btn _btn_other_1	:1; //5bit
		Btn _btn_start		:1; //6bit
		Btn _btn_select		:1; //7bit
		
		//[1]		
		Btn	_btn_north	:1; //上 0bit
		Btn	_btn_east	:1; //右 1bit
		Btn	_btn_west	:1; //左 2bit
		Btn _btn_south	:1; //下 3bit
		
		DirecX _btn_cross_x :2; //十字キー x軸 4,5bit
		DirecY _btn_cross_y :2; //十字キー y軸 6,7bit
		
		//[2]
		DirecX _stick_right_x	:2; //右スティック x方向 0,1bit
		DirecY _stick_right_y	:2; //右スティック y方向 2,3bit
		DirecX _stick_left_x	:2; //左スティック x方向 4,5bit
		DirecY _stick_left_y	:2; //左スティック y方向 6,7bit
	}
	_sub;
	
	ControllerData _array[_NUM_CONTROLLER_DATA_];
	
	ullint _all :24;
}
Controller;

/************************************************************************/

#ifdef __cplusplus

	};

#endif	/*__cplusplus*/

/************************************************************************/

