#include <REGX52.H>
#include <INTRINS.H>

void Delay1ms(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;
	
	while(xms--){
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
	while(1){
		if(P3_1 == 0){
			//P2的初始值为11111111
			P2--;
			Delay1ms(20);
			while(P3_1 == 0);
			Delay1ms(20);
		}
	}
}
