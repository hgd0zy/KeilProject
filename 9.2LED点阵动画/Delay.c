#include <Delay.h>

//延时函数，参数xms单位为1毫秒
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