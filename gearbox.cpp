#include "gearbox.h"

Gearbox::Gearbox()
	: m_first_gear_ratio 	{0}
	, m_second_gear_ratio {0}
	, m_third_gear_ratio 	{0}
	, m_fourth_gear_ratio {0}
	, m_fifth_gear_ratio 	{0}
	, m_sixth_gear_ratio 	{0}
	, m_gear 							{0}
	, m_circumference			{0}
	, m_rim_diameter		  {0}
	, m_tire_height				{0}
	, m_tire_width				{0}
{
}

Gearbox::~Gearbox()
{
}

void Gearbox::SetGearRatio(Gear a_gear, double a_gear_ratio)
{
	switch (static_cast<uint32_t>(a_gear))
	{
		case Gear_neutral:
		break;
		
		case Gear_first:
			m_first_gear_ratio = a_gear_ratio;
		break;
		
		case Gear_second:
			m_second_gear_ratio = a_gear_ratio;
		break;
		
		case Gear_third:
			m_third_gear_ratio = a_gear_ratio;
		break;
		
		case Gear_fourth:
			m_fourth_gear_ratio = a_gear_ratio;
		break;
		
		case Gear_fifth:
			m_fifth_gear_ratio = a_gear_ratio;
		break;
		
		case Gear_sixth:
			m_sixth_gear_ratio = a_gear_ratio;
		break;
		
		case Gear_seventh:
			m_seventh_gear_ratio = a_gear_ratio;
		break;
		
		case Gear_main:
			m_main_gear_ratio = a_gear_ratio;
		break;
	}
}

void Gearbox::SetRimDiameter(uint8_t a_rim_diaameter)
{
	m_rim_diameter = a_rim_diaameter;
}

void Gearbox::SetTireHeight(uint8_t a_tire_height)
{
	m_tire_height = a_tire_height;
}

void Gearbox::SetTireWidth(uint16_t a_tire_width)
{
	m_tire_width = a_tire_width;
}

void Gearbox::CalculateCircumference()
{
	static const double inches_to_cm {2.54};
	static const double double_pi{6.28};
	static const int cm_to_meters{100};
	static double rim_radius{static_cast<double>(m_rim_diameter / 2)};
	
	m_circumference = static_cast<double>
		((double(m_tire_width * m_tire_height) / 1000 
			+ inches_to_cm * rim_radius)*double_pi / cm_to_meters);
}

void Gearbox::CalculateGear(uint32_t a_rpm, uint32_t a_speed)
{
	static double closest_gear_ratio = (a_rpm * m_circumference * 60) / (a_speed * 1000 * m_main_gear_ratio);
	if (!a_speed || !a_rpm)
		{
			m_gear = Gear_neutral; 
			return;
		}
	else
		{
			static double delta = 0;
			return;
		}
}

uint8_t Gearbox::GetGear()
{
	return m_gear;
}
