#include "Timer0.h"
#include <REGX52.H>

/**
  * @brief 初始化定时器0计时1ms
  * @param 无
  * @retval 无
  */
void Timer0Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时

	ET0 = 1;//配置定时器0中断
	EA = 1;//总中断
	PT0 = 0;//中断优先级
}



//定时器0中断调用模板，此为1秒模板
/*
void Timer0_Rountine(void) interrupt 1
{
	static unsigned int count = 0;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	count++;
	
	if(count == 1000)//控制执行次数，每次1ms
	{
		count = 0;

	}
}
*/