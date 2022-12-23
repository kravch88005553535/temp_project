#ifndef __I2C_H__
#define __I2C_H__

#include <stm32f411xe.h>

class I2c
{
public:
	enum Interface
	{
		Interface_I2C,
		Interface_SMBUS
	};
	enum Status
	{	
		Status_Master_Transmitter,
		Status_Master_Reciever,
		Status_Slave_Transmitter,
		Status_Slave_Reciever
	};
	
	enum Mode
	{
		Mode_Sm,
		Mode_Fm
	};
	enum Address
	{
		Address_7bit,
		Address_10bit
	};
	enum Speed
	{
		Speed_100kHz,
		Speed_400kHz
	};
	
	I2c(I2C_TypeDef* ap_i2c, uint32_t a_i2c_clock, Speed a_speed);
	~I2c();
	void Transmit(uint16_t a_address, uint8_t* ap_data, uint32_t a_size);
	void Recieve(uint16_t a_address, uint8_t* ap_data);
	void SetSpeed(Speed a_speed);
private:	
	I2C_TypeDef* mp_i2c;
};

#endif //__I2C_H__