#ifndef __OneWire_H__
#define __OneWire_H__

unsigned char OneWire_Init(void);
void OneWire_sendBit(unsigned char Bit);
unsigned char OneWire_receiveBit(void);
void OneWire_sendByte(unsigned char Byte);
unsigned char OneWire_receiveByte(void);

#endif