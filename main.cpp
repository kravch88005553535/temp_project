#include <stm32f411xe.h>

//#include "clocks.h"
#include "gpio.h"
#include "rpm.h"
#include "speedometer.h"
#include "eeprom_data.h"
#include "rcc.h"
#include "led_strip.h"

volatile bool v;
volatile double frequency{400};
constexpr uint32_t f_cpu = 100'000'000;

  extern "C" {

void HardFault_Handler()
{
__ASM("nop");
}

void TIM1_UP_TIM10_IRQHandler()
{  
  GPIOC->ODR ^= GPIO_ODR_OD13;
  while(TIM1->SR) TIM1->SR = 0;
}

void TIM3_IRQHandler()
{
  while((TIM3->SR & TIM_SR_UIF) == TIM_SR_UIF)
  {
    v=0;
    TIM3->SR &= ~TIM_SR_UIF;
  }
  
  while((TIM3->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF)
  {
    v=1;
    TIM3->SR &= ~TIM_SR_CC1IF;
    TIM3->CNT = 0;
  }
}
  
  
}

int main (void)
 {
   Rcc rcc(Rcc::Pll_clock ,25000);
  
  Pin c13(GPIOC, 13, Pin::mode_out_pulldown);
   
//  bool state {c13.Getstate()};
//  static Eeprom_data eeprom_data;
  
  DBGMCU->APB2FZ |= DBGMCU_APB2_FZ_DBG_TIM1_STOP;
  DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_TIM3_STOP;
   
  Pin B4(GPIOB, 4, Pin::mode_alternate_function_pulldown);
  B4.SetAlternateFunctionNumber(2);
  
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  
  TIM1->ARR = 65535;
  TIM1->PSC = 4;
  TIM1->DIER |= TIM_DIER_UIE;
  TIM1->CR1 |= TIM_CR1_CEN;
  NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

  //  RPM rpm (TIM3, 100'000'000 ,4);  
  Speedometer speedometer (Speedometer::Pulses_6K, TIM3, rcc.GetTimerClock(TIM3), Speedometer::Kilometers);

  uint32_t revpermin = 0;
  uint32_t speed = 0; 
  
while(1)
  {
      frequency = static_cast<double>(double(f_cpu) / (TIM1->ARR+1) / (TIM1->PSC+1) /2);
    if(v) 
    {
      speedometer.CalcualteSpeed();
//      rpm.CalculateRPM();
      v=0;
      speed = speedometer.GetSpeed();
//      revpermin = rpm.GetRPM();
    }
  }  
}