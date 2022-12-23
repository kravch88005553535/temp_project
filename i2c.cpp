#include "i2c.h"

I2c::I2c(I2C_TypeDef* ap_i2c, uint32_t a_i2c_clock, Speed a_speed)
	:mp_i2c{ap_i2c}
{
	switch(reinterpret_cast<uint32_t>(mp_i2c))
	{
		case I2C1_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		break;
		
		case I2C2_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
		break;
		
		case I2C3_BASE:
			RCC->APB1ENR |=  RCC_APB1ENR_I2C3EN;
		break;
	}
  
  
  mp_i2c->CR1 |= I2C_CR1_SWRST;
  mp_i2c->CR1 &= ~I2C_CR1_SWRST;
	
	mp_i2c->CR2 &= ~I2C_CR2_FREQ;
	mp_i2c->CR2 |= a_i2c_clock / 1'000'000 << I2C_CR2_FREQ_Pos;	
	SetSpeed(a_speed);
	mp_i2c->CR1 |= I2C_CR1_PE;
}

I2c::~I2c()
{
}

void I2c::Transmit(uint16_t a_address, uint8_t* ap_data, uint32_t a_size)
{
	mp_i2c->CR1 |= I2C_CR1_START;
	while ((mp_i2c->SR1 & I2C_SR1_SB) != I2C_SR1_SB) ;
	mp_i2c->SR1;
  mp_i2c->DR = 0xA0;
	while ((mp_i2c->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR) __ASM("nop");
  mp_i2c->SR1;
  mp_i2c->SR2;
  while ((mp_i2c->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE);
	mp_i2c->DR = static_cast<uint8_t>(a_address >> 8);
	while ((mp_i2c->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE);
	mp_i2c->DR = static_cast<uint8_t>(a_address&0x00FF);
  while ((mp_i2c->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE) ;
  mp_i2c->DR = *ap_data;
//  while (a_size--)
//	{
//		while ((mp_i2c->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE) ;
//		mp_i2c->DR = *ap_data;
//		ap_data++;
//	}
  while ((mp_i2c->SR1 & I2C_SR1_BTF) != I2C_SR1_BTF) ;
	mp_i2c->CR1 |= I2C_CR1_STOP;
}

void I2c::Recieve(uint16_t a_address, uint8_t* ap_data)
{
  mp_i2c->CR1 |= I2C_CR1_START;
	while ((mp_i2c->SR1 & I2C_SR1_SB) != I2C_SR1_SB) ;
	mp_i2c->SR1;
  mp_i2c->DR = 0xA0;
	while ((mp_i2c->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR) __ASM("nop");
  mp_i2c->SR1;
  mp_i2c->SR2;
  while ((mp_i2c->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE) ;
	mp_i2c->DR = static_cast<uint8_t>(a_address >> 8);
	while ((mp_i2c->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE) ;
	mp_i2c->DR = static_cast<uint8_t>(a_address&0x00FF);
  while ((mp_i2c->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE) ;
  
  mp_i2c->CR1 |= I2C_CR1_START;
  while ((mp_i2c->SR1 & I2C_SR1_SB) != I2C_SR1_SB) ;
	mp_i2c->SR1;
  mp_i2c->DR = 0xA1;

  
  mp_i2c->CR1 &= ~I2C_CR1_ACK;
	mp_i2c->SR1 &= ~I2C_SR1_ADDR;
  (void)mp_i2c->SR1;
  (void)mp_i2c->SR2;

	while ((mp_i2c->SR1 & I2C_SR1_RXNE) != I2C_SR1_RXNE);
	*ap_data = mp_i2c->DR;
  mp_i2c->CR1 |= I2C_CR1_STOP;
	
	
}

void I2c::SetSpeed(Speed a_speed)
{
	mp_i2c->CR1 &= ~I2C_CR1_PE;
	uint32_t apb_frequency = mp_i2c->CR2 & I2C_CR2_FREQ_Msk;
	const uint32_t Trise_plus_Tw_100kHz = 5000;

	switch (static_cast<uint32_t>(a_speed))
	{
		case Speed_100kHz:
			mp_i2c->CCR &= ~I2C_CCR_FS;
			mp_i2c->CCR &= ~I2C_CCR_CCR_Msk;
			mp_i2c->CCR = apb_frequency * Trise_plus_Tw_100kHz / 1000;
			mp_i2c->TRISE = apb_frequency + 1;
		break;
		
		case Speed_400kHz:
			mp_i2c->CCR |= I2C_CCR_FS;
			mp_i2c->CCR |= I2C_CCR_DUTY;
			mp_i2c->CCR &= ~I2C_CCR_CCR_Msk;
			mp_i2c->CCR |= apb_frequency * 100 /1000;
			mp_i2c->TRISE = (apb_frequency * 300 / 1000) + 1;
		break;
	}
	mp_i2c->CR1 |= I2C_CR1_PE;
}