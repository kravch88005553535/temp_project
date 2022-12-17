#ifndef __EEPROM_H__
#define __EEPROM_H__

class Eeprom
{
  public:
  virtual void Read() = 0;
  virtual void Write() = 0;
};


class Spi_eeprom : public Eeprom
{
public:
  Spi_eeprom() = delete;
  Spi_eeprom(/*pointer of spi interface*/);
  ~Spi_eeprom();
  void Read(const a_address, *ap_read_to, *a_size);
  void Write(const a_address, *ap_read_from, *a_size);
private:
//  *const /*pointer of spi interface*/ 
};




#endif //__EEPROM_H__