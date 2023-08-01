#include <REGX52.H>
#include "myLCD1602.h"

void main(void)
{
	LCD_Init();
	LCD_ShowChar(1,1,'@');
	LCD_ShowString(2,1,"Hello!");
	LCD_ShowNum(1,3,789,3);
	LCD_ShowSignedNum(1,7,-99,2);
	LCD_ShowHexNum(1,11,0xB2,2);
	LCD_ShowBinNum(2,8,0xA2,8);
	while(1){}
}
