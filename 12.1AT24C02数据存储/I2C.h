#ifndef __I2C_H__
#define __I2C_H__

void I2C_start(void);
void I2C_stop(void);
void I2C_sendByte(unsigned char byte);
unsigned char I2C_receiveByte(void);
void I2C_sendACK(unsigned char Ackbit);
unsigned char I2C_receiveACK(void);

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

#endif