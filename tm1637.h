#ifndef __TM1637_H__
#define __TM1637_H__
#include "i2c.h"


class TM_1637
{
public:
	void Init();
	void SetBrightness(uint8_t brightness);
	void WriteSegment();
	void WriteDigit();
private:
  I2c* mp_i2c;
};




#endif //__TM1637_H__