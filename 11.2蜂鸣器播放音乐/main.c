#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"
#include "song.h"

unsigned char FreqSelect = 0, MusicSelect = 0; 

/*
unsigned char star[] = {
	M1,M1,M5,M5,M6,M6,M5,M4,M4,M3,M3,
	M2,M2,M1,M5,M5,M4,M4,M3,M3,M2,M5,
	M5,M4,M4,M3,M3,M2,M1,M1,M5,M5,M6,
	M6,M5,M4,M4,M3,M3,M2,M2,M1,0xff
};
unsigned char code star_time[] = {
	4,4,4,4, 4,4,4+4, 4,4,4,4, 4,4,4+4,
	4,4,4,4, 4,4,4+4, 4,4,4,4, 4,4,4+4,
	4,4,4,4, 4,4,4+4, 4,4,4,4, 4,4,4+4
};
*/

void main(void)
{
	Timer0Init();
	
	while(1)
	{
		if((FreqSelect = sky[MusicSelect]) != 0xff){
			MusicSelect++;
			Delay(SPEED/4*sky[MusicSelect]);
			MusicSelect++;
			TR0 = 0;
			Delay(5);
			TR0 = 1;
		}
		else {
			//播放结束
			TR0 = 0;
			Buzzer_IO = 0;
			while(1);
		}
	}
}

void Timer0_Rountine(void) interrupt 1
{
	if(FreqTable[FreqSelect]){
		TL0 = FreqTable[FreqSelect]%256;		//设置定时初值
		TH0 = FreqTable[FreqSelect]/256;		//设置定时初值
	
		Buzzer_IO = ~Buzzer_IO;//蜂鸣器震动
	}
}