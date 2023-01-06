#include <stm32f411xe.h>

//#include "clocks.h"
#include "gpio.h"
#include "rpm.h"
#include "speedometer.h"
#include "eeprom.h"
#include "eeprom_data.h"
#include "rcc.h"
#include "led_strip.h"
#include "usart.h"
#include "gearbox.h"
//#include "i2c.h"

volatile double frequency{400};
constexpr uint32_t f_cpu = 100'000'000;

int main (void)
{
	Rcc rcc(Rcc::Pll_clock, 25000);	
	Pin c13(GPIOC, 13, Pin::mode_out_pulldown);

	Pin B8(GPIOB, 8, Pin::mode_alternate_function_open_drain); //I2C B8 clock
	Pin B9(GPIOB, 9, Pin::mode_alternate_function_open_drain); //I2C B9 data
	B8.SetAlternateFunctionNumber(Pin::AlternateFunction_4);
	B9.SetAlternateFunctionNumber(Pin::AlternateFunction_4);	 
	I2c i2c(I2C1,rcc.GetApb1Clock(), I2c::Speed_400kHz, I2c::Address_7bit);

	I2C_eeprom eeprom(0xA0, &i2c);
	double tr_data{998.1675};
//	eeprom.Write(0x0005,reinterpret_cast<uint8_t*>(&tr_data),sizeof(double));
	double r_data{55.1};
	eeprom.Read(0x0005, reinterpret_cast<uint8_t*>(&r_data),sizeof(double));
	uint8_t u8temp[sizeof(double)];	
	eeprom.Read(0x0005, &u8temp[0],sizeof(double));
	
	uint8_t ptr[9] = {8,5,4,2,4,0,9,2,45};
	LedStrip::Animation ptr_animation {LedStrip::Animation::onecolortoanother};
	
	eeprom.Write(eeprom_leds_num, &ptr[0], sizeof (uint8_t));
	eeprom.Write(eeprom_brightness, &ptr[1], sizeof (uint8_t));
	eeprom.Write(eeprom_dimmer_brightness, &ptr[2], sizeof (uint8_t));
	
	eeprom.Write(eeprom_animation, reinterpret_cast<uint8_t*>(&ptr_animation), sizeof (ptr_animation));
	
	eeprom.Write(eeprom_segments_number, &ptr[3], sizeof (uint8_t));
	Color ptr_color[6];
//	eeprom.Write(eeprom_shift_color_1, reinterpret_cast<uint8_t*>(&ptr_color), sizeof(ptr_color));
//	eeprom.Write(eeprom_shift_color_2, reinterpret_cast<uint8_t*>(&ptr_color), sizeof(ptr_color));
//	eeprom.Write(eeprom_seg_1_color, reinterpret_cast<uint8_t*>(&ptr_color), sizeof(ptr_color));
//	eeprom.Write(eeprom_seg_2_color, reinterpret_cast<uint8_t*>(&ptr_color), sizeof(ptr_color));
//	eeprom.Write(eeprom_seg_3_color, reinterpret_cast<uint8_t*>(&ptr_color), sizeof(ptr_color));
//	eeprom.Write(eeprom_seg_4_color, reinterpret_cast<uint8_t*>(&ptr_color), sizeof(ptr_color));
//	
	eeprom.Write(eeprom_seg_1_led_number, &ptr[4], sizeof (uint8_t));
	eeprom.Write(eeprom_seg_2_led_number, &ptr[5], sizeof (uint8_t));
	eeprom.Write(eeprom_seg_3_led_number, &ptr[6], sizeof (uint8_t));
	eeprom.Write(eeprom_seg_4_led_number, &ptr[7], sizeof (uint8_t));
//	
	auto cylinders_number = RPM::Cylinders_4;
//	eeprom.Write(eeprom_cylinders_number, reinterpret_cast<uint8_t*>(&cylinders_number), sizeof (cylinders_number));
//	eeprom.Write(eeprom_tachometer_sensitivity_level, &ptr, sizeof (uint8_t));
//	
	
	////////////////
	for (int i=0; i< (sizeof(ptr)/sizeof(ptr[0])); i++)
		ptr[i] = 0;
	
	eeprom.Read(eeprom_leds_num, &ptr[0], sizeof (uint8_t));
	eeprom.Read(eeprom_brightness, &ptr[1], sizeof (uint8_t));
	eeprom.Read(eeprom_dimmer_brightness, &ptr[2], sizeof (uint8_t));
	
	eeprom.Read(eeprom_animation, reinterpret_cast<uint8_t*>(&ptr_animation), sizeof (ptr_animation));
	
	eeprom.Read(eeprom_segments_number, &ptr[3], sizeof (uint8_t));

	eeprom.Read(eeprom_shift_color_1, reinterpret_cast<uint8_t*>(&ptr_color[0]), sizeof(ptr_color[0]));
	eeprom.Read(eeprom_shift_color_2, reinterpret_cast<uint8_t*>(&ptr_color[1]), sizeof(ptr_color[1]));
	eeprom.Read(eeprom_seg_1_color, reinterpret_cast<uint8_t*>(&ptr_color[2]), sizeof(ptr_color[2]));
	eeprom.Read(eeprom_seg_2_color, reinterpret_cast<uint8_t*>(&ptr_color[3]), sizeof(ptr_color[3]));
	eeprom.Read(eeprom_seg_3_color, reinterpret_cast<uint8_t*>(&ptr_color[4]), sizeof(ptr_color[4]));
	eeprom.Read(eeprom_seg_4_color, reinterpret_cast<uint8_t*>(&ptr_color[5]), sizeof(ptr_color[5]));
	
	eeprom.Read(eeprom_seg_1_led_number, &ptr[4], sizeof (uint8_t));
	eeprom.Read(eeprom_seg_2_led_number, &ptr[5], sizeof (uint8_t));
	eeprom.Read(eeprom_seg_3_led_number, &ptr[6], sizeof (uint8_t));
	eeprom.Read(eeprom_seg_4_led_number, &ptr[7], sizeof (uint8_t));
	

	eeprom.Read(eeprom_cylinders_number, reinterpret_cast<uint8_t*>(&cylinders_number), sizeof (cylinders_number));
	eeprom.Read(eeprom_tachometer_sensitivity_level, &ptr[8], sizeof (uint8_t));
	
	__ASM("nop");
	 
	int a = Eeprom_offsets::eeprom_crc;

	Gearbox gearbox;

	gearbox.SetGearRatio(Gearbox::Gear_main, 4.13); //eeprom download
	gearbox.SetGearRatio(Gearbox::Gear_first, 2.92);
	gearbox.SetGearRatio(Gearbox::Gear_second, 2.05);
	gearbox.SetGearRatio(Gearbox::Gear_third, 1.56);
	gearbox.SetGearRatio(Gearbox::Gear_fourth, 1.31);
	gearbox.SetGearRatio(Gearbox::Gear_fifth, 1.13);
	gearbox.SetGearRatio(Gearbox::Gear_sixth, 0.94);

	gearbox.SetTireWidth(185);
	gearbox.SetTireHeight(60);
	gearbox.SetRimDiameter(14);
	gearbox.CalculateCircumference();
	gearbox.CalculateGear(800, 11);


	Usart usart(USART1, Usart::Interface_UART, Usart::WordLength_8bits, Usart::StopBits_1, Usart::Oversampling_8, 
	 Usart::ParityControl_disabled, Usart::Baudrate_9600KBaud, rcc.GetPeripheralClock(USART1));
	Pin A9(GPIOA, 9, Pin::mode_alternate_function_pulldown);
	Pin A10(GPIOA, 10, Pin::mode_alternate_function_pulldown);
	A9.SetAlternateFunctionNumber(Pin::AlternateFunction_7);

  DBGMCU->APB2FZ |= DBGMCU_APB2_FZ_DBG_TIM1_STOP;
  DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_TIM3_STOP;
   
  Pin B4(GPIOB, 4, Pin::mode_alternate_function_pulldown);
  B4.SetAlternateFunctionNumber(Pin::AlternateFunction_2);
   
  Pin B6(GPIOB, 6, Pin::mode_alternate_function_pulldown);
  B6.SetAlternateFunctionNumber(Pin::AlternateFunction_2);
  
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  
  TIM1->ARR = 65535/2;
  TIM1->PSC = 90;
  TIM1->DIER |= TIM_DIER_UIE;
  TIM1->CR1 |= TIM_CR1_CEN;
  NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

  RPM rpm (TIM3, rcc.GetTimerClock(TIM3),RPM::Cylinders_4);
  Speedometer speedometer (Speedometer::Pulses_6K, TIM4, rcc.GetTimerClock(TIM4), Speedometer::Kilometers);

  uint32_t revpermin = 0;
  uint32_t speed = 0; 
  uint8_t usart_data[] = {'R', 'P', 'M', ' ', '=', ' ', 't', 'e', 's', 't',
		' ','s','p','e','e','d',' ','=',' ','s', 'p', 'd','\n', '\r'};
while(1)
  {
			usart_data[6] = revpermin /1000 +48;
			usart_data[7] = revpermin / 100 % 10 +48;
			usart_data[8] = revpermin % 100 / 10 +48;
			usart_data[9] = revpermin %10 +48;

			usart_data[19] =  speed / 100 +48;
			usart_data[20] = speed / 10 % 10 +48;
			usart_data[21] = speed % 10 +48;
		
			usart.Transmit(&usart_data[0], 24);
      speedometer.CalcualteSpeed();
      rpm.CalculateRPM();
      
      speed = speedometer.GetSpeed();
      revpermin = rpm.GetRPM();
		
			gearbox.CalculateGear(rpm.GetRPM(), speedometer.GetSpeed());
   
    frequency = static_cast<double>(double(f_cpu) / (TIM1->ARR+1) / (TIM1->PSC+1) /2);
  }  
}