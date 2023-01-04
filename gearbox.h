#ifndef __GEARBOX_H__
#define __GEARBOX_H__

#include <stdint.h>

class Gearbox
{
public:	
	enum Gear
	{
		Gear_neutral,
		Gear_first,
		Gear_second,
		Gear_third,
		Gear_fourth,
		Gear_fifth,
		Gear_sixth,
		Gear_main
	};
	Gearbox();
	~Gearbox();
	void CalculateGear(uint32_t a_rpm, uint32_t a_speed);
	void CalculateCircumference();
	uint8_t GetGear();
	void SetGearRatio(Gear a_gear, double a_gear_ratio);
private:
	uint8_t m_gear;
	double m_main_gear_ratio;
	double m_first_gear_ratio;
	double m_second_gear_ratio;
	double m_third_gear_ratio;
	double m_fourth_gear_ratio;
	double m_fifth_gear_ratio;
	double m_sixth_gear_ratio;
	
	double m_circumference;
	uint8_t m_rim_diameter;
	uint8_t m_tire_height;
	uint16_t m_tire_width;
};

#endif //__GEARBOX_H__