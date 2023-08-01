#include <REGX52.H>
#include "OneWire.h"

sbit OneWire_DQ=P3^7;


/**
  * @brief 开始使用单总线协议
  * @param 无
  * @retval 响应值（0为响应，1为未响应）
  */
unsigned char OneWire_Init(void)
{
	unsigned char i,ACK;
	
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	i = 227;while (--i);// 500us
	OneWire_DQ = 1;
	i = 29;while (--i);// 70us
	ACK = OneWire_DQ;
	i = 227;while (--i);// 500us
	return ACK;
}


/**
  * @brief 发送一个位数据（1或0）
  * @param 发送的位数据
  * @retval 无
  */
void OneWire_sendBit(unsigned char Bit)
{
	unsigned char i;
	
	OneWire_DQ = 0;
	i = 4;while (--i);// 15us
	OneWire_DQ = Bit;
	i = 22;while (--i);// 55us
	OneWire_DQ = 1;
}


/**
  * @brief 接收一个位数据
  * @param 无
  * @retval 接收到的位数据
  */
unsigned char OneWire_receiveBit(void)
{
	unsigned char Bit,i;
	
	OneWire_DQ = 0;
	i = 2;while (--i);//10us
	OneWire_DQ = 1;
	i = 2;while (--i);//10us
	Bit = OneWire_DQ;
	i = 22;while (--i);// 55us
	return Bit;
}


/**
  * @brief 发送一个字节数据
  * @param 要发送的字节
  * @retval 无
  */
void OneWire_sendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		OneWire_sendBit(Byte & (0x01<<i));
	}
}


/**
  * @brief 接收一个字节数据
  * @param 无
  * @retval 接收到的字节
  */
unsigned char OneWire_receiveByte(void)
{
	unsigned char Byte = 0x00,i;
	for(i=0;i<8;i++)
	{
		if(OneWire_receiveBit()){Byte |= (0x01<<i);}
	}
	return Byte;
}
