#include "eeprom.h"

I2C_eeprom::I2C_eeprom(uint8_t a_eeprom_address, I2c* ap_i2c_ptr)
  : m_eeprom_address {a_eeprom_address}
  , mp_i2c{ap_i2c_ptr}
{
}

I2C_eeprom::~I2C_eeprom()
{
}

void I2C_eeprom::Read(uint16_t a_address, uint8_t* ap_data, uint32_t a_size)
{	
	if (!(mp_i2c->IsLocked()))
	{
		while (IsEepromBusy()) __ASM("nop");	
	//	mp_i2c->GenerateStartCondition();
	//	mp_i2c->TransmitDeviceAddress(m_eeprom_address);
		mp_i2c->TransmitData(static_cast<uint8_t>(a_address >> 8));
		mp_i2c->TransmitData(static_cast<uint8_t>(a_address&0x00FF));
		mp_i2c->GenerateStartCondition();
		mp_i2c->TransmitDeviceAddress(m_eeprom_address | 0x01);
		while (--a_size)
		{
			mp_i2c->RecieveData(ap_data++);
		}
		mp_i2c->RecieveDataNoAck(ap_data);
		mp_i2c->GenerateStopCondition();
	}
}

void I2C_eeprom::Write(uint16_t a_address, uint8_t* ap_data, uint32_t a_size)
{
	if (!(mp_i2c->IsLocked()))
	{
		while (IsEepromBusy()) __ASM("nop");	
	//	mp_i2c->GenerateStartCondition();
	//	mp_i2c->TransmitDeviceAddress(m_eeprom_address);
		mp_i2c->TransmitData(static_cast<uint8_t>(a_address >> 8));
		mp_i2c->TransmitData(static_cast<uint8_t>(a_address&0x00FF));
		mp_i2c->TransmitData(*ap_data++);
		while (--a_size)
		{
			mp_i2c->TransmitData(*ap_data++);
		}
		mp_i2c->CheckByteTransmissionFlag();
		mp_i2c->GenerateStopCondition();
	}
}
bool I2C_eeprom::IsEepromBusy()
{
	mp_i2c->GenerateStartCondition();
	mp_i2c->GetPtrI2C()->DR = m_eeprom_address;
	while ((mp_i2c->GetPtrI2C()->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR)
		if (mp_i2c->GetPtrI2C()->SR1 & I2C_SR1_AF) 
		{
			mp_i2c->GetPtrI2C()->SR1 &= ~I2C_SR1_AF;
			return true;
		}
	mp_i2c->GetPtrI2C()->SR1;
	mp_i2c->GetPtrI2C()->SR2;
	return false;
}