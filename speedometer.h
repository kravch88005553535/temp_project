#ifndef __SPEEDOMETER_H__
#define __SPEEDOMETER_H__

#include <stm32f411xe.h>

class Speedometer
{
  public:
    enum PulsesPerUnit :int
    {
      Pulses_2K = 2000,
      Pulses_3K = 3000,
      Pulses_4K = 4000,
      Pulses_5K = 5000,
      Pulses_6K = 6000,
      Pulses_7K = 7000,
      Pulses_8K = 8000,
      Pulses_9K = 9000,
      Pulses_10K = 10000,
      Pulses_11K = 11000,
      Pulses_12K = 12000,
      Pulses_13K = 13000,
      Pulses_14K = 14000,
      Pulses_15K = 15000,
      Pulses_16K = 16000,
      Pulses_17K = 17000,
      Pulses_18K = 18000,
      Pulses_19K = 19000,
      Pulses_20K = 20000,
      Pulses_21K = 21000,
      Pulses_22K = 22000,
      Pulses_23K = 23000,
      Pulses_24K = 24000,
      Pulses_25K = 25000
    };
    enum Units
    {
      Kilometers = 0,
      Miles
    };
    Speedometer() = delete;
    Speedometer(const PulsesPerUnit a_pulses_per_unit, TIM_TypeDef* const ap_timer, 
                const uint32_t a_timer_bus_clock, const Speedometer::Units a_units);
    ~Speedometer();
    void CalcualteSpeed();
    void SetUnits(Speedometer::Units a_units);
    void SetPulsesPerUnit(uint16_t a_pulses_per_unit);
    const uint16_t GetSpeed();
  
  private:
    const uint32_t m_tim_arr_max;  //IS IT NEEDED?
    const uint32_t m_timer_bus_clock;
    uint8_t m_sensitivity;
    uint16_t m_speed;
    uint16_t m_pulses_per_unit;
    Units m_units;
    TIM_TypeDef* const mp_timer;
};

#endif //__SPEEDOMETER_H__