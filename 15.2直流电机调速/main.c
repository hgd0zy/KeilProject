#include <REGX52.H>
#include "Key.h"
#include "Nixie.h"
#include "Timer0.h"

sbit LED0=P2^0;
sbit motor=P1^0;

unsigned char compare;
unsigned char key,Speed = 0;

void main(void)
{
	Timer0Init();
	while(1)
	{
		key = getKey();
		if(key == 1)
		{
			Speed++;
			Speed %= 4;
			switch(Speed){
				case 0:
					compare = 0;
					break;
				case 1:
					compare = 50;
					break;
				case 2:
					compare = 75;
					break;
				case 3:
					compare = 100;
					break;
			}
		}
		Nixie(1,Speed);
	}
}

//通过不间断的改变电机运动状态来改变转速(周期性)
void Timer0_Rountine(void) interrupt 1
{
	static unsigned int count = 0;
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	
	count++;
	count %= 100;
	if(count>=compare){LED0 = 1;motor=0;}
	else {LED0 = 0;motor=1;}
}
