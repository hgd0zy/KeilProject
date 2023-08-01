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
	int next = 1;
	while(1){
		if(P3_1 == 0){
			P2_0 = ~P2_0;
			
			//此段代码是为了
			//消除按钮的震动导致异常
			Delay1ms(20);
			while(P3_1 == 0);
			Delay1ms(20);
		}
	}
}
