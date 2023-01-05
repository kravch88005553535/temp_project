#ifndef __RPM_H__
#define __RPM_H__

#include <stm32f411xe.h>

class RPM
{
public:
  enum Cylinders : int
  {
    Cylinders_1 = 1,
    Cylinders_2 = 2,
    Cylinders_3 = 3,
    Cylinders_4 = 4,
    Cylinders_5 = 5,
    Cylinders_6 = 6,
    Cylinders_8 = 8,
    Cylinders_10 = 10,
    Cylinders_12 = 12,
    Cylinders_14 = 14,
    Cylinders_16 = 16
  };

  RPM() = delete;
  RPM(TIM_TypeDef* const ap_timer, const uint32_t a_timer_bus_clock, const Cylinders a_cylinders_number);
  ~RPM();
  
  const uint16_t GetRPM();
  void CalculateRPM();
  void SetMinRPM(const uint16_t a_min_rpm);
  const uint16_t GetMinRPM();
  void SetNumberOfCylinders(const Cylinders a_cylinders_number);
  
  volatile static inline uint32_t m_tachometer_ticks = 0;
private:
  
  const uint32_t m_tim_arr_max;  //IS IT NEEDED?
  const uint32_t m_timer_bus_clock;
  uint16_t m_rpm;
  uint16_t m_min_rpm;
  Cylinders m_cylinders_number;
  uint8_t m_sensitivity_level;
  TIM_TypeDef* const mp_timer;
};


#endif //__RPM_H__