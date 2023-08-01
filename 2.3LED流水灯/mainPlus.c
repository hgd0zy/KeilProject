#include <REGX52.H>
#include <INTRINS.H>

void Delay1ms(unsigned int time)		//@12.000MHz
{
	unsigned char i, j;

	while(time--){
		i = 12;
		j = 169;
		do
		{
			while (--j);
		} while (--i);
	}
}


void main(){
	int Led[] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
	int i = 0;
	while(1){
		for(i=0;i<8;i++){
			P2 = Led[i];
			Delay1ms(100);
		}
	}
}