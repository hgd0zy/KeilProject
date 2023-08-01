#include <REGX52.H>
#include "IR.h"
#include "Motor.h"
#include "DS18B20.h"
#include "AT24C02.h"
#include "LCD1602.h"
#include "Delay.h"

#define Motor 1
#define DS18B20 1

unsigned char Speed = 0,Command;
char Thigh = 0,Tlow = 0;
float T;

void main(void)
{
	LCD_Init();
	
	#if DS18B20
	IR_Init();
	#endif
	
	#if Motor
	Motor_Init();
	#endif
	
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	
	while(1)
	{
		//数据读取
		#if DS18B20
		
		DS18B20_ConvertT();
		T = DS18B20_readT();
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
		if(IR_getDataFlag())
		{
			Command = IR_getCommand();
			switch(Command)
			{
				#if Motor
				case IR_0:
					Speed = 0;
					break;
				case IR_1:
					Speed = 1;
					break;
				case IR_2:
					Speed = 2;
					break;
				case IR_3:
					Speed = 3;
					break;
				#endif
				
				case IR_VOL_ADD:
					Thigh++;
					if(Thigh>125){Thigh = 125;}
					break;
				case IR_VOL_MINUS:
					Thigh--;
					if(Thigh<Tlow){Thigh = Tlow;}
					break;
				case IR_NEXT:
					Tlow++;
					if(Tlow>Thigh){Tlow = Thigh;}
					break;
				case IR_PREVIOUS:
					Tlow--;
					if(Tlow<-55){Tlow = -55;}
					break;
			
			}
			
			AT24C02_writeByte(1,Thigh);
			AT24C02_writeByte(0,Tlow);
			
		}
		
		#if Motor
		Motor_setSpeed(Speed);
		#endif
		
		LCD_ShowSignedNum(2,4,Thigh,3);
		LCD_ShowSignedNum(2,12,Tlow,3);
		
		//显示温度报警
		if(T > Thigh){
			
			Delay(40);
			DS18B20_ConvertT();
			T = DS18B20_readT();
			
			if (T > Thigh) {
			LCD_ShowString(1,13,"OV:H");
			Speed = 3; 
			}
		}
		else if(T < Tlow){
			
			Delay(40);
			DS18B20_ConvertT();
			T = DS18B20_readT();
			
			if (T < Tlow) {
			LCD_ShowString(1,13,"OV:L");
			Speed = 0;
			}
		}
		else {LCD_ShowString(1,13,"    ");}
		#endif
		
	}
}
