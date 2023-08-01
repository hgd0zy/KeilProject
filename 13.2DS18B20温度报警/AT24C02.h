#ifndef __AT24C02_H_
#define __AT24C02_H_

#define AT24C02_ADDRESS 0xA0

void AT24C02_writeByte(unsigned char wordAddress, Data);
unsigned char AT24C02_readByte(unsigned char wordAddress);

#endif