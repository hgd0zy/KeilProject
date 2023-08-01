#include <REGX52.H>
#include <INTRINS.h>

sbit BuzzerIO=P2^5;



/**
  * @brief 蜂鸣器所使用的延时函数
  * @param 无
  * @retval 无
  */
static void 
Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}



/**
  * @brief 使蜂鸣器响一段时间(ms)
  * @param 时间(ms)
  * @retval 无
  */
void 
Buzzer_time(unsigned int xms)
{
	//xms *= 2;
	while(xms--)
	{
		BuzzerIO = ~BuzzerIO;
		Buzzer_Delay500us();
	}
}
	
