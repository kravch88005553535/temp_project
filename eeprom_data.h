#ifndef __EEPROM_DATA_H__
#define __EEPROM_DATA_H__

#include "speedometer.h"
#include "led_strip.h"

enum Eeprom_offsets
{
	led_num_offset = 0,
	animation_offset = led_num_offset + sizeof(uint8_t),
	shift_color_1_offset = animation_offset + sizeof (int),//(LedStrip::Animation),
	shift_color_2_offset = shift_color_1_offset + 3 * sizeof(uint8_t),
	shift_color_3_offset = shift_color_2_offset + 3 * sizeof(uint8_t),
	number_of_led_1_offset = shift_color_3_offset + 3 * sizeof(uint8_t),
	number_of_led_2_offset = number_of_led_1_offset + sizeof (uint8_t),
	number_of_led_3_offset = number_of_led_2_offset + sizeof (uint8_t),
	blink_color_1_offset = number_of_led_3_offset + sizeof (uint8_t),
	sd	
	
};

class Eeprom_data
{
public:
  Eeprom_data(){};
  ~Eeprom_data(){};
  void CalculateCRC();
private:   
  uint8_t led_num;
  LedStrip::Animation animation;
  Color shift_color_1;
  Color shift_color_2;
  Color shift_color_3;
  uint8_t number_of_led_1;
  uint8_t number_of_led_2;
  uint8_t number_of_led_3;
  Color blink_color_1;
  Color blink_color_2;
  uint8_t led_brightness;
  bool is_led_dimmer_enabled;

  uint8_t display_brightness;
  uint8_t display_dimmer_mode;
  
  uint8_t cylinders_number;
  uint16_t min_rpm;

  uint16_t m_pulses_per_unit;
  Speedometer::Units m_units;
  uint32_t odometer_value;
  uint32_t actual_oil_change_interval;
  uint32_t defined_oil_change_interval;

  bool iswriteneeded;
  uint32_t crc;
};

#endif //__EEPROM_DATA_H__