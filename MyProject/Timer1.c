#include "Timer1.h"
#include <REGX52.H>

/**
  * @brief 初始化定时器1计时1ms
  * @param 无
  * @retval 无
  */
void Timer1Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x66;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时

	ET1 = 1;//配置定时器1中断
	EA = 1;//总中断
	PT1 = 0;//中断优先级
}



//定时器1中断调用模板，此为1秒模板
/*
void Timer1_Rountine(void) interrupt 3
{
	static unsigned int count = 0;
	TL1 = 0x66;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	count++;
	
	if(count == 1000)//控制执行次数，每次1ms
	{
		count = 0;

	}
}
*/