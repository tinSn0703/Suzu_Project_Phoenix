

#pragma once

#include "MotorData/MotorData.h"

/************************************************************************/

#ifdef __cplusplus

/************************************************************************/

namespace ClassMotor
{

/************************************************************************/

class MotorBase
{
protected:
	
	Motor	_mem_data;
	sint	_mem_pwm_adjustment :5;
	
	void Initialize  (MdcNum _num_mdc, MdNum _num_md);
	
public:
	
	MotorBase ();
	
	void Clear ();
	
	void Reset(MdNum _md_num);
	void Reset(MdcNum _mdc_num);	
	void Reset(MdcNum _num_mdc, MdNum _num_md);
};

/************************************************************************/

class MotorGet : public MotorBase
{
public:
	
	MotorGet();
	
	MdNum Get_md_num();
	MdcNum Get_mdc_num();
	
	Signal	Get_sig ();
	Pwm		Get_pwm ();
	
	DataMotor Get_data_0 ();
	DataMotor Get_data_1 ();
	
	BOOL Is_steps_used ();
};

/************************************************************************/

class MotorOperate : public virtual MotorGet
{
public:
	
	MotorOperate();
	
	void Set(Signal _sig);
	void Set(Pwm _pwm);	
	void Set(Signal _sig, Pwm _pwm, BOOL _is_steps_on);
	
	void Set_pwm_P(int _target_value, int _current_value, double _p_constant, YesNo _is_reverse = NO);
	
	void Adjust_for(Pwm _adjustment_value);
	
	void Set_direct(Signal _sig);
	void Set_direct(Pwm _pwm);
	void Set_direct(Signal _sig, Pwm _pwm, BOOL _is_steps_on);
	
	void Want_to_use_steps (YesNo _yes_no);
	
	void operator ++ (int );
	void operator -- (int );
};

/************************************************************************/

class MotorLCD : public virtual MotorGet
{
public:
	
	MotorLCD();
	
	void LCD_signal	(LcdAdrs _adrs);
	void LCD_pwm	(LcdAdrs _adrs);
	void LCD_steps	(LcdAdrs _adrs);
	
	void LCD_data0 (LcdAdrs _adrs);
	void LCD_data1 (LcdAdrs _adrs);
};

/************************************************************************/

}

/************************************************************************/

#include "MotorBase_inline.h"
#include "MotorLCD_inline.h"

#endif //__cplusplus
