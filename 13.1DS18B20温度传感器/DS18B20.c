#include <REGX52.H>
#include "OneWire.h"
#include "DS18B20.h"


/**
  * @brief 将温度写入到缓存中
  * @param 无
  * @retval 无
  */
void DS18B20_ConvertT(void)
{
	OneWire_Init();
	OneWire_sendByte(SKIP_ROM);
	OneWire_sendByte(CONVERT_T);
}


/**
	* @brief 从缓存中读取温度并转化为浮点数
  * @param 无
  * @retval 转化后的温度
  */
float DS18B20_readT(void)
{
	unsigned char TLSB,TMSB;
	int temp;
	float T;
	
	OneWire_Init();
	OneWire_sendByte(SKIP_ROM);
	OneWire_sendByte(READ_SCRATCHPAD);
	TLSB = OneWire_receiveByte();
	TMSB = OneWire_receiveByte();
	temp = (TMSB<<8) | TLSB;//???不知道原理
	T = temp/16.0;
	return T;
}
