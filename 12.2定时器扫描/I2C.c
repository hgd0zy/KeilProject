#include <REGX52.H>
#include "I2C.h"


/**
  * @brief I2C开始
  * @param 无
  * @retval 无
  */
void I2C_start(void)
{
	I2C_SCL = 0;
	I2C_SDA = 1;
	I2C_SCL = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
}


/**
  * @brief I2C结束
  * @param 无
  * @retval 无
  */
void I2C_stop(void)
{
	I2C_SDA = 0;
	I2C_SCL = 1;  
	I2C_SDA = 1;
}


/**
  * @brief I2C发送一个字节
  * @param 要发送的字节
  * @retval 无
  */
void I2C_sendByte(unsigned char byte)
{
	unsigned char i;
	for(i=0;i<8;i++){
		I2C_SDA = (byte<<i) & 0x80;
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}


/**
  * @brief I2C接收一个字节
  * @param 无
  * @retval 接收到的字节
  */
unsigned char I2C_receiveByte(void)
{
	unsigned char Data = 0x00,i;
	
	I2C_SDA = 1;
	for(i=0;i<8;i++)
	{
		I2C_SCL = 1;
		if(I2C_SDA){Data |= (0x80>>i);}
		I2C_SCL = 0;
	}
	return Data;
}


/**
  * @brief I2C发送应答(0为应答，1为非应答)
  * @param 发送的应答
  * @retval 无
  */
void I2C_sendACK(unsigned char Ackbit)
{
	I2C_SDA = Ackbit & 0x01;
	I2C_SCL = 1;
	I2C_SCL = 0;
}


/**
  * @brief I2C接收应答
  * @param 无
  * @retval 接收到的应答
  */
unsigned char I2C_receiveACK(void)
{
	unsigned char Ackbit;
	I2C_SDA  = 1;
	I2C_SCL = 1;
	Ackbit = I2C_SDA;
	I2C_SCL = 0;
	return Ackbit;
}