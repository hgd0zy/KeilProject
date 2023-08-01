#include <REGX52.H>
#include "Nixie.h"
#include "Timer0.h"
#include "Key.h"
#include "AT24C02.h"

unsigned char KeyNumber,Min=0,Sec=0,miniSec=0;
unsigned char runflag=1;

void main(void)
{
	Timer0Init();
	while(1){
		KeyNumber = Key();
		switch(KeyNumber)
		{
			case 1:
				runflag = !runflag;
				break;
			case 2:
				Min = 0;
				Sec = 0;
				miniSec = 0;
				break;
			case 3:
				AT24C02_writeByte(0,Min);
				AT24C02_writeByte(1,Sec);
				AT24C02_writeByte(2,miniSec);
				break;
			case 4:
				Min = AT24C02_readByte(0);
				Sec = AT24C02_readByte(1);
				miniSec = AT24C02_readByte(2);
				break;
		}
		Nixie_setNum(1,Min/10);
		Nixie_setNum(2,Min%10);
		Nixie_setNum(3,11);
		Nixie_setNum(4,Sec/10);
		Nixie_setNum(5,Sec%10);
		Nixie_setNum(6,11);
		Nixie_setNum(7,miniSec/10);
		Nixie_setNum(8,miniSec%10);
	}
}

void Sec_loop(void)
{
	if(runflag){
		miniSec++;
		if(miniSec>=100)
		{
			miniSec %= 100;
			Sec++;
			if(Sec>=60)
			{
				Sec %= 60;
				Min++;
				if(Min >= 60)
				{
					Min = 0;
				}
			}
		}
	}
}

void Timer0_Rountine(void) interrupt 1
{
	static unsigned int count1 = 0,count2 = 0,count3=0;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	
	count1++;
	if(count1 >= 20)//控制执行次数，每次1ms
	{
		Key_scan();
		count1 = 0;
	}
	count2++;
	if(count2 >= 2)
	{
		Nixie_scan();
		count2 = 0;
	}
	count3++;
	if(count3 >= 10)
	{
		Sec_loop();
		count3 = 0;
	}
}
