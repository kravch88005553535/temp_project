#ifndef __EEPROM_DATA_H__
#define __EEPROM_DATA_H__

#include "speedometer.h"
#include "led_strip.h"

class Eeprom_data
{
public:
  Eeprom_data(){};
  ~Eeprom_data(){};
  void CalculateCRC();
private:
  uint8_t writing_number;
  uint8_t data_size;
  uint32_t crc;
//  iswriteneeded
   
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
};

#endif //__EEPROM_DATA_H__