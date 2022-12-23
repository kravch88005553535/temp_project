#include <stm32f411xe.h>
#include "rpm.h"
#include "speedometer.h"


extern "C"{
extern RPM rpm;
void HardFault_Handler()
{
__ASM("nop");
}

void TIM1_UP_TIM10_IRQHandler()
{  
  TIM1->ARR -= 1;
  TIM1->ARR == 0 ? TIM1->ARR = 65535/2 : TIM1->ARR;
  
  GPIOC->ODR ^= GPIO_ODR_OD13;
  while(TIM1->SR) TIM1->SR = 0;
}

void TIM3_IRQHandler()
{
  while((TIM3->SR & TIM_SR_UIF) == TIM_SR_UIF)
  {
    RPM::m_tachometer_ticks = 0;
    TIM3->SR &= ~TIM_SR_UIF;
    TIM3->SR &= ~TIM_SR_CC1IF;
  }
  
  while((TIM3->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF)
  {
    RPM::RPM::m_tachometer_ticks = ((TIM3->PSC+1)*TIM3->CCR1);
    TIM3->SR &= ~TIM_SR_CC1IF;
    TIM3->CNT = 0;
  }
}

void TIM4_IRQHandler()
{
  while((TIM4->SR & TIM_SR_UIF) == TIM_SR_UIF)
  {
    Speedometer::m_speedometer_ticks = 0;
    TIM4->SR &= ~TIM_SR_UIF;
    TIM4->SR &= ~TIM_SR_CC1IF;
  }
  
  while((TIM4->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF)
  {
    Speedometer::m_speedometer_ticks = ((TIM4->PSC+1) * TIM4->CCR1);
    TIM4->SR &= ~TIM_SR_CC1IF;
    TIM4->CNT = 0;
  }
}

}
