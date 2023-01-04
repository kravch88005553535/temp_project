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

void Gearbox::CalculateGear(uint32_t a_rpm, uint32_t a_speed)
{
	static double closest_gear_ratio = (a_rpm * m_circumference * 60) / (a_speed * 1000 * m_main_gear_ratio);
	m_gear = Gear_neutral; 
	//CALCULATE!!!
}

uint8_t Gearbox::GetGear()
{
	return m_gear;
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
		
		case Gear_main:
			m_main_gear_ratio = a_gear_ratio;
		break;
	}
}