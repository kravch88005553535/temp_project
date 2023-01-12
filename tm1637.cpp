#include "tm1637.h"

TM_1637::TM_1637(I2c* ap_i2c)
	: mp_i2c{ap_i2c}
{
};

void TM_1637::Start()
{
	mp_i2c->GenerateStartCondition();

};

void TM_1637::Stop()
{
		mp_i2c->GenerateStopCondition();
};

////void TM_1637::Init()
////{
////	Start();
////	mp_i2c->TransmitDeviceAddress(0x40);
////	Stop();
//};

void TM_1637::SetBrightness(Brightness a_brightness)
{
	Start();
	mp_i2c->TransmitData(0x87 + static_cast<uint8_t>(a_brightness));
	Stop();
};

void TM_1637::SetSegments(const uint8_t a_segments[], uint8_t a_length, uint8_t a_pos)
{
	Start();
	mp_i2c->TransmitData(0x40);
	Stop();
	
	Start();
	mp_i2c->TransmitData(0xC0+(a_pos & 0x03));
	
	for (uint8_t i=0; i<a_length; ++i)
	{
		mp_i2c->TransmitData(a_segments[i]);
	}
	mp_i2c->CheckByteTransmissionFlag();
	Stop();
	
	SetBrightness(Brightness_7);
};