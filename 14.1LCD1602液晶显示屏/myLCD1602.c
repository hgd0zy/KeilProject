#include <REGX52.H>

sbit LCD_RS=P2^6;
sbit LCD_WR=P2^5;
sbit LCD_EN=P2^7;
#define LCD_DataPort P0

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

unsigned int getPow(unsigned char x,unsigned char pow)
{
	unsigned int result=1;
	
	while(pow--){result *= x;}
	
	return result;
}

/**
  * @brief 将一个指令发送给LCD1602
  * @param 要执行命令
  * @retval 无
  */
void WriteCommand(unsigned char command)
{
	LCD_RS = 0;
	LCD_WR = 0;
	LCD_DataPort = command;
	LCD_EN = 1;
	Delay1ms();
	LCD_EN = 0;
	Delay1ms();
}

/**
  * @brief 将一个数据（字符）发送给LCD1602
  * @param 要发送的字符
  * @retval 无
  */
void WriteData(unsigned char Data)
{
	LCD_RS = 1;
	LCD_WR = 0;
	LCD_DataPort = Data;
	LCD_EN = 1;
	Delay1ms();
	LCD_EN = 0;
	Delay1ms();
}

/**
  * @brief 设置光标位置
  * @param 行号，列号
  * @retval 无
  */
void setAC(unsigned char line,unsigned char column)
{
	unsigned char Address;
	if(line == 1){Address = 0x80|(column-1);}
	else if(line == 2){Address = 0xC0|(column-1);}
	WriteCommand(Address);
}

/**
  * @brief LCD1602的初始化（）设置光标，数据模式等
  * @param 无
  * @retval 无
  */
void LCD_Init(void)
{
	WriteCommand(0x38);
	WriteCommand(0x0C);
	WriteCommand(0x06);
	WriteCommand(0x01);
}

/**
	* @brief 在LCD上指定位置显示一个字符
  * @param 行号，列号，字符
  * @retval 无
  */
void LCD_ShowChar(unsigned char line,unsigned char column,unsigned char Char)
{
	setAC(line,column);
	WriteData(Char);
}

/**
  * @brief 在指定位置显示字符串
  * @param 行号，列号，字符串
  * @retval 无
  */
void LCD_ShowString(unsigned char line,unsigned char column,unsigned char string[])
{
	unsigned char i;
	setAC(line,column);
	
	for(i=0;string[i]!='\0';i++)
	{WriteData(string[i]);}
}

/**
	* @brief 显示无符号数字
  * @param 行号，列号，无符号数字，长度
  * @retval 无
  */
void LCD_ShowNum(unsigned char line,unsigned char column,unsigned int num,unsigned char length)
{
	setAC(line,column);
	while(length)
	{
		WriteData((num/getPow(10, --length))%10+'0');
	}
}

/**
	* @brief 在指定位置显示一个有符号数
  * @param 行号，列号，有符号数字，长度
  * @retval 无
  */
void LCD_ShowSignedNum(unsigned char line,unsigned char column,int num,unsigned char length)
{
	unsigned int number;
	setAC(line,column);
	
	if(num>=0){number = num;WriteData('+');}
	else {number = -num;WriteData('-');}
	while(length)
	{
		WriteData((number/getPow(10, --length))%10+'0');
	}
}

/**
  * @brief 在指定位置显示一个数字（十六进制）
  * @param 行号，列号，无符号数字，长度
  * @retval 无
  */
void LCD_ShowHexNum(unsigned char line,unsigned char column,unsigned int num,unsigned char length)
{
	unsigned char HexNum;
	setAC(line,column);

	while(length)
	{
		HexNum = (num/getPow(16, --length))%16;
		if(HexNum<10){WriteData(HexNum+'0');}
		else {WriteData(HexNum-10+'A');}
	}
}

/**
  * @brief 在指定位置显示一个数字（二进制）
  * @param 行号，列号，无符号数字，长度
  * @retval 无
  */
void LCD_ShowBinNum(unsigned char line,unsigned char column,unsigned char num,unsigned char length)
{
	unsigned char BinNum;
	setAC(line,column);

	while(length)
	{
		BinNum = (num/getPow(2, --length))%2;
		WriteData(BinNum+'0');
	}
}
