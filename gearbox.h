#ifndef __GEARBOX_H__
#define __GEARBOX_H__

#include <stdint.h>

class Gearbox
{
	public:
		Gearbox();
		~Gearbox();
		void CalculateGear(uint32_t a_rpm, uint32_t a_speed);
	private:
	double m_main_gear_ratio;
	double m_first_gear_ratio;
	double m_second_gear_ratio;
	double m_third_gear_ratio;
	double m_fourth_gear_ratio;
	double m_fifth_gear_ratio;
	double m_sixth_gear_ratio;
};

#endif //__GEARBOX_H__