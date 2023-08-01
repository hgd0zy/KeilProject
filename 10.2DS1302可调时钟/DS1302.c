#include <REGX52.H>
#include "DS1302.h"

sbit DS1302_SCLK=P3^6;
sbit DS1302_CE=P3^5;
sbit DS1302_IO=P3^4;

char DS1302_time[] = {23,03,16,20,24,30};



/**
  * @brief 初始化DB1302
  * @param 无
  * @retval 无
  */
void DS1302_Init(void)
{
	DS1302_SCLK = 0;//时钟初始化
	DS1302_CE = 0;//电源置0
}



/**
  * @brief 向DB1302中指定的位置写入一个字节的数据
  * @param 写入的命令和地址
	* @param 要写入的数据
  * @retval 无
  */
void DS1302_Write(unsigned char Command, Data)
{
	unsigned char i;
	DS1302_CE = 1;//电源
	
	//读入指令和操作的地址(上升沿)
	for(i=0;i<8;i++)
	{
		DS1302_IO = Command&(0x01<<i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	Data = 16*(Data/10) + Data%10;//10进制转BCD码
	//将数据写入(上升沿)
	for(i=0;i<8;i++)
	{
		DS1302_IO = Data&(0x01<<i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	DS1302_CE = 0;
}



/**
  * @brief 从DB1302中读取某个位置的一个字节的数据
  * @param 要读取的地址
  * @retval 读到的数据
  */
unsigned char DS1302_Read(unsigned char Command)
{
	unsigned char i,Data = 0x00;
	DS1302_CE = 1;
	Command |= 0x01;//将写地址改为读地址
	//读入指令和操作的地址(上升沿)
	for(i=0;i<8;i++)
	{
		DS1302_IO = Command&(0x01<<i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	
	//读取数据(下降沿，比写入少一个周期)
	for(i=0;i<8;i++)
	{	
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if(DS1302_IO){Data |= (0x01<<i);}
	}
	DS1302_IO = 0;
	DS1302_CE = 0;
	return Data;
}



/**
  * @brief 以数组设置全部的时间(年月日时分秒)
  * @param 无
  * @retval 无
  */
void DS1302_setTime(void)
{
	DS1302_Write(DS1302_WP,0x00);
	
	DS1302_Write(DS1302_Year, DS1302_time[0]);
	DS1302_Write(DS1302_Mon, DS1302_time[1]);
	DS1302_Write(DS1302_Date, DS1302_time[2]);
	DS1302_Write(DS1302_Hour, DS1302_time[3]);
	DS1302_Write(DS1302_Min, DS1302_time[4]);
	DS1302_Write(DS1302_Sec, DS1302_time[5]);
	
	DS1302_Write(DS1302_WP,0x80);
}



/**
  * @brief 获取全部的时间存到数组中
  * @param 无
  * @retval 无
  */
void DS1302_readTime(void)
{
	unsigned char temp;
	temp = DS1302_Read(DS1302_Year);
	DS1302_time[0] = temp/16*10+temp%16;//BCD码转10进制数(2位BCD码)
	temp = DS1302_Read(DS1302_Mon);
	DS1302_time[1] = temp/16*10+temp%16;
	temp = DS1302_Read(DS1302_Date);
	DS1302_time[2] = temp/16*10+temp%16;
	temp = DS1302_Read(DS1302_Hour);
	DS1302_time[3] = temp/16*10+temp%16;
	temp = DS1302_Read(DS1302_Min);
	DS1302_time[4] = temp/16*10+temp%16;
	temp = DS1302_Read(DS1302_Sec);
	DS1302_time[5] = temp/16*10+temp%16;
}
