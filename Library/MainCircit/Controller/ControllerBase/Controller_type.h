
#pragma once

/************************************************************************/

#define NUM_CONTROLLER_28BIT 6
#define NUM_CONTROLLER_24BIT 4
#define NUM_CONTROLLER_DATA 3

/************************************************************************/

typedef uByte ControllerData;

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
	BTN_R	= 7,
	BTN_ZR	= 5,
	
	BTN_L	= 6,
	BTN_ZL	= 4,
	
	BTN_HOME = 1,	//other_0
	
	BTN_X	= 8,
	BTN_A	= 9,
	BTN_B	= 10,
	BTN_Y	= 11,
	
	BTN_SELECT	= 0,
	BTN_R3		= 2,	//other_1
	BTN_L3		= 1,	//other_0
	BTN_START	= 3,
	
	BTN_L2	= 4,
	BTN_R2	= 5,
	BTN_L1	= 6,
	BTN_R1	= 7,
	
	BTN_TRI	= 8,
	BTN_CIR	= 9,
	BTN_CRO	= 10,
	BTN_SQU	= 11,
}
ControllerBtn;

//----------------------------------------------------------------------//

/************************************************************************/

namespace ClassController
{

/************************************************************************/

union Controller
{
	struct PartsController
	{		
		//[0]
		Btn _btn_select		:1; //7bit
		Btn _btn_other_0	:1; //4bit
		Btn _btn_other_1	:1; //5bit
		Btn _btn_start		:1; //6bit
		Btn _btn_left_1		:1; //3bit
		Btn _btn_right_1	:1; //1bit
		Btn _btn_left_0		:1; //2bit
		Btn _btn_right_0	:1; //0bit
		
		//[1]		
		Btn	_btn_mark_o	:1; //上 0bit
		Btn	_btn_mark_r	:1; //右 1bit
		Btn _btn_mark_u	:1; //下 2bit
		Btn	_btn_mark_l	:1; //左 3bit
		
		DirecX _cross_x :2; //十字キー x軸 4,5bit
		DirecY _cross_y :2; //十字キー y軸 6,7bit
		
		//[2]
		DirecX _stick_right_x	:2; //右スティック x方向 0,1bit
		DirecY _stick_right_y	:2; //右スティック y方向 2,3bit
		DirecX _stick_left_x	:2; //左スティック x方向 4,5bit
		DirecY _stick_left_y	:2; //左スティック y方向 6,7bit
	}
	_sub;
	
	struct ClusterController
	{
		uByte _other_btns		:4;
		uByte _right_left_btns	:4;
		uByte _mark_btns		:4;
	}
	_cluster;
	
	ControllerData _array[NUM_CONTROLLER_DATA];
	
	ullint _all :24;
};

/************************************************************************/

};

/************************************************************************/

