#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"

static unsigned char sec = 0;
static unsigned char minute = 0;
static unsigned char hour = 0;//给时分秒分别赋初值

void main()
{
	LCD_Init();
	Timer0Init();
	LCD_ShowString(1,1,"Clock:");//时钟提示
	
	while(1)
	{
		LCD_ShowNum(2,1,hour,2);
		LCD_ShowChar(2,3,':');
		LCD_ShowNum(2,4,minute,2);
		LCD_ShowChar(2,6,':');
		LCD_ShowNum(2,7,sec,2);
	}
}

void Timer0_Rountine(void) interrupt 1
{
	static unsigned int count = 0;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	count++;
	
	if(count == 1000)
	{
		count = 0;
		sec++;
		if(sec >= 60)
		{
			//每过60秒分钟数加一
			minute += 1;
			sec -= 60;
		}
		if(minute >= 60)
		{
			//每过60分钟时钟数加一
			hour += 1;
			minute -= 60;
		}
		//每过24小时清零一次
		if(hour >= 24)
			hour = 0;
		
	}
}
