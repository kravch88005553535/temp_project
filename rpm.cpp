#include "rpm.h"

RPM::RPM(TIM_TypeDef* const ap_timer, const uint32_t a_timer_bus_clock, const uint8_t a_cylinders_number)
  : m_tim_arr_max{65536}
  , mp_timer{ap_timer}
  , m_timer_bus_clock{a_timer_bus_clock}
  , m_cylinders_number{a_cylinders_number}
  , m_sensitivity{0}
{
  switch (reinterpret_cast<uint32_t>(mp_timer))
  {
    case TIM1_BASE:
      RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    break;
    
    case TIM2_BASE :
      RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    break;
    
    case TIM3_BASE :
      RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    break;
    
    case TIM4_BASE :
      RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    break;
    
    case TIM5_BASE :
      RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
    break;
    
    case TIM9_BASE:
      RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
    break;
    
    case TIM10_BASE:
      RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
    break;
    
    case TIM11_BASE:
      RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
    break;
  }

// for future purposes
  
//  switch (reinterpret_cast<uint32_t>(mp_timer))
//  {
//    case TIM1_BASE:
//    case TIM9_BASE:
//    case TIM10_BASE:
//    case TIM11_BASE:
//    m_timer_bus_clock = 
//    break;
//    
//    case TIM2_BASE:
//    case TIM3_BASE:
//    case TIM4_BASE:
//    case TIM5_BASE:
//    m_timer_bus_clock = 
//    break;
//  }
  
  mp_timer->ARR = 0xFFFF;
  
  mp_timer->CCMR1 |= TIM_CCMR1_CC1S_0; //SELECT CC1 ENABLED
//INPUT FILTER DURATION  TIM3->CCMR1 |= TIM_CCMR1_IC1F_0..3 if input signal not stable
  mp_timer->CCER &= ~TIM_CCER_CC1P; //rising edge
  mp_timer->CCER &= ~TIM_CCER_CC1NP;
// Select the edge of the active transition on the TI1 channel by writing the CC1P and 
//CC1NP bits to 00 in the TIMx_CCER register (rising edge in this case).
  
//  TIM3->CCMR1 |= TIM_CCMR1_IC1PSC0..1; //sensitivity
  
  NVIC_EnableIRQ(TIM3_IRQn);
  mp_timer->CCER |= TIM_CCER_CC1E;
  mp_timer->DIER |= TIM_DIER_CC1IE;
  mp_timer->DIER |= TIM_DIER_UIE;

//  TIM3->DIER |= TIM_DIER_CC1DE; DMA Enable

  mp_timer->CR1 |= TIM_CR1_CEN;
  SetMinRPM(400);
//  overflow->rpm=0;
}

RPM::~RPM()
{
}

const uint16_t RPM::GetRPM()
{
  return m_rpm;
}

void RPM::CalculateRPM()
{
  m_rpm = m_timer_bus_clock / m_cylinders_number * 2 / mp_timer->CCR1 * 60  / (mp_timer->PSC+1);

}

void RPM::SetMinRPM(const uint16_t a_min_rpm)
{
  m_min_rpm = a_min_rpm;
  mp_timer->PSC = m_timer_bus_clock / a_min_rpm / m_cylinders_number * 60 * 2 / m_tim_arr_max;
}

const uint16_t RPM::GetMinRPM()
{
  return m_min_rpm;
}


void RPM::SetNumberOfCylinders(const uint8_t a_cylinders_number)
{
  m_cylinders_number = a_cylinders_number;
  //setminrpm
}
