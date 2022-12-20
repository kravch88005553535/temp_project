#include <math.h>
#include "usart.h"


Usart::Usart(USART_TypeDef* ap_usart, Interface a_interface, WordLength a_wordlength, StopBits a_stopbits,
  Oversampling a_oversampling, ParityControl a_paritycontrol, Baudrate a_baudrate, uint32_t a_usart_clock)
  : mp_usart{ap_usart}
  , m_interface{a_interface}
{
  switch(reinterpret_cast<uint32_t>(ap_usart))
  {
    case USART1_BASE:
      RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    break;
        
    case USART2_BASE:
      RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
     break;
     
     case USART6_BASE:
       RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
     break;
   }
   
  mp_usart->CR1 |= USART_CR1_UE;
  SetWordLength(a_wordlength);
  SetStopBits(a_stopbits);
  SetOversampling(a_oversampling);
  SetParityControl(a_paritycontrol);
  
  SetBaudrate(a_baudrate, a_usart_clock);
  m_mode = Mode::Mode_Idle;
  
  //configure interface
}

Usart::~Usart()
{
}

void Usart::SetInterface (Interface a_interface)
{
	m_interface = a_interface;
}

void Usart::SetOversampling(Oversampling a_oversampling)
{
  switch(static_cast<uint32_t>(a_oversampling))
  {
    case Oversampling_8:
      mp_usart->CR1 |= USART_CR1_OVER8;
    break;
    
    case Oversampling_16:
      mp_usart->CR1 &= ~USART_CR1_OVER8;
    break;
  }
}

void Usart::SetWordLength(WordLength a_wordlength)
{
  switch(static_cast<uint32_t>(a_wordlength))
  {
    case WordLength_8bits:
      mp_usart->CR1 &= ~USART_CR1_M;
    break;
    
    case WordLength_9bits:
      mp_usart->CR1 |= USART_CR1_M;
    break;
  }
}

void Usart::SetStopBits(StopBits a_stopbits)
{
  if(m_interface==Interface_UART | m_interface==Interface_USART)
  {
    switch(static_cast<uint32_t>(a_stopbits))
    {
    case StopBits_1:
      mp_usart->CR2 &= ~USART_CR2_STOP;
    break;
    
    case StopBits_2:
      mp_usart->CR2 &= ~USART_CR2_STOP;
      mp_usart->CR2 |= USART_CR2_STOP_1;
    break;
    }
  }else
  {
    while(1);
  }
}

void Usart::SetBaudrate(Baudrate a_baudrate, uint32_t a_usart_clock)
{
  double baudrate = static_cast <double>(a_usart_clock) / 
    (static_cast<uint32_t>(a_baudrate) * 8 * (2 - static_cast<bool>(mp_usart->CR1 & USART_CR1_OVER8)));
  mp_usart->BRR =0;
  
  if ((mp_usart->CR1 & USART_CR1_OVER8)) //oversampling = 8
  {
    mp_usart->BRR |=  static_cast<uint32_t>(baudrate) << USART_BRR_DIV_Mantissa_Pos;
    uint8_t fraction =	static_cast<uint32_t>(round((baudrate - static_cast<uint32_t>(baudrate))*8)) & USART_BRR_DIV_Fraction_Msk;
    mp_usart->BRR |= fraction > 8 ? --fraction : fraction;
  } 
  else                                  //oversampling = 16
  {
    mp_usart->BRR |=  static_cast<uint32_t>(baudrate) << USART_BRR_DIV_Mantissa_Pos;
    mp_usart->BRR |= 	static_cast<uint32_t>(round((baudrate - static_cast<uint32_t>(baudrate))*16)) & USART_BRR_DIV_Fraction_Msk;
  }
}

void Usart::SetParityControl(ParityControl a_paritycontrol)
{
  switch(static_cast<uint32_t>(a_paritycontrol))
  {
    case ParityControl_disabled:
      mp_usart->CR1 &= ~USART_CR1_PCE;
    break;
    
    case ParityControl_enabled:
      mp_usart->CR1 |= USART_CR1_PCE;
    break;
  }
}

uint32_t Usart::GetBaudrate()
{
//	rcc.GetPeripheralClock(USART1) / 8 / (2 - static_cast<bool>(mp_usart->CR1 & USART_CR1_OVER8)) / usartdiv
	return 0;
}
void Usart::Transmit(uint8_t* ap_data, uint16_t a_size)
{
  m_mode = Mode::Mode_TX;
  mp_usart->CR1 |= USART_CR1_TE;
  while(a_size)
  {
    while (!(mp_usart->SR & USART_SR_TXE));
    mp_usart->DR = *ap_data;
    --a_size;
    if(a_size) ap_data++;
  }
  m_mode = Mode::Mode_Idle;
}

//void Recieve(uint8_t* ap_data);
