#include <REGX52.H>
#include "Timer1.h"

sbit motor=P1^0;

unsigned char compare = 0;

/**
  * @brief 电机初始化
  * @param 无
  * @retval 无
  */
void Motor_Init(void)
{
	Timer1Init();
}

/**
  * @brief 设置电机转速档位
  * @param 转速档位
  * @retval 无
  */
void Motor_setSpeed(unsigned char speed)
{
	switch(speed){
		case 0:
			compare = 0;
			break;
		case 1:
			compare = 4;
			break;
		case 2:
			compare = 8;
			break;
		case 3:
			compare = 10;
			break;
	}
}

//通过不间断的改变电机运动状态来改变转速(周期性)
void Timer1_Rountine(void) interrupt 3
{
	static unsigned int count = 0;
	TL1 = 0x00;		//设置定时初值
	TH1 = 0xDC;		//设置定时初值
	
	count++;
	count %= 10;
	if(count>=compare){motor=0;}
	else {motor=1;}
}