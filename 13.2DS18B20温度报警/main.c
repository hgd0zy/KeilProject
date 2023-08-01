#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Key.h"
#include "AT24C02.h"

char Thigh = 0,Tlow = 0;
unsigned char key_number;
float T;

void main(void)
{
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	while(1)
	{
		//数据读取
		DS18B20_ConvertT();
		T = DS18B20_readT();
		key_number = getKey();
		Thigh = AT24C02_readByte(1);
		Tlow = AT24C02_readByte(0);
		
		//显示实时温度
		if(T<0)
		{
			LCD_ShowChar(1,3,'-');
			T = -T;
		}
		else 
		{
			LCD_ShowChar(1,3,'+');
		}
		LCD_ShowNum(1,4,T,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(T*100)%100,3);
		
		//根据按键控制上下限和使用EEPROM持久化
		if(key_number)
		{
			switch(key_number){
				case 1:
					Thigh++;
					if(Thigh>125){Thigh = 125;}
					break;
				case 2:
					Thigh--;
					if(Thigh<Tlow){Thigh = Tlow;}
					break;
				case 3:
					Tlow++;
					if(Tlow>Thigh){Tlow = Thigh;}
					break;
				case 4:
					Tlow--;
					if(Tlow<-55){Tlow = -55;}
					break;
			}
			AT24C02_writeByte(1,Thigh);
			AT24C02_writeByte(0,Tlow);
		}
		LCD_ShowSignedNum(2,4,Thigh,3);
		LCD_ShowSignedNum(2,12,Tlow,3);
		
		//显示温度报警
		if(T > Thigh){LCD_ShowString(1,13,"OV:H");}
		else if(T < Tlow){LCD_ShowString(1,13,"OV:L");}
		else {LCD_ShowString(1,13,"    ");}
	}
}
