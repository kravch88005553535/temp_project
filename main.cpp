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
	 
	 uint8_t data1 = '8';
	 uint8_t data2 = 'X';

	 eeprom.Write(0x00F2,&data1,1);
	 eeprom.Write(0x00F3,&data2,1);
	 
	 uint8_t recieve_data[5] = {};
	 eeprom.Read(0x00EF, &recieve_data[0], 5);
		 
		__ASM("nop");
	 
	 
   Usart usart(USART1, Usart::Interface_UART, Usart::WordLength_8bits, Usart::StopBits_1, Usart::Oversampling_8, 
     Usart::ParityControl_disabled, Usart::Baudrate_9600KBaud, rcc.GetPeripheralClock(USART1));
   Pin a9(GPIOA, 9, Pin::mode_alternate_function_pulldown);
   Pin a10(GPIOA, 10, Pin::mode_alternate_function_pulldown);
  a9.SetAlternateFunctionNumber(Pin::AlternateFunction_7);

   
   
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
			usart_data[8] = revpermin % 100 /10 +48;
			usart_data[9] = revpermin %10 +48;

			usart_data[19] =  speed / 100 +48;
			usart_data[20] = speed / 10 % 10 +48;
			usart_data[21] = speed %10 +48;
		
		
			
			usart.Transmit(&usart_data[0], 24);
      speedometer.CalcualteSpeed();
      rpm.CalculateRPM();
      
      speed = speedometer.GetSpeed();
      revpermin = rpm.GetRPM();
   
    frequency = static_cast<double>(double(f_cpu) / (TIM1->ARR+1) / (TIM1->PSC+1) /2);
  }  
}