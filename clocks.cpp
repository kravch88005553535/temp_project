#include <stm32f411xe.h>

void SetSysClockToMax()
{
  FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
  while ((FLASH->ACR & FLASH_ACR_LATENCY_3WS) != FLASH_ACR_LATENCY_3WS) __asm("nop");
  
  
  RCC->CR |= RCC_CR_HSEON; 
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY) __ASM("nop"); 

  RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC; //HSE as PLL source
  RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
  RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
  //RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;  //pllp = 2;

  constexpr int pll_n = 104; //104
  constexpr int pll_m = 13;  //13
  RCC->PLLCFGR |= pll_n << RCC_PLLCFGR_PLLN_Pos;
  RCC->PLLCFGR |= pll_m << RCC_PLLCFGR_PLLM_Pos;
  RCC->PLLCFGR |= RCC_PLLCFGR_PLLQ; //pllq = 16
  
  RCC->CR |= RCC_CR_PLLON;
  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY) __ASM("nop"); 

  //AHB 100MHz
  //APB2 100MHz
  //APB1 50MHz
  //configure PLL
  //HCLK
  constexpr int max_mcu_frequency {100'000'000};
  constexpr int hse_clock {25'000'000};
  
  RCC->CFGR &= ~RCC_CFGR_HPRE; //AHB  not divided
  RCC->CFGR &= ~RCC_CFGR_PPRE2; //APB2 clear
  RCC->CFGR &= ~RCC_CFGR_PPRE1; //APB1 clear
  //RCC->CFGR |= RCC_CFGR_PPRE2_2; //APB2 divided by 2
  RCC->CFGR |= RCC_CFGR_PPRE1_2; //APB1 divided by 2
  RCC->DCKCFGR |= RCC_DCKCFGR_TIMPRE;
  
  RCC->CFGR |= RCC_CFGR_SW_1;
  
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) __ASM("nop"); 

  
  //uart write source clock
  //RCC->CR |= RCC_CR_CSSON;
}