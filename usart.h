#ifndef __USART_H__
#define __USART_H__

#include <stm32f411xe.h>

class Usart
{
  enum Interface
  {
    Interface_UART,
    Interface_USART
  };
  enum WordLength
  {
    WordLength_8b,
    WordLength_9b
  };
  enum StopBits
  {
    StopBits_0_5,
    StopBits_1,
    StopBits_1_5,
    StopBits_2
  };
  enum Mode
  {
    Mode_TX,
    Mode_RX
  };
  enum Oversampling
  {
    Oversampling_8,
    Oversampling_16
  };
  
public:
  Usart() = delete;
  Usart(USART_TypeDef* ap_usart, Interface a_interface, uint32_t a_baudrate, WordLength a_wordlength);
  ~Usart();
  void SetBaudrate(uint32_t a_baudrate);
  uint32_t GetBaudrate();
  void Read();
  void Write();
private:
  USART_TypeDef* mp_usart;
  Interface m_interface;
};

#endif //__USART_H__