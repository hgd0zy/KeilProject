#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"

void main(void)
{
	LCD_Init();
	DS1302_Init();
	DS1302_setTime();
	
	while(1)
	{
		DS1302_readTime();
		//年月日
		LCD_ShowNum(1,1,DS1302_time[0],2);
		LCD_ShowChar(1,3,':');
		LCD_ShowNum(1,4,DS1302_time[1],2);
		LCD_ShowChar(1,7,':');
		LCD_ShowNum(1,8,DS1302_time[2],2);
		//时分秒
		LCD_ShowNum(2,1,DS1302_time[3],2);
		LCD_ShowChar(2,3,':');
		LCD_ShowNum(2,4,DS1302_time[4],2);
		LCD_ShowChar(2,7,':');
		LCD_ShowNum(2,8,DS1302_time[5],2);
	}
}
