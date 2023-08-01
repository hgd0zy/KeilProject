#include <REGX52.H>
#include "Delay.h"

#define MATRIX_LED_PORT P0

sbit RCK=P3^5;
sbit SCK=P3^6;
sbit SER=P3^4;

/**
  * @brief 初始化74HC595的传送周期
  * @param 无
  * @retval 无
  */
void _74HC595_Init(void)
{
	SCK = 0;
	RCK = 0;
}

/**
  * @brief 向74HC595的数据寄存器写入一个数据(输出端)
  * @param 要输出的数据
  * @retval 无
  */
void _74HC595_Write(unsigned char byte)
{
	unsigned char i;
	//将SER中的数据放入移位寄存器中
	for(i=0;i<8;i++)
	{
		/*
		例:
		10110101 & 10000000 (byte&0x80) = 10000000 = 1(第一位值)
		10110101 & 01000000 (byte&0x40) = 00000000 = 0(第二位值)
		*/
		SER = byte&(0x80>>i);//用移位操作来简化
		SCK = 1;
		SCK = 0;
	}
	//将移位寄存器的数据移动到数据寄存器中
	RCK = 1;
	RCK = 0;
}


/**
  * @brief 指定8x8LED点阵的某一列显示数据
  * @param 选择的列（0-7）,0在左边
	* @param 要显示的数据
  * @retval 无
  */
void LED_Show_column(unsigned char column, Data)
{
	_74HC595_Write(Data);
	MATRIX_LED_PORT = ~(0x80>>column);//从左往右数
	Delay(1);
	MATRIX_LED_PORT = 0xff;
}
