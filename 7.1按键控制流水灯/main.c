#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char Led_mode = 1;

void main()
{
	Timer0Init();//初始化定时器0
	P2 = 0xfe;//赋led的初值
	
	//根据按下的按键控制左移和右移
	while(1){
		#if 0
		switch(getKey()){
			case 1:
				Led_mode = 1;
				break;
			case 2:
				Led_mode = -1;
				break;
		}
		#endif
		if(getKey() == 1)Led_mode = -Led_mode;
	}
}

void Timer0_Rountine(void) interrupt 1
{
	static unsigned int count = 0;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	count++;
	
	if(count >= 500)
	{
		count = 0;
		//右移（低位向高位）
		if(Led_mode == 1){
			P2 = _crol_(P2,1);
		}
		//左移（高位向低位）
		if(Led_mode == -1){
			P2 = _cror_(P2,1);
		}
	}
}
