#include <REGX52.H>
#include "LCD1602.h"
#include "Key.h"
#include "I2C.h"
#include "AT24C02.h"
#include "Delay.h"

void main(void)
{
	unsigned char key;
	unsigned int num = 0;
	
	LCD_Init();
	LCD_ShowNum(1,1,num,5);
	
	while(1)
	{
		key = getKey();
		switch(key){
			case 1:
				if(num == 65535){num = 0;}
				else{num++;}
				LCD_ShowNum(1,1,num,5);
				break;
			case 2:
				if(num == 0){num = 65535;}
				else {num--;}
				LCD_ShowNum(1,1,num,5);
				break;
			case 3://读取数据（在开关机时会有一次P3_2=0，所以设置为读取）
				num = AT24C02_readByte(1)*256 + AT24C02_readByte(0);
				LCD_ShowNum(1,1,num,5);
				LCD_ShowString(2,1,"Read OK");
				Delay(1000);
				LCD_ShowString(2,1,"       ");
				break;
			case 4://保存数据
				AT24C02_writeByte(0, num%256);
				AT24C02_writeByte(1, num/256);
				LCD_ShowNum(1,1,num,5);
				LCD_ShowString(2,1,"Write OK");
				Delay(1000);
				LCD_ShowString(2,1,"        ");
				break;
		}
	}
}
