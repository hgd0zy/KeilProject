#include <REGX52.H>
#include <INTRINS.H>

/*
void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
*/

void Delay1ms(unsigned int time)		//@11.0592MHz
{
	unsigned char i, j;
	
	while(time--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}



void main(){
	//每个灯的位置
	int Led[] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
	int i = 0;
	while(1){
		for(i=0;i<8;i++){
			P2 = Led[i];
			Delay1ms(1000);
		}
	}
}