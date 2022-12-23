#ifndef __RCC_H__
#define __RCC_H__

class Rcc
{
public:
  enum Pll_clock_source
  {
    Hse_oscillator,
    Hsi_oscillator
  };
  enum Clock_source
  {
    Hse_clock,
    Hsi_clock,
    Pll_clock,
    Lse_clock,
    Lsi_clock
  };
  Rcc() = delete;
  Rcc(Clock_source a_clock_source, uint16_t a_hse_frequency);
  ~Rcc();
  void SetPLLSource(Pll_clock_source);
  void SetAHBClock();
  uint32_t GetAhbClock();
  uint32_t GetApb1Clock();  
  uint32_t GetApb2Clock();
	uint32_t GetPeripheralClock(void* a_peripheral);
  uint32_t GetTimerClock(TIM_TypeDef* ap_timer);
  void SetMcuToLowPowerMode();
  void SetMcuToRunMode();
private:
  void SetSysClockToMax();
  Clock_source m_clock_source;
  uint16_t m_hse_frequency;
};

#endif //__RCC_H__