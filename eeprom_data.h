#ifndef __EEPROM_DATA_H__
#define __EEPROM_DATA_H__

#include "speedometer.h"
#include "led_strip.h"

enum Eeprom_offsets
{
	///////////////// LED_STRIP
	eeprom_leds_num = 0,
	eeprom_brightness = eeprom_leds_num + sizeof(uint8_t), //LedStrip::m_leds_num
	eeprom_dimmer_brightness = eeprom_brightness + sizeof(uint8_t), //Led::m_brightness
	eeprom_animation	= eeprom_dimmer_brightness + sizeof(uint8_t), //Led::m_dimmer_brightness
	eeprom_segments_number = eeprom_animation + sizeof (LedStrip::Animation), //LedStrip::m_animation
	eeprom_shift_color_1	= eeprom_segments_number + sizeof (uint8_t), //LedStrip::m_segments_num
	eeprom_shift_color_2 = eeprom_shift_color_1 + sizeof (Color),
	eeprom_seg_1_color	= eeprom_shift_color_2 + sizeof (Color),
	eeprom_seg_2_color	= eeprom_seg_1_color + sizeof (Color),
	eeprom_seg_3_color = eeprom_seg_2_color + sizeof (Color),
	eeprom_seg_4_color = eeprom_seg_3_color + sizeof (Color),
	eeprom_seg_1_led_number = eeprom_seg_4_color + sizeof (Color),
	eeprom_seg_2_led_number = eeprom_seg_1_led_number + sizeof (uint8_t), //seg_1_led_number
	eeprom_seg_3_led_number = eeprom_seg_2_led_number + sizeof (uint8_t),	//seg_2_led_number
	eeprom_seg_4_led_number = eeprom_seg_3_led_number + sizeof (uint8_t), //seg_3_led_number

	///////////////// RPM_CALCULATION
	eeprom_cylinders_number = eeprom_seg_4_led_number + sizeof (uint8_t), //seg_4_led_number
	eeprom_tachometer_sensitivity_level	= eeprom_cylinders_number + sizeof(RPM::Cylinders),

	///////////////// SPEEDOMETER
	eeprom_speedometer_sensitivity_level = eeprom_tachometer_sensitivity_level + sizeof(uint8_t), //RPM::m_sensitivity_level
	eeprom_pulses_per_unit	= eeprom_speedometer_sensitivity_level + sizeof(uint8_t), //Speedometer::m_sensitivity_level
	eeprom_speedometer_units	= eeprom_pulses_per_unit + sizeof(Speedometer::PulsesPerUnit),

	///////////////// GEARBOX
	eeprom_main_gear_ratio = eeprom_speedometer_units + sizeof (Speedometer::Units),
	eeprom_first_gear_ratio	= eeprom_main_gear_ratio + sizeof(double), //Gearbox::m_main_gear_ratio
  eeprom_second_gear_ratio = eeprom_first_gear_ratio + sizeof(double), //Gearbox::m_gears[0]
	eeprom_third_gear_ratio = eeprom_second_gear_ratio + sizeof(double), //Gearbox::m_gears[1]
	eeprom_fourth_gear_ratio = eeprom_third_gear_ratio + sizeof(double), //Gearbox::m_gears[2]
	eeprom_fifth_gear_ratio = eeprom_fourth_gear_ratio + sizeof(double), //Gearbox::m_gears[3]
	eeprom_sixth_gear_ratio = eeprom_fifth_gear_ratio + sizeof(double), //Gearbox::m_gears[4]
	eeprom_seventh_gear_ratio = eeprom_sixth_gear_ratio + sizeof(double), //Gearbox::m_gears[5]
	eeprom_circumference = eeprom_seventh_gear_ratio + sizeof(double), //Gearbox::m_gears[6]
	eeprom_rim_diameter	= eeprom_circumference + sizeof(double), //Gearbox::m_circumference
	eeprom_tire_height = eeprom_rim_diameter + sizeof(uint8_t), //Gearbox::m_rim_diameter
	eeprom_tire_width = eeprom_tire_height + sizeof(uint8_t),	//Gearbox::m_tire_height
	
	///////////////// ODOMETER
	eeprom_odometer_value	= eeprom_tire_width + sizeof(uint16_t), //Gearbox::m_tire_width
	eeprom_actual_oil_change_interval = eeprom_odometer_value + sizeof (uint32_t), //Odometer::m_odometer_value
	eeprom_defined_oil_change_interval	= eeprom_actual_oil_change_interval + sizeof(uint32_t), //Odometer::m_actual_oil_change_interval
	//= defined_oil_change_interval + sizeof(uint32_t),	//Odometer::defined_oil_change_interval
	
	///////////////// DISPLAY
	//display_brightness
	//display dimmer_brightness
	///////////////// TECHNICAL DATA
	eeprom_crc = eeprom_defined_oil_change_interval + sizeof(uint32_t),	//Odometer::defined_oil_change_interval
};
#endif //__EEPROM_DATA_H__