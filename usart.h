#ifndef __USART_H__
#define __USART_H__

#include <stm32f411xe.h>

class Usart
{
	public:
  enum Interface
  {
    Interface_UART,
    Interface_USART,
    Interface_LIN,
    Interface_Smartcard
  };
  enum Baudrate
  {
    Baudrate_1200KBaud = 1200,
    Baudrate_2400KBaud = 2400,
    Baudrate_9600KBaud = 9600,
    Baudrate_19200KBaud = 19200,
    Baudrate_38400KBaud = 38400,
    Baudrate_57600KBaud = 57600,
    Baudrate_115200KBaud = 115200,
    Baudrate_230400KBaud = 230400,
    Baudrate_460800KBaud = 460800,
    Baudrate_921600KBaud = 921600,
    Baudrate_2MBaud = 2'000'000,
    Baudrate_3MBaud = 3'000'000
  };
  enum WordLength :int
  {
    WordLength_8bits,
    WordLength_9bits
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
    Mode_RX,
    Mode_Idle
  };
  enum Oversampling
  {
    Oversampling_8,
    Oversampling_16
  };
  enum ParityControl
  {
    ParityControl_disabled,
    ParityControl_enabled		
  };
  
  Usart() = delete;
  Usart(USART_TypeDef* ap_usart, Interface a_interface, WordLength a_wordlength, StopBits a_stopbits,
    Oversampling a_oversampling, ParityControl a_paritycontrol, Baudrate a_baudrate, uint32_t a_usart_clock);
  ~Usart();
  void SetInterface (Interface a_interface);
  void SetBaudrate(Baudrate a_baudrate, uint32_t a_usart_clock);
  void SetWordLength(Usart::WordLength a_wordlength);
  void SetStopBits(StopBits a_stopbits);
  void SetOversampling(Oversampling a_oversampling);
  void SetParityControl(ParityControl a_paritycontrol);
  uint32_t GetBaudrate();
  void Transmit(uint8_t* ap_data, uint16_t a_size);
  void Recieve(uint8_t* ap_data);
private:
  USART_TypeDef* mp_usart;
  Interface m_interface;
  Mode m_mode;
};

#endif //__USART_H__