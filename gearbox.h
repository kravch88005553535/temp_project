#ifndef __GEARBOX_H__
#define __GEARBOX_H__

#include <stdint.h>

class Gearbox
{
public:	
	enum Gear
	{
		Gear_first,
		Gear_second,
		Gear_third,
		Gear_fourth,
		Gear_fifth,
		Gear_sixth,
		Gear_seventh,
		Gear_neutral,
		Gear_main
	};
	Gearbox();
	~Gearbox();
	void SetGearRatio(Gear a_gear, double a_gear_ratio);
	void SetRimDiameter(uint8_t a_rim_diaameter);
	void SetTireHeight(uint8_t a_tire_height);
	void SetTireWidth(uint16_t a_tire_width);
	void CalculateCircumference();
	void CalculateGear(uint32_t a_rpm, uint32_t a_speed);
	uint8_t GetActiveGear();
	
private:
	Gear m_active_gear;
	double m_main_gear_ratio;
	double m_gears[7];
//	double m_first_gear_ratio;
//	double m_second_gear_ratio;
//	double m_third_gear_ratio;
//	double m_fourth_gear_ratio;
//	double m_fifth_gear_ratio;
//	double m_sixth_gear_ratio;
//	double m_seventh_gear_ratio;
//	
	double m_circumference;
	uint8_t m_rim_diameter;
	uint8_t m_tire_height;
	uint16_t m_tire_width;
};

#endif //__GEARBOX_H__