
#pragma once

#include "Motor_type.h"

/************************************************************************/

namespace ClassMotor
{

/************************************************************************/

class MotorBase
{
protected:
	
	Motor	_mem_data;
	Pwm		_mem_pwm_adjustment :5;
	
	void Initialize(MotorNumber _num_md);
	
public:
	
	MotorBase();
	
	/*
	 *	モータの動作データを削除する。
	 */
	void Clear();
	
	/*
	 *	モータ番号を再設定する。
	 */
	void Reset(MotorNumber _md_num);
};

/************************************************************************/

class MotorGet : public MotorBase
{
public:
	
	MotorGet();
	
	MotorNumber	Get_number();
	
	Signal	Get_sig();
	Pwm		Get_pwm();
	
	MotorData Get_data_0();
	MotorData Get_data_1();
	
	BOOL Is_steps_used();
};

/************************************************************************/

class MotorOperate : public virtual MotorGet
{
public:
	
	MotorOperate();
	
	void Set_direct(Pwm _pwm);
	
	void Set(Pwm _pwm);
	void Set(Signal _sig);
	void Set(Signal _sig, Pwm _pwm);
	
	void Set_from_pwm(Pwm _pwm, YesNo _is_reverse = NO);
	
	/*
	 *	PWMをP制御する。
	 *
	 *	_target_value	: 目標値
	 *	_current_value	: 現在値
	 *	_p_constant		: 定数
	 *	_is_reverse		: モータの回転方向を反転させるかどうか
	 */
	void Control_P(int _target_value, int _current_value, double _p_constant, YesNo _is_reverse = NO);
	
	void Adjust_for(Pwm _adjustment_value);
	
	void Want_to_use_steps(YesNo _yes_no);
	
	void operator ++ (int );
	void operator -- (int );
};

/************************************************************************/

class MotorLCD : public virtual MotorGet
{
public:
	
	MotorLCD();
	
	void Display_signal	(LcdAdrs _adrs);
	void Display_pwm	(LcdAdrs _adrs);
	void Display_steps	(LcdAdrs _adrs);
	
	void Display_data0 (LcdAdrs _adrs);
	void Display_data1 (LcdAdrs _adrs);
};

/************************************************************************/

#include "MotorBase_inline.h"
#include "MotorLCD_inline.h"

/************************************************************************/

}

/************************************************************************/
