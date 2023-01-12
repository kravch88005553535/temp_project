#include <stm32f411xe.h>
#include "rcc.h"


Rcc::Rcc(System_clock_source a_clock_source, Hse_frequency a_hse_frequency)
  : m_hse_frequency{a_hse_frequency}
{
  FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
  while ((FLASH->ACR & FLASH_ACR_LATENCY_3WS) != FLASH_ACR_LATENCY_3WS) __asm("nop");
	EnableHse();
	SetPllSource(Pll_clock_source_hse_oscillator);
  SetPllM(13);
	SetPllN(104);
	SetPllP(Pll_p_2);
	SetPllQ(15);
	EnablePll();	
	SetApb1Prescaler(Apb1_prescaler_2);
	SetTimersPrescaler(1);
	SetSystemClockSource(a_clock_source);
}

Rcc::~Rcc()
{
	
}
uint32_t Rcc::GetAhbClock()
{
	return GetSystemClock()/ GetAhbPrescaler();
}
uint32_t Rcc::GetApb1Clock()
{
	return GetAhbClock()/GetApb1Prescaler();
} 
uint32_t Rcc::GetApb2Clock()
{
	return GetAhbClock()/GetApb2Prescaler();
}

uint32_t Rcc::GetPeripheralClock(void* a_peripheral)
{
	uint32_t clock{0};
	switch(reinterpret_cast<uint32_t>(a_peripheral))
	{
		case USART1_BASE:
			clock = this->GetApb2Clock();
		break;
			
		case USART2_BASE:
			clock = this->GetApb1Clock();
		break;
		
		case USART6_BASE:
			clock = this->GetApb2Clock();
		break;
	}
	return clock;
}

uint32_t Rcc::GetTimerClock(TIM_TypeDef* ap_timer)
{
  return 100'000'000;
  //here implementation
}

void Rcc::SetSysClockToMax()
{
  FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
  while ((FLASH->ACR & FLASH_ACR_LATENCY_3WS) != FLASH_ACR_LATENCY_3WS) __asm("nop");
	EnableHse();
	SetPllSource(Pll_clock_source_hse_oscillator);
  SetPllM(13);
	SetPllN(104);
	SetPllP(Pll_p_2);
	SetPllQ(15);
	EnablePll();	
	SetApb1Prescaler(Apb1_prescaler_2);
	SetTimersPrescaler(1);
	SetSystemClockSource(System_clock_source_pll_clock);
}

Rcc::System_clock_source Rcc::GetSystemClockSource()
{
	return static_cast<System_clock_source>((RCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos);
}
	
void Rcc::SetSystemClockSource(System_clock_source a_system_clock_source)
{
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= a_system_clock_source << RCC_CFGR_SW_Pos;
	while (GetSystemClockSource() != a_system_clock_source) __ASM("nop");
}
Rcc::Pll_clock_source Rcc::GetPllSource()
{
	return static_cast<Pll_clock_source>(bool(RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC));
}
uint32_t Rcc::GetSystemClock()
{
	switch (static_cast<uint32_t>(GetSystemClockSource()))
	{
		case System_clock_source_hse_clock:
		return m_hse_frequency;
		break;
		
		case System_clock_source_hsi_clock:
		return SystemCoreClock;
		break;
		
		case System_clock_source_pll_clock:
			uint32_t system_clock{};
			system_clock = GetPllSource() == Pll_clock_source_hsi_oscillator ?  SystemCoreClock : m_hse_frequency;
			system_clock *= GetPllN(); 
			system_clock /= GetPllM() * GetPllP();
			return system_clock;
		break;
	}
	while(1){}
	
	return 666;
}

void Rcc::SetPllSource(Pll_clock_source a_pll_clock_soiurce)
{
	switch (static_cast<uint32_t>(a_pll_clock_soiurce))
	{
		case Pll_clock_source_hsi_oscillator:
			RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;
		break;
		case Pll_clock_source_hse_oscillator:
			RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;
		break;
	}
}

void Rcc::SetPllM(uint32_t a_pll_m)
{
#ifdef DEBUG
	//check pllm
#endif //DEBUG
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_Msk;
	RCC->PLLCFGR |= a_pll_m << RCC_PLLCFGR_PLLM_Pos;
}

void Rcc::SetPllN(uint32_t a_pll_n)
{
#ifdef DEBUG
	//check plln
#endif //DEBUG
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_Msk;
	RCC->PLLCFGR |= a_pll_n << RCC_PLLCFGR_PLLN_Pos;
}

void Rcc::SetPllP(Pll_p a_pll_p)
{
#ifdef DEBUG
	//check pllp
#endif //DEBUG
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_Msk;
	RCC->PLLCFGR |= a_pll_p << RCC_PLLCFGR_PLLP_Pos;
}

void Rcc::SetPllQ(uint32_t a_pll_q)
{
#ifdef DEBUG	
	while(a_pll_q < 1 || a_pll_q >15)
	{
	__ASM("nop");
	}
#endif //DEBUG
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ_Msk;
	RCC->PLLCFGR |= a_pll_q << RCC_PLLCFGR_PLLQ_Pos;
}

uint32_t Rcc::GetPllM()
{
	return (RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos;
}

uint32_t Rcc::GetPllN()
{
	return (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
}

uint32_t Rcc::GetPllP()
{
	switch((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos)
	{
		case Pll_p_2:
		return 2;
		
		case Pll_p_4:
		return 4;
				
		case Pll_p_6:
		return 6;
						
		case Pll_p_8:
		return 8;
	}
	
	while(1){}
	return 666;
}

uint32_t Rcc::GetPllQ()
{
	return (RCC->PLLCFGR & RCC_PLLCFGR_PLLQ) >> RCC_PLLCFGR_PLLQ_Pos;
}

bool Rcc::IsHseReady()
{
	return RCC->CR & RCC_CR_HSERDY;
}

bool Rcc::IsPllReady()
{
	return RCC->CR & RCC_CR_PLLRDY;
}

void Rcc::EnableHse()
{
	RCC->CR |= RCC_CR_HSEON; 
	  while (!IsHseReady())	__ASM("nop");
}

void Rcc::DisableHse()
{
	RCC->CR &= ~RCC_CR_HSEON; 
}

void Rcc::EnablePll()
{
	RCC->CR |= RCC_CR_PLLON;
	  while (!IsPllReady()) __ASM("nop"); 
}

void Rcc::DisablePll()
{
	RCC->CR &= ~RCC_CR_PLLON;
}

uint32_t Rcc::GetAhbPrescaler()
{
	switch ((RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos)
	{
		case Ahb_prescaler_not_divided:
		return 1;
		
		case Ahb_prescaler_2:
		return 2;
		
		case Ahb_prescaler_4:
		return 4;
		
		case Ahb_prescaler_8:
		return 8;
		
		case Ahb_prescaler_16:
		return 16;
		
		case Ahb_prescaler_64:
		return 64;
		
		case Ahb_prescaler_128:
		return 128;
		
		case Ahb_prescaler_256:
		return 256;
		
		case Ahb_prescaler_512:
		return 512;		
	}
	while(1){}
	return 666;
}

uint32_t  Rcc::GetApb1Prescaler()
{
	switch ((RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos)
	{
		case Apb1_prescaler_not_divided:
		return 1;
		
		case Apb1_prescaler_2:
		return 2;
		
		case Apb1_prescaler_4:
		return 4;
		
		case Apb1_prescaler_8:
		return 8;
		
		case Apb1_prescaler_16:
		return 16;
	}
	
	while(1){}
			
	return 666;
}

uint32_t  Rcc::GetApb2Prescaler()
{
	switch ((RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos)
	{
		case Apb2_prescaler_not_divided:
		return 1;
		
		case Apb2_prescaler_2:
		return 2;
		
		case Apb2_prescaler_4:
		return 4;
		
		case Apb2_prescaler_8:
		return 8;
		
		case Apb2_prescaler_16:
		return 16;
	}
	
	while(1){}
			
	return 666;
}

void Rcc::SetAhbPrescaler(Ahb_prescaler a_ahb_prescaler)
{
	RCC->CFGR &= ~RCC_CFGR_HPRE;
	RCC->CFGR |= a_ahb_prescaler << RCC_CFGR_HPRE_Pos; 
}

void Rcc::SetApb1Prescaler(Apb1_prescaler a_apb1_prescaler)
{
  RCC->CFGR &= ~RCC_CFGR_PPRE1;
	RCC->CFGR |= a_apb1_prescaler <<RCC_CFGR_PPRE1_Pos;
}

void Rcc::SetApb2Prescaler(Apb2_prescaler a_apb2_prescaler)
{
	RCC->CFGR &= ~RCC_CFGR_PPRE2;
	RCC->CFGR |= a_apb2_prescaler <<RCC_CFGR_PPRE2_Pos;
}

void Rcc::SetTimersPrescaler(bool a_prescaler)
{
	 RCC->DCKCFGR &= ~RCC_DCKCFGR_TIMPRE;
	 RCC->DCKCFGR |= a_prescaler << RCC_DCKCFGR_TIMPRE_Pos;
}
bool Rcc::GetTimersPrescaler()
{
	return RCC->DCKCFGR & RCC_DCKCFGR_TIMPRE;
}