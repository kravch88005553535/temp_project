#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <stm32f411xe.h>

class Rotary_encoder
{
	public:

	Rotary_encoder(TIM_TypeDef* ap_timer);
	
	Rotary_encoder() = delete;
	~Rotary_encoder();
	
	void Check();
	private:
	TIM_TypeDef* mp_timer;
};

#endif //__ENCODER_H__