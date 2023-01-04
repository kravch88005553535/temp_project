#include "i2c.h"

I2c::I2c(I2C_TypeDef* ap_i2c, uint32_t a_i2c_clock, Speed a_speed, Address a_address)
	: mp_i2c{ap_i2c}
	, m_address{a_address}
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

void I2c::Lock()
{
  m_islocked = true;
}

void I2c::Unlock()
{
  m_islocked = false;
}
bool I2c::IsLocked()
{
  return m_islocked;
} 

void I2c::GenerateStartCondition()
{
	mp_i2c->CR1 |= I2C_CR1_START;
	while ((mp_i2c->SR1 & I2C_SR1_SB) != I2C_SR1_SB);
	mp_i2c->SR1;
}

void I2c::GenerateStopCondition()
{
	mp_i2c->CR1 |= I2C_CR1_STOP;
}

void I2c::TransmitDeviceAddress(uint16_t a_address)
{
	switch (static_cast <uint32_t> (m_address))
	{
		case Address_7bit:
		mp_i2c->DR = (a_address & 0xFF);
		while ((mp_i2c->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR) __ASM("nop");
		mp_i2c->SR1;
		mp_i2c->SR2;
		break;
		
		case Address_10bit:
		break;
	}
}

void I2c::TransmitData(uint8_t a_transmitdata)
{
	mp_i2c->DR = a_transmitdata;
	while ((mp_i2c->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE) ;
}

void I2c::RecieveData(uint8_t *ap_recievedata)
{
	mp_i2c->CR1 |= I2C_CR1_ACK;
	while ((mp_i2c->SR1 & I2C_SR1_RXNE) != I2C_SR1_RXNE) __ASM("nop");
	*ap_recievedata = mp_i2c->DR;
}

void I2c::RecieveDataNoAck(uint8_t *ap_recievedata)
{
	mp_i2c->CR1 &= ~I2C_CR1_ACK;
	while ((mp_i2c->SR1 & I2C_SR1_RXNE) != I2C_SR1_RXNE) __ASM("nop");
	*ap_recievedata = mp_i2c->DR;
}

void I2c::CheckByteTransmissionFlag()
{
  while ((mp_i2c->SR1 & I2C_SR1_BTF) != I2C_SR1_BTF) __ASM("nop");
}


void I2c::SetSpeed(Speed a_speed)
{
  //check if locked
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

I2C_TypeDef* I2c::GetPtrI2C()
{
  return mp_i2c;
}