#ifndef __GPIO_H__
#define __GPIO_H__

#include <stm32f411xe.h>

//virtual class for  GPIO
class Gpio
{
virtual void Set() = 0;
virtual void Reset() = 0;
};

class Pin : public Gpio
{
public:
enum Mode : int
{
  mode_in_floating = 0,
  mode_in_pullup,
  mode_in_pulldown,
  mode_out_pullup,
  mode_out_pulldown,
  mode_out_open_drain,
  mode_alternate_function_pullup,
  mode_alternate_function_pulldown,
  mode_alternate_function_open_drain,
  mode_analog
};

enum AlternateFunction :int
{
	AlternateFunction_0 = 0,
	AlternateFunction_1,
	AlternateFunction_2,
	AlternateFunction_3,
	AlternateFunction_4,
	AlternateFunction_5,
	AlternateFunction_6,
	AlternateFunction_7,
	AlternateFunction_8,
	AlternateFunction_9,
	AlternateFunction_10,
	AlternateFunction_11,
	AlternateFunction_12,
	AlternateFunction_13,
	AlternateFunction_14,
	AlternateFunction_15
};

Pin() = delete;
Pin(GPIO_TypeDef* ap_port, uint8_t a_pin_number, Mode a_mode);
~Pin();
void Set();
void Reset();
bool Getstate();
void TogglePin(void);
void SetMode(const Mode a_mode);
Mode GetMode();
void SetAlternateFunctionNumber(AlternateFunction a_af_number);
void Lock();

private:
GPIO_TypeDef* mp_port;
uint8_t m_pin_number;
Mode m_mode;
};

#endif //__GPIO_H__