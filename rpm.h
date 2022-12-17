#ifndef __RPM_H__
#define __RPM_H__

#include <stm32f411xe.h>

class RPM
{
public:
  RPM() = delete;
  RPM(TIM_TypeDef* const ap_timer, const uint32_t a_timer_bus_clock, const uint8_t a_cylinders_number);
  ~RPM();

  const uint16_t GetRPM();
  void CalculateRPM();
  void SetMinRPM(const uint16_t a_min_rpm);
  const uint16_t GetMinRPM();
  void SetNumberOfCylinders(const uint8_t a_cylinders_number);

private:
  const uint32_t m_tim_arr_max;  //IS IT NEEDED?
  const uint32_t m_timer_bus_clock;
  uint16_t m_rpm;
  uint16_t m_min_rpm;
  uint8_t m_cylinders_number;
  uint8_t m_sensitivity;
  TIM_TypeDef* const mp_timer;

};

#endif //__RPM_H__