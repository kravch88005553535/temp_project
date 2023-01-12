#ifndef __TM1637_H__
#define __TM1637_H__
#include "i2c.h"


class TM_1637
{
public:
	enum Brightness : int
	{
		Brightness_display_off = 0,
		Brightness_1 = 1,
		Brightness_2 = 2,
		Brightness_3 = 3,
		Brightness_4 = 4,
		Brightness_5 = 5,
		Brightness_6 = 6,
		Brightness_7 = 7,
		Brightness_8 = 8,
		Brightness_display_full = 9
	};
	
	enum Digittosegment
	{
		Digittosegment_0 = 0b00111111,
		Digittosegment_1 = 0b00000110,
		Digittosegment_2 = 0b01011011,
		Digittosegment_3 = 0b01001111,
		Digittosegment_4 = 0b01100110,
		Digittosegment_5 = 0b01101101,
		Digittosegment_6 = 0b01111101,
		Digittosegment_7 = 0b00000111,
		Digittosegment_8 = 0b01111111,
		Digittosegment_9 = 0b01101111,
		Digittosegment_A = 0b01110111,
		Digittosegment_b = 0b01111100,
		Digittosegment_C = 0b00111001,
		Digittosegment_d = 0b01011110,
		Digittosegment_E = 0b01111001,
		Digittosegment_F = 0b01110001
	};
	
	TM_1637(I2c* ap_i2c);
	~TM_1637();
	
	void Init();
	void SetBrightness(Brightness a_brightness);
	void SetSegments(const uint8_t a_segments[], uint8_t a_length, uint8_t a_pos);
	void WriteSegment();
	void WriteDigit();
private:
	void Start();
	void Stop();
  I2c* mp_i2c;
	uint8_t m_brightness;
};




#endif //__TM1637_H__