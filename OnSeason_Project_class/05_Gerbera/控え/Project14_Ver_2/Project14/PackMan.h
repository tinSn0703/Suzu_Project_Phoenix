
#pragma once

/************************************************************************/

namespace Gerbera
{
namespace BanriFinal
{

/************************************************************************/

class PackMan
{
//variable
private:
	
	Motor _motor_pack_man_stand;
	
	MotorRotationOnly _motor_pack_man_arm[4];
	
	LimitSensor _limit_stand_over;
	LimitSensor _limit_stand_under;
	
	YesNo _is_stand_over  :1;
	YesNo _is_stand_under :1;
	
	LimitSensor _limit_arm_stretch[4];
	LimitSensor _limit_arm_shorten[4];
	
	DirectionY _direcion_stand :2;
	
//function
private:
	
	void Move_pack_man_arm_stretch();
	void Move_pack_man_arm_shorten();
	void Move_pack_man_arm_stop();
	
public:
	
	PackMan(const MotorNum _num, const UartNum _uart_num);
	
	void Clear();
	
	void Read();
	
	void Set_stand_over(YesNo _yes_no);
	void Set_stand_under(YesNo _yes_no);
	
	void Move_stand();
	
	void Move_pack_man_arm(DirectionY _move);
	
	void Move_pack_man_arm(YesNo _is_stretch, YesNo _is_shorten);
	
	void Write();
	
	void Write_clear();
	
	void Display_motor_stand(LcdAdrs _adrs);
	
	void Display_motor_arm(LcdAdrs _adrs, uByte _space = 0);
	
	void Display_sensor_stand(LcdAdrs _adrs, uByte _space = 0);
	
	void Display_sensor_arm_stretch(LcdAdrs _adrs, uByte _space = 0);
	void Display_sensor_arm_shorten(LcdAdrs _adrs, uByte _space = 0);
	
	void Display_sensor_num_stand_over(LcdAdrs _adrs);
	void Display_sensor_num_stand_under(LcdAdrs _adrs);	
	
	void Display_sensor_num_arm_stretch(LcdAdrs _adrs, uByte _space = 0);
	void Display_sensor_num_arm_shorten(LcdAdrs _adrs, uByte _space = 0);
	
}; //PackMan

/************************************************************************/

};
};

/************************************************************************/
