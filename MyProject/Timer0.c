#include "Timer0.h"
#include <REGX52.H>

void Timer0Init(void)
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0;		//设置定时初值
	TH0 = 0;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0不计时
}

void Timer0_setCount(unsigned int value)
{
	TH0 = value/256;
	TL0 = value%256;
}

void Timer0_run(unsigned char run)
{
	TR0 = run;
}

unsigned int Timer0_getCount(void)
{
	return (TH0<<8)|TL0;
}
