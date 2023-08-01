#include <REGX52.H>
#include "AT24C02.h"
#include "I2C.h"
#include "Delay.h"

/**
  * @brief 向AT24C02写一个数据
  * @param 写入的地址和写入的数据
  * @retval 无
  */
void AT24C02_writeByte(unsigned char wordAddress, Data)
{
	I2C_start();//开始I2C
	I2C_sendByte(AT24C02_ADDRESS);//发送模式（从机接收）
	I2C_receiveACK();
	I2C_sendByte(wordAddress);//发送写入地址
	I2C_receiveACK();
	I2C_sendByte(Data);//发送写入数据
	I2C_receiveACK();
	I2C_stop();//关闭I2C
	Delay(5);
}


/**
  * @brief 从AT24C02读取一个数据
  * @param 要读取的地址
  * @retval 读到的数据
  */
unsigned char AT24C02_readByte(unsigned char wordAddress)
{
	unsigned char Data;
	I2C_start();//开始I2C写
	I2C_sendByte(AT24C02_ADDRESS);//发送模式（从机接收）
	I2C_receiveACK();
	I2C_sendByte(wordAddress);//要读取的地址（发送要读取的地址）
	I2C_receiveACK();
	I2C_start();//开始I2C读
	I2C_sendByte(AT24C02_ADDRESS | 0x01);//读取模式（从机发送）
	I2C_receiveACK();
	Data = I2C_receiveByte();//读取一个字节
	I2C_sendACK(1);
	I2C_stop();//关闭I2C
	Delay(5);
	return Data;
}
