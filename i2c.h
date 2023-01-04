#ifndef __I2C_H__
#define __I2C_H__

#include <stm32f411xe.h>

class I2C_Interface
{
public:
virtual void Lock() = 0;
virtual void Unlock() = 0;
virtual bool IsLocked() = 0;
};

class I2c: public I2C_Interface 
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
	
	I2c(I2C_TypeDef* ap_i2c, uint32_t a_i2c_clock, Speed a_speed, Address a_address);
	~I2c();
	
  void Lock();
  void Unlock();
  bool IsLocked();
	void GenerateStartCondition();
	void GenerateStopCondition();
	void TransmitDeviceAddress(uint16_t a_address);
	void TransmitData(uint8_t a_transmitdata);
	void RecieveData(uint8_t *ap_recievedata);
	void RecieveDataNoAck(uint8_t *ap_recievedata);
	void CheckByteTransmissionFlag();
	void SetSpeed(Speed a_speed);
  I2C_TypeDef* GetPtrI2C();
private:	
	Address m_address;
	I2C_TypeDef* mp_i2c;
  bool m_islocked;
};

#endif //__I2C_H__