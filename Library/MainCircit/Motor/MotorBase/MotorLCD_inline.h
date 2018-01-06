

#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline void MotorLCD :: Display_signal(const LcdAdrs _adrs)
{
	LCD::Write(_adrs, MotorGet::Get_sig(), 1, DECIMAL_10);
}

//----------------------------------------------------------------------//

inline void MotorLCD :: Display_pwm(LcdAdrs _adrs)
{
	LCD::Write(_adrs, MotorGet::Get_pwm(), 2, DECIMAL_10);
}

//----------------------------------------------------------------------//

inline void MotorLCD :: Display_steps(LcdAdrs _adrs)
{
	LCD::Write(_adrs, MotorGet::Is_steps_used(), 1, DECIMAL_02);
}

//----------------------------------------------------------------------//

inline void MotorLCD :: Display_data0(LcdAdrs _adrs)
{
	LCD::Write(_adrs, MotorGet::Get_data_0(), 9, DECIMAL_02);
}

//----------------------------------------------------------------------//

inline void MotorLCD :: Display_data1(LcdAdrs _adrs)
{
	LCD::Write(_adrs, MotorGet::Get_data_1(), 9, DECIMAL_02);
}

//----------------------------------------------------------------------//
