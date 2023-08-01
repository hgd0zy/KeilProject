#include <REGX52.H>
#include <INTRINS.H>

void Delay(unsigned int xms);


void main(){
	
	P2 = 0xfe;
	while(1){
		if(P3_1 == 0){
			Delay(20);
			while(P3_1 == 0);
			Delay(20);
			
			P2 = ~(~P2<<1);//左移
			if(P2 == 0xff){
				P2 = 0xfe;//在最左时移动到右边去
			}
		}
		else if(P3_0 == 0){
			Delay(20);
			while(P3_0 == 0);
			Delay(20);
			
			P2 = ~(~P2>>1);//右移
			if(P2 == 0xff){
				P2 = 0x7f;//在最右时移动到最左来
			}
		}
		
	}
}

void Delay(unsigned int xms)		//@11.0592MHz
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
