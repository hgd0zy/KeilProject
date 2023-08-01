#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"

void TimeShow(void);
void TimeSet(void);

unsigned char Key, Mode, Cursor = 0, Flash = 0;

void main(void)
{	

	LCD_Init();
	DS1302_Init();
	Timer0Init();
	DS1302_setTime();
	
	while(1)
	{
		Key = getKey();
		if(Key == 1 && Mode == 1)//在切回时将改变的时间写入
		{Mode = 0;DS1302_setTime();}
		else if(Key == 1)//进入设置模式
		{Cursor = 0;Mode = 1;}
		
		switch(Mode){
			case 0:
				TimeShow();
				break;
			case 1:
				TimeSet();
				break;
		}
	}
}

/**
  * @brief 显示当前DS1302中的时间
  * @param 无
  * @retval 无
  */
void
TimeShow(void)
{
	DS1302_readTime();
	//年月日
	LCD_ShowNum(1,1,DS1302_time[0],2);
	LCD_ShowChar(1,3,'-');
	LCD_ShowNum(1,4,DS1302_time[1],2);
	LCD_ShowChar(1,6,'-');
	LCD_ShowNum(1,7,DS1302_time[2],2);
	//时分秒
	LCD_ShowNum(2,1,DS1302_time[3],2);
	LCD_ShowChar(2,3,':');
	LCD_ShowNum(2,4,DS1302_time[4],2);
	LCD_ShowChar(2,6,':');
	LCD_ShowNum(2,7,DS1302_time[5],2);
}



/**
  * @brief 调整数组中的时间并展示
  * @param 无
  * @retval 无
  */
void 
TimeSet(void)
{
	switch(Key){
		case 2:
			Cursor++;
			Cursor %= 6;
			break;
		case 3:
			DS1302_time[Cursor]++;//调整时间(正向)
			if(DS1302_time[0]>99){DS1302_time[0]=0;}//年
			if(DS1302_time[1]>12){DS1302_time[1]=1;}//月
			if(DS1302_time[2]>31 && (DS1302_time[1] == 1 
			|| DS1302_time[1] == 3 || DS1302_time[1] == 5 
			|| DS1302_time[1] == 7 || DS1302_time[1] == 8 
			|| DS1302_time[1] == 10 || DS1302_time[1] ==  12))
			{DS1302_time[2]=1;}
			if(DS1302_time[2]>30 && (DS1302_time[1] == 4 
			|| DS1302_time[1] == 6 || DS1302_time[1] == 9 || DS1302_time[1] == 11))
			{DS1302_time[2]=1;}
			if(DS1302_time[2]>29 && (DS1302_time[1] == 2))
			{DS1302_time[2]=1;}
			if(DS1302_time[2]>28 && (DS1302_time[1] == 2) && (DS1302_time[0]%4))
			{DS1302_time[2]=1;}//日
			if(DS1302_time[3]>23){DS1302_time[3]=0;}//时
			if(DS1302_time[4]>59){DS1302_time[4]=0;}//分
			if(DS1302_time[5]>59){DS1302_time[5]=0;}//秒
			break;
		case 4:
			DS1302_time[Cursor]--;//调整时间(反向)
			if(DS1302_time[0]<0){DS1302_time[0]=99;}//年
			if(DS1302_time[1]<1){DS1302_time[1]=12;}//月
			if(DS1302_time[2]<1){
				if(DS1302_time[1] == 1 || DS1302_time[1] == 3 || DS1302_time[1] == 5 
					|| DS1302_time[1] == 7 || DS1302_time[1] == 8 
					|| DS1302_time[1] == 10 || DS1302_time[1] ==  12)
				{DS1302_time[2]=31;}
				else if(DS1302_time[1] == 4 || DS1302_time[1] == 6 
				|| DS1302_time[1] == 9 || DS1302_time[1] == 11)
				{DS1302_time[2]=30;}
				else if((DS1302_time[1] == 2) && !(DS1302_time[0]%4))
				{DS1302_time[2]=29;}
				else {DS1302_time[2]=28;}
			}
			if(DS1302_time[2]>31 && (DS1302_time[1] == 1 
			|| DS1302_time[1] == 3 || DS1302_time[1] == 5 
			|| DS1302_time[1] == 7 || DS1302_time[1] == 8 
			|| DS1302_time[1] == 10 || DS1302_time[1] ==  12))
			{DS1302_time[2]=1;}
			if(DS1302_time[2]>30 && (DS1302_time[1] == 4 
			|| DS1302_time[1] == 6 || DS1302_time[1] == 9 || DS1302_time[1] == 11))
			{DS1302_time[2]=1;}
			if(DS1302_time[2]>29 && (DS1302_time[1] == 2))
			{DS1302_time[2]=1;}//日
			if(DS1302_time[2]>28 && (DS1302_time[1] == 2) && (DS1302_time[0]%4))
			{DS1302_time[2]=1;}
			if(DS1302_time[3]<0){DS1302_time[3]=23;}//时
			if(DS1302_time[4]<0){DS1302_time[4]=59;}//分
			if(DS1302_time[5]<0){DS1302_time[5]=59;}//秒
			break;
	}
	
	//LCD_ShowNum(2,10,Cursor,2);//调试用
	
	//使选中的位置闪烁以突出选择
	//年月日
	if(Flash && Cursor == 0){LCD_ShowString(1,1,"  ");}
	else {LCD_ShowNum(1,1,DS1302_time[0],2);}
	LCD_ShowChar(1,3,'-');
	if(Flash && Cursor == 1){LCD_ShowString(1,4,"  ");}
	else {LCD_ShowNum(1,4,DS1302_time[1],2);}
	LCD_ShowChar(1,6,'-');
	if(Flash && Cursor == 2){LCD_ShowString(1,7,"  ");}
	else {LCD_ShowNum(1,7,DS1302_time[2],2);}
	//时分秒
	if(Flash && Cursor == 3){LCD_ShowString(2,1,"  ");}
	else {LCD_ShowNum(2,1,DS1302_time[3],2);}
	LCD_ShowChar(2,3,':');
	if(Flash && Cursor == 4){LCD_ShowString(2,4,"  ");}
	else {LCD_ShowNum(2,4,DS1302_time[4],2);}
	LCD_ShowChar(2,6,':');
	if(Flash && Cursor == 5){LCD_ShowString(2,7,"  ");}
	else {LCD_ShowNum(2,7,DS1302_time[5],2);}
}



void Timer0_Rountine(void) interrupt 1
{
	static unsigned int count = 0;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	count++;
	
	if(count == 500)//控制执行次数，每次1ms
	{
		count = 0;
		Flash = ~Flash;//闪烁控制
	}
}
