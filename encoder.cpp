#include "encoder.h"

Rotary_encoder::Rotary_encoder(TIM_TypeDef* ap_timer)
	: mp_timer{ap_timer}
{}