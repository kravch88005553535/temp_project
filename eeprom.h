#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "i2c.h"

class Eeprom_interface
{
  public:
  virtual void Read() = 0;
  virtual void Write() = 0;
};

class I2C_eeprom //: public Eeprom_interface
{
public:
  I2C_eeprom() = delete;
  I2C_eeprom(uint8_t a_eeprom_address, I2c* ap_i2c_ptr);
  ~I2C_eeprom();

  void Read(uint16_t a_address, uint8_t* ap_data, uint32_t a_size);
 	void Write(uint16_t a_address, uint8_t* ap_data, uint32_t a_size);
	bool IsEepromBusy();
private:
  I2c* mp_i2c;
  uint8_t m_eeprom_address;
};

//class Spi_eeprom : public Eeprom
//{
//public:
//  Spi_eeprom() = delete;
//  Spi_eeprom(/*pointer of spi interface*/);
//  ~Spi_eeprom();
//  void Read(const a_address, *ap_read_to, *a_size);
//  void Write(const a_address, *ap_read_from, *a_size);
//private:
////  *const /*pointer of spi interface*/ 
//};

#endif //__EEPROM_H__