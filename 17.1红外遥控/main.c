#include <REGX52.H>
#include "myLCD1602.h"
#include "IR.h"

unsigned char num;
unsigned char Address,Command;

//在LCD屏幕上显示红外控制器的地址和命令码
//还有num值（通过遥控器控制）
void main(void)
{
	LCD_Init();
	num = 0;
	Address = 0;
	Command = 0;
	LCD_ShowString(1,1,"ADDR  CMD  NUM");
	IR_Init();
	
	while(1)
	{
		if(IR_getDataFlag() || IR_getRepeatFlag())
		{
			Command = IR_getCommand();
			Address = IR_getAddress();
			
			if(Command == IR_VOL_MINUS)
			{
				num--;
			}
			if(Command == IR_VOL_ADD)
			{
				num++;
			}
		}
		LCD_ShowHexNum(2,1,Address,2);
		LCD_ShowHexNum(2,7,Command,2);
		LCD_ShowNum(2,12,num,3);
	}
}

