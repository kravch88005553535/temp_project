#ifndef __FLASH_H__
#define __FLASH_H__

#include <stdint.h>

class Flash
{
Flash();
~Flash();

void Read(uint32_t a_address, uint32_t* ap_data);
void Write(uint32_t a_address, uint32_t* ap_data);
};

#endif //__FLASH_H__