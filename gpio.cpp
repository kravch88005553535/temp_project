#include <stm32f411xe.h>
#include "gpio.h"

Pin::Pin(GPIO_TypeDef* ap_port, uint8_t a_pin_number, Mode a_mode)
  : mp_port(ap_port)
  , m_pin_number(a_pin_number)
  , m_mode(a_mode)
{
  switch(reinterpret_cast<uint32_t>(ap_port))
  {
    case GPIOA_BASE:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    break;
    case GPIOB_BASE:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    break;
    case GPIOC_BASE:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    break;
    case GPIOD_BASE:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    break;
    case GPIOE_BASE:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    break;
    case GPIOH_BASE:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    break;
  }

  switch(static_cast<int>(a_mode))
  {
    case mode_in_floating:
      mp_port->MODER &= ~(GPIO_MODER_MODER0_Msk << (a_pin_number*2)); // clear / 00input
      mp_port->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << (a_pin_number*2)); // clear no pullup/pulldown
      mp_port->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << a_pin_number); // clear out push_pull = 0
    break;
    
    case mode_in_pullup:
      mp_port->MODER &= ~(GPIO_MODER_MODER0_Msk << (a_pin_number*2)); // clear / 00input
      mp_port->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << (a_pin_number*2)); // clear no pullup/pulldown
      mp_port->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << a_pin_number); // clear out push_pull = 0
      mp_port->PUPDR |= GPIO_PUPDR_PUPD0_0 << (a_pin_number*2); //01 pullup
    break;
    
    case mode_in_pulldown:
      mp_port->MODER &= ~(GPIO_MODER_MODER0_Msk << (a_pin_number*2)); // clear / 00input
      mp_port->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << (a_pin_number*2)); // clear no pullup/pulldown
      mp_port->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << a_pin_number); // clear out push_pull = 0
      mp_port->PUPDR |= GPIO_PUPDR_PUPD0_1 << (a_pin_number*2); //10 pulldown
    break;
    
    case mode_out_pullup:
      mp_port->MODER &= ~(GPIO_MODER_MODER0_Msk << (a_pin_number*2)); // clear
      mp_port->MODER |= GPIO_MODER_MODER0_0 << (a_pin_number*2); // 01 output
      mp_port->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << a_pin_number); // clear out push_pull = 0
      mp_port->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << (a_pin_number*2)); // clear no pullup/pulldown
      mp_port->PUPDR |= GPIO_PUPDR_PUPD0_0 << (a_pin_number*2); //01 pullup
    break;
    
    case mode_out_pulldown:
      mp_port->MODER &= ~(GPIO_MODER_MODER0_Msk << (a_pin_number*2)); // clear
      mp_port->MODER |= GPIO_MODER_MODER0_0 << (a_pin_number*2); // 01 output
      mp_port->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << a_pin_number); // clear out push_pull = 0
      mp_port->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << (a_pin_number*2)); // clear no pullup/pulldown
      mp_port->PUPDR |= GPIO_PUPDR_PUPD0_1 << (a_pin_number*2); //10 pulldown
    break;
    
    case mode_out_open_drain:
      mp_port->MODER &= ~(GPIO_MODER_MODER0_Msk << (a_pin_number*2)); // clear
      mp_port->MODER |= GPIO_MODER_MODER0_0 << (a_pin_number*2); // 01 output
      mp_port->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << a_pin_number); // clear out push_pull = 0
      mp_port->OTYPER |= GPIO_OTYPER_OT0_Msk << a_pin_number; //out open drain = 1 
      mp_port->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << (a_pin_number*2)); // clear no pullup/pulldown
    break;
    
    case mode_alternate_function_pullup:
      mp_port->MODER &= ~(GPIO_MODER_MODER0_Msk << (a_pin_number*2)); // clear
      mp_port->MODER |= GPIO_MODER_MODER0_1 << (a_pin_number*2); // 10 alternate
      mp_port->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << a_pin_number); // clear out push_pull = 0
      mp_port->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << (a_pin_number*2)); // clear no pullup/pulldown
      mp_port->PUPDR |= GPIO_PUPDR_PUPD0_0 << (a_pin_number*2); //01 pullup
    break;
    
    case mode_alternate_function_pulldown:
      mp_port->MODER &= ~(GPIO_MODER_MODER0_Msk << (a_pin_number*2)); // clear
      mp_port->MODER |= GPIO_MODER_MODER0_1 << (a_pin_number*2); // 10 alternate
      mp_port->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << a_pin_number); // clear out push_pull = 0
      mp_port->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << (a_pin_number*2)); // clear no pullup/pulldown
      mp_port->PUPDR |= GPIO_PUPDR_PUPD0_1 << (a_pin_number*2); //10 pulldown
    break;
    
    case mode_alternate_function_open_drain:
      mp_port->MODER &= ~(GPIO_MODER_MODER0_Msk << (a_pin_number*2)); // clear
      mp_port->MODER |= GPIO_MODER_MODER0_1 << (a_pin_number*2); // 10 alternate
      mp_port->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << a_pin_number); // clear
      mp_port->OTYPER |= GPIO_OTYPER_OT0_Msk << a_pin_number;    //open drain
      mp_port->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << (a_pin_number*2)); // clear no pullup/pulldown
    break;
    
    case mode_analog:
      mp_port->MODER &= ~(GPIO_MODER_MODER0_Msk << (a_pin_number*2)); // clear
      mp_port->MODER |= GPIO_MODER_MODER0 << (a_pin_number*2); // 11 analog
    break;
  }
		mp_port->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0 << (a_pin_number*2);
}
Pin::~Pin()
{
}
void Pin::Set()
{
  mp_port->ODR |= GPIO_ODR_OD0_Msk << m_pin_number;
}
void Pin::Reset()
{
  mp_port->ODR &= ~(GPIO_ODR_OD0_Msk << m_pin_number);
}
bool Pin::Getstate()
{
  return mp_port->IDR & GPIO_IDR_ID0 << m_pin_number;
}
void Pin::TogglePin(void)
{
  mp_port->ODR ^= GPIO_ODR_OD0_Msk << m_pin_number;
}
void Pin::SetMode(const Mode a_mode)
{
}
Pin::Mode Pin::GetMode()
{
return m_mode;
}

void Pin::SetAlternateFunctionNumber(AlternateFunction a_af_number)
{
  if (m_pin_number <=7)
  {
    mp_port->AFR[0] &= ~(GPIO_AFRL_AFRL0 << m_pin_number*4);
    mp_port->AFR[0] |= a_af_number << m_pin_number*4;
  }
  else
    mp_port->AFR[1] &= ~(GPIO_AFRH_AFRH0 << (m_pin_number-8)*4);
    mp_port->AFR[1] |= a_af_number << (m_pin_number-8)*4;
}

void Pin::Lock()
{
//  mp_port->LCKR |= GPIO_LCKR_LCK0 << m_pin_number;
//  do {mp_port->LCKR ^= GPIO_LCKR_LCKK; } while ((mp_port->LCKR & GPIO_LCKR_LCKK) != GPIO_LCKR_LCKK);
}