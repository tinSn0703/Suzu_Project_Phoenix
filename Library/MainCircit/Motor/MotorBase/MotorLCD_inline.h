

#pragma once

namespace ClassMotor
{

/************************************************************************/
/*	MotorDisplay														*/
/************************************************************************/
inline void MotorLCD :: LCD_signal (const LcdAdrs _arg_adrs)
{
	LCD_Write_num(_arg_adrs, MotorGet :: Get_sig(), 1, DECIMAL_10);
}

//----------------------------------------------------------------------//

inline void MotorLCD :: LCD_pwm (LcdAdrs _arg_adrs)
{
	LCD_Write_num(_arg_adrs, MotorGet :: Get_pwm(), 2, DECIMAL_10);
}

//----------------------------------------------------------------------//

inline void MotorLCD :: LCD_steps (LcdAdrs _arg_adrs)
{
	LCD_Write_num(_arg_adrs, MotorGet :: Is_steps_used(), 1, DECIMAL_02);
}

//----------------------------------------------------------------------//

inline void MotorLCD :: LCD_data0 (LcdAdrs _arg_adrs)
{
	LCD_Write_num(_arg_adrs, MotorGet :: Get_data_0(), 9, DECIMAL_02);
}

//----------------------------------------------------------------------//

inline void MotorLCD :: LCD_data1 (LcdAdrs _arg_adrs)
{
	LCD_Write_num(_arg_adrs, MotorGet :: Get_data_1(), 9, DECIMAL_02);
}

//----------------------------------------------------------------------//

};